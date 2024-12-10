/*
 * DatabaseScanner.cpp
 *
 *  Created on: 2010-07-21
 *      Author: Pavel
 */
#include "DatabaseScanner.h"
#include "Track.h"
#include <FApp.h>


DatabaseScanner::DatabaseScanner():
	_dbTracksSrc(L"/data/dbTracks.db"),
	_pDb(null),
	_opened(false)
{
}

DatabaseScanner::~DatabaseScanner() {
	if(_pDb!=null)
		delete _pDb;
}
void
DatabaseScanner::Construct(){
	_pDb=new Database();
}

void
DatabaseScanner::Open(){
	if(!_opened){
	_pDb->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+_dbTracksSrc,false);
	_opened=true;
	}
}
bool
DatabaseScanner::SetUp(){
	_pDb->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+_dbTracksSrc,true);//konstruujemy baze,true ze ma stworzyc
	_opened=true;

	String query;
	query.SetCapacity(212);//policzona ilosc liter ponizej ;p
	query.Append(L"CREATE TABLE IF NOT EXISTS Statistics ( ");
	query.Append(L"id INTEGER PRIMARY KEY AUTOINCREMENT,");//dodajemy kolumne id!
	query.Append(L"avrageSpeed REAL,");//dodajemy kolumne avrageSpeed
	query.Append(L"maxSpeed REAL,");
	query.Append(L"distance INTEGER,");//dystans
	query.Append(L"calories INTEGER,");//kalorie
	query.Append(L"startTime INTEGER,");
	query.Append(L"endTime INTEGER,");
	query.Append(L"totalTime INTEGER,");
	query.Append(L"pauseTime INTEGER)");
	//AppLog("query size:%d",query.GetLength());

	result r=_pDb->ExecuteSql(query, true);//zaladowanie !
	if(IsFailed(r)) return false;

	query.Clear();
	query.SetCapacity(102);//policzona ilosc liter ponizej ;p
	query.Append(L"CREATE TABLE IF NOT EXISTS Tracks ( ");//tworzymy baze Tracks z koordynatami
	query.Append(L"id INTEGER,");
	query.Append(L"altitude REAL,");//longitude
	query.Append(L"latitude REAL,");//latitude
	query.Append(L"longitude REAL,");//altitude
	query.Append(L"speed REAL )");
	//AppLog("query size:%d",query.GetLength());

	r=_pDb->ExecuteSql(query, true);//zaladowanie !
	if(IsFailed(r)) return false;
	return true;
}


Track*
DatabaseScanner::ReadN(int __value){
	Open();

	Track* stats = new Track();
	stats->Construct();

	String query;
	query.Append(L"SELECT * FROM Statistics WHERE (id='");//zapytanie do bazy danych
	query.Append(__value);/**  */
	query.Append(L"')");

	DbEnumerator* pEnum;

	pEnum = _pDb->QueryN(query);//wykonanie

	if (IsFailed(GetLastResult())|| !pEnum) {
		delete pEnum;
		return null;
	}

	double tempD;//zmienne pomocnicze
	int tempI;
	long long int tempL;

	//czytanie i zapisywanie tego co nam przyslali
	pEnum->Reset();
	pEnum->MoveNext();
	/** wczytywanie */
	pEnum->GetDoubleAt(1,tempD);
		stats->SetAvrageSpeed(tempD);
	pEnum->GetDoubleAt(2,tempD);
		stats->SetMaxSpeed(tempD);
	pEnum->GetIntAt(3,tempI);
		stats->SetDistance(tempI);
	pEnum->GetIntAt(4,tempI);
		stats->SetCalories(tempI);

	/** time spany  */
	pEnum->GetInt64At(5,tempL);
		stats->SetStartTime(tempL);
	pEnum->GetInt64At(6,tempL);
		stats->SetEndTime(tempL);
	pEnum->GetInt64At(7,tempL);
		stats->SetTotalTime(tempL);
	pEnum->GetInt64At(8,tempL);
		stats->SetPauseTime(tempL);

	delete pEnum;

	query.Clear();
	query.Append(L"SELECT * FROM Tracks WHERE (id='");
	query.Append(__value);
	query.Append(L"')");

	pEnum = _pDb->QueryN(query);

	if (IsFailed(GetLastResult())) {
			delete pEnum;
			return null;
	}
	else if(!pEnum){//wypadek kiedy nie ma zadnych punktow
		delete pEnum;
		return stats;
	}
	else{
	TrackPoint point;
	pEnum->Reset();
	while(pEnum->MoveNext()==E_SUCCESS){
		pEnum->GetDoubleAt(1,tempD);
		point.SetAltitude(tempD);
		pEnum->GetDoubleAt(2,tempD);
		point.SetLatitude(tempD);
		pEnum->GetDoubleAt(3,tempD);
		point.SetLongitude(tempD);
		pEnum->GetDoubleAt(4,tempD);
		point.SetSpeed(tempD);
		stats->AddPoint(point);
	}
	}

	delete pEnum;

	return stats;
}
/**
 * Jak zrocil true to znaczy ze zapisal i usnal z pamieci obiekt z pod wskaznika ,jak false to nie zapisal i nie usunal
 * @param __value wskaznik do Track
 * @return
 */
bool
DatabaseScanner::SaveD(Track* __value){
	Open();


	String query;
	result r;
	DbStatement* pStmt;
	DbEnumerator* pEnum;

	if(__value->GetCount()>0){
	_pDb->BeginTransaction();

	/** zajebiscie dlugi statment*/
	query.Append(L"INSERT INTO Statistics (id,avrageSpeed,maxSpeed,distance,calories,startTime,endTime,totalTime,pauseTime) VALUES (?,?,?,?,?,?,?,?,?)");


	pStmt = _pDb->CreateStatementN(query);


	r=pStmt->BindNull(0);
	r=pStmt->BindDouble(1,__value->GetAvrageSpeed());
	r=pStmt->BindDouble(2,__value->GetMaxSpeed());
	r=pStmt->BindInt(3, __value->GetDistance());
	r=pStmt->BindInt(4, __value->GetCalories());
	r=pStmt->BindInt64(5,__value->GetStarTime().GetTicks());
	r=pStmt->BindInt64(6,__value->GetEndTime().GetTicks());
	r=pStmt->BindInt64(7,__value->GetTotalTime().GetTicks());
	r=pStmt->BindInt64(8,__value->GetPauseTime().GetTicks());
	pEnum = _pDb->ExecuteStatementN(*pStmt);
	if(IsFailed(GetLastResult())) {
		delete pEnum;
		delete pStmt;
		return false;
	}

	if(pEnum!=null) delete pEnum;
	if(pStmt!=null) delete pStmt;

	_pDb->CommitTransaction();
	_pDb->BeginTransaction();

	int id;
	query.Clear();
	query.Append(L"SELECT MAX(id) FROM Statistics");

	pEnum=_pDb->QueryN(query);
	pEnum->Reset();
	pEnum->MoveNext();
	pEnum->GetIntAt(0,id);

	delete pEnum;

	query.Clear();
	query.Append(L"INSERT INTO Tracks (id,altitude,latitude,longitude,speed) VALUES(?,?,?,?,?)");
	pStmt = _pDb->CreateStatementN(query);

	TrackPoint* temp;

	IEnumeratorT<TrackPoint*>* pIterator;
	pIterator=__value->GetEnumeratorN();

	pIterator->Reset();
	while(pIterator->MoveNext()==E_SUCCESS){
		pIterator->GetCurrent(temp);
		pStmt->BindInt(0,id);
		pStmt->BindDouble(1,temp->GetAltitude());
		pStmt->BindDouble(2, temp->GetLatitude());
		pStmt->BindDouble(3,temp->GetLongitude());
		pStmt->BindDouble(4, temp->GetSpeed());
		//AppLog("%f",temp->GetSpeed());
		pEnum = _pDb->ExecuteStatementN(*pStmt);
		if(IsFailed(GetLastResult())) {
			_pDb->RollbackTransaction();
			Delete(id);
			delete pEnum;
			delete pStmt;
			return false;
		}
	}
	if(pEnum!=null)delete pEnum;
	if(pStmt!=null)delete pStmt;

	_pDb->CommitTransaction();
	}
	return true;
}

DbEnumerator*
DatabaseScanner::ReadTracksN(){
	Open();

	String query;
	query.Append(L"SELECT id,startTime FROM Statistics");
	DbEnumerator* pEnum;
	pEnum= _pDb->QueryN(query);
	return pEnum;
}

bool
DatabaseScanner::Empty(){
	Open();
	String query;
	query.Append("SELECT id FROM Statistics");
	DbEnumerator* pEnum;
	pEnum=_pDb->QueryN(query);
	if(pEnum!=null) return false;
	else return true;

}


float
DatabaseScanner::GetAvrageSpeed(){
	Open();

	double speed,temp;
	int count;
	String query;
	speed=0;
	count=0;
	query.Append(L"SELECT avrageSpeed FROM Statistics");


	DbEnumerator* pEnum;

	pEnum = _pDb->QueryN(query);
	if(!pEnum) {
			return 0.0f;
	}

	count=0;

	pEnum->Reset();
	while(pEnum->MoveNext()==E_SUCCESS){
		pEnum->GetDoubleAt(0,temp);
		speed+=temp;
		count++;
	}

	delete pEnum;
	if(count==0) count =1;
	return (float)speed/count;
}

float
DatabaseScanner::GetMaxSpeed(){
	Open();
	double maxSpeed;
	maxSpeed=0;
	String query;
	query.Append(L"SELECT MAX(maxSpeed) FROM Statistics");

	DbEnumerator* pEnum;

	pEnum =_pDb->QueryN(query);
	if(!pEnum){
		return 0.0f;
	}
	pEnum->Reset();
	pEnum->MoveNext();
	pEnum->GetDoubleAt(0,maxSpeed);

	delete pEnum;

	return (float)maxSpeed;
}

int
DatabaseScanner::GetTotalDistance(){
	Open();

	int distance,temp;
	String query;
	distance=0;
	query.Append(L"SELECT distance FROM Statistics");

	DbEnumerator* pEnum;

	pEnum = _pDb->QueryN(query);

	if(!pEnum) {
		return 0.0f;
	}

	pEnum->Reset();
	while(pEnum->MoveNext()==E_SUCCESS){
		pEnum->GetIntAt(0,temp);//?
		distance+=temp;
	}

	delete pEnum;
	return distance;
}

int
DatabaseScanner::GetCalories(){
	Open();

	int calories,temp;
	String query;
	calories=0;
	query.Append(L"SELECT calories FROM Statistics");

	DbEnumerator* pEnum;

	pEnum = _pDb->QueryN(query);

	if(!pEnum) {
		return 0.0f;
	}

	pEnum->Reset();
	while(pEnum->MoveNext()==E_SUCCESS){
		pEnum->GetIntAt(0,temp);//?
		calories+=temp;
	}

	delete pEnum;

	return calories;
}

int
DatabaseScanner::GetFurthestRun(){
	Open();
	int distance;
	distance=0;
	String query;
	query.Append(L"SELECT MAX(distance) FROM Statistics");

	DbEnumerator* pEnum;

	pEnum =_pDb->QueryN(query);
	if(!pEnum){
		return 0;
	}
	pEnum->Reset();
	pEnum->MoveNext();
	pEnum->GetIntAt(0,distance);

	delete pEnum;

	return distance;
}

TimeSpan
DatabaseScanner::GetTotalTime(){
	Open();
	long long int time,temp;
	time=0;
	String query;

	query.Append(L"SELECT totalTime FROM Statistics");

	DbEnumerator* pEnum;

	pEnum =_pDb->QueryN(query);

	if(!pEnum){
		TimeSpan span(0);
		return span;
	}

	pEnum->Reset();
	while(pEnum->MoveNext()==E_SUCCESS){
		pEnum->GetInt64At(0,temp);//?
		time+=temp;
	}

	delete pEnum;

	TimeSpan span(time);
	return span;
}

TimeSpan
DatabaseScanner::GetLongestRun(){
	Open();
	long long int time;
	time=0;
	String query;
	query.Append(L"SELECT MAX(totalTime) FROM Statistics");

	DbEnumerator* pEnum;

	pEnum =_pDb->QueryN(query);
	if(!pEnum){
		TimeSpan span(0);
		return span;
	}
	pEnum->Reset();
	pEnum->MoveNext();
	pEnum->GetInt64At(0,time);

	delete pEnum;

	TimeSpan span(time);
	return span;
}

bool
DatabaseScanner::DeleteAll(){
	result r=Database::Delete(_dbTracksSrc);
	if(IsFailed(r)) return false;
	return SetUp();
}

bool
DatabaseScanner::Delete(int __value){
	Open();
	_pDb->BeginTransaction();
	String query;
	query.Append(L"DELETE FROM Statistics WHERE (id='");
	query.Append(__value);
	query.Append(L"')");
	result r;
	r=_pDb->ExecuteSql(query, true);
	if (IsFailed(r)){
		_pDb->RollbackTransaction();
		return false;
	}
	query.Clear();
	query.Append(L"DELETE FROM Tracks WHERE (id='");
	query.Append(__value);
	query.Append(L"')");
	r=_pDb->ExecuteSql(query, true);
	if (IsFailed(r)){
		_pDb->RollbackTransaction();
		return false;
	}
	_pDb->CommitTransaction();
	return true;
}

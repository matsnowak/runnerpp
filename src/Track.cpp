/*
 * Track.cpp
 *
 *  Created on: 2010-07-14
 *      Author: Mateusz
 */

#include "Track.h"

using Tizen::Base::Collection::LinkedListT;
Track::Track() :
	_startTime(0), _endTime(0), _pauseTime(0), _totalTime(0), _save(false),_maxAltitude(0),
	_minAltitude(0), _maxLongitude(0),_minLongitude(0),_maxLatitude(0),_minLatitude(0),_maxSpeed(0),
	_avrageSpeed(0),_Calories(0),_distance(0){
}

result Track::Construct(void) {
	_points = new LinkedListT<TrackPoint*> (); //TODO: Sprawdzic czy napewno zwraca to co powinno!
	if (null != _points)
		return E_SUCCESS;
	else
		return E_FAILURE;
}

Track::~Track() {
	if (null != _points) {
		Tizen::Base::Collection::IEnumeratorT<TrackPoint*>* temp =_points->GetEnumeratorN();
		temp->Reset();
		TrackPoint* tempVertex;
		while(temp->MoveNext() == E_SUCCESS){
			temp->GetCurrent(tempVertex);
			delete tempVertex;
		}
		delete temp;
		_points->RemoveAll();
		delete _points;
		_points = null;
	}
}

Tizen::Base::Collection::IEnumeratorT<TrackPoint*>* Track::GetEnumeratorN(void) {
	return _points->GetEnumeratorN();
}

result Track::AddPoint(TrackPoint& trackPoint) {
	result r = _points->Add(new TrackPoint(trackPoint));

	// Jesli na liscie jest tylko jeden punkt to on ma wartosci charakterystyczne
	if (1 == _points->GetCount()) {
		_maxAltitude = trackPoint.GetAltitude();
		_minAltitude = trackPoint.GetAltitude();
		_maxLatitude = trackPoint.GetLatitude();
		_minLatitude = trackPoint.GetLatitude();
		_maxLongitude = trackPoint.GetLongitude();
		_minLongitude = trackPoint.GetLongitude();
	} else {
		// Altitude
		if (trackPoint.GetAltitude() > _maxAltitude)
			_maxAltitude = trackPoint.GetAltitude();
		else if (trackPoint.GetAltitude() < _minAltitude)
			_minAltitude = trackPoint.GetAltitude();

		// Latitude
		if (trackPoint.GetLatitude() > _maxLatitude)
			_maxLatitude = trackPoint.GetLatitude();
		else if (trackPoint.GetLatitude() < _minLatitude)
			_minLatitude = trackPoint.GetLatitude();

		// Longitude
		if (trackPoint.GetLongitude() > _maxLongitude)
			_maxLongitude = trackPoint.GetLongitude();
		else if (trackPoint.GetLongitude() < _minLongitude)
			_minLongitude = trackPoint.GetLongitude();
	}
	return r;
}

void Track::SetTotalTime(TimeSpan time) {
	_totalTime = time;
}

void Track::SetStartTime(TimeSpan time) {
	_startTime = time;
}

void Track::SetAvrageSpeed(float speed) {
	_avrageSpeed = speed;
}

TimeSpan Track::GetEndTime(void) const {
	return _endTime;
}

float Track::GetAvrageSpeed(void) const {
	return _avrageSpeed;
}

TimeSpan Track::GetTotalTime(void) const {
	return _totalTime;
}

void Track::SetEndTime(TimeSpan time) {
	_endTime = time;
}

TimeSpan Track::GetStarTime(void) const {
	return _startTime;
}

TimeSpan Track::GetPauseTime(void) const {
	return _pauseTime;
}

void Track::SetDistance(int distance) {
	_distance = distance;
}

int Track::GetDistance(void) const {
	return _distance;
}

void Track::SetPauseTime(TimeSpan time) {
	_pauseTime = time;
}

float Track::GetMaxSpeed(void) const {
	return _maxSpeed;
}

void Track::SetMaxSpeed(float speed) {
	_maxSpeed = speed;
}

int Track::GetCalories(void) const {
	return _Calories;
}

void Track::SetCalories(int kcal) {
	_Calories = kcal;
}

void Track::_Reset() {
	_avrageSpeed = 0;
	_endTime = 0;
	_startTime = 0;
}

void Track::ClearAll(void) {
	_points->RemoveAll();
	_Reset();
}

int Track::GetCount(void) const {
	return _points->GetCount();
}

// Characteristics

float Track::GetMaxAltitude() const {
	return _maxAltitude;
}

float Track::GetMaxLatitude() const {
	return _maxLatitude;
}

float Track::GetMaxLongitude() const {
	return _maxLongitude;
}

float Track::GetMinAltitude() const {
	return _minAltitude;
}

float Track::GetMinLatitude() const {
	return _minLatitude;
}

float Track::GetMinLongitude() const {
	return _minLongitude;
}

void Track::SetMaxAltitude(float maxAltitude) {
	this->_maxAltitude = maxAltitude;
}

void Track::SetMaxLatitude(float maxLatitude) {
	this->_maxLatitude = maxLatitude;
}

void Track::SetMaxLongitude(float maxLongitude) {
	this->_maxLongitude = maxLongitude;
}

void Track::SetMinAltitude(float minAltitude) {
	this->_minAltitude = minAltitude;
}

void Track::SetMinLatitude(float minLatitude) {
	this->_minLatitude = minLatitude;
}

void Track::SetMinLongitude(float minLongitude) {
	this->_minLongitude = minLongitude;
}

TrackPoint*
Track::GetTrackPointAt(int n){
	TrackPoint* tp;
	_points->GetAt(n,tp);
	return tp;
}

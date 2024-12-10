/*
 * DatabaseScanner.h
 *
 *  Created on: 2010-07-21
 *      Author: Pavel
 */

#ifndef DATABASESCANNER_H_
#define DATABASESCANNER_H_

#include <FIo.h>
#include <FBase.h>

//#include "ISave.h"
//#include "IRead.h"
#include "Track.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Io;


/**
 * @class	DatabaseServer
 * @brief	Klasa implementuje ISave, i pozwala na zapisanie Klasy Statistics do bazy danych !
 * 			W wewnetrznej logice jest licznik/ID kazdego biegu!
 * 			Przed uzyciem odpalic Construct() !
 * 			Funkcja Open musi zostac odpalona na poczatku kazdej funkcji
 * @note	Klasa przy pierwszym uruchomieniu programu musi wywolac operacje SetUP(), tworzy bazy danych
 * 			Nazwy Tabel: Statistics,  Tracks
 */
class DatabaseScanner/* :
	public ISave,
	public IRead*/
{
private:
	String _dbTracksSrc;//sciezka bazy danych
	Database* _pDb;
	bool _opened;

	void Open();

public:
	DatabaseScanner();
	virtual ~DatabaseScanner();
	bool Delete(int __value);

	void Construct();


	/**
	 * UWAGA !! Wazne by odpalic to przy pierwszym uruchomieniu
	 * @return True-jesli uda sie stworzyc baze danych,false jesli nie
	 */
	bool SetUp();
	/**
	 *
	 * @param __value Track* wskaznik do klasy Track
	 * @return true - zapisal i skasowal Track,false - nie zapisal i nie usunal track
	 */
	bool SaveD(Track* __value);
	/**
	 * Wczytuje statystyki z bazy
	 * @param __value ID - wczytywane
	 * @return	wskaznik do klasy statistics,lub NULL jak sie nie uda
	 */
	Track* ReadN(int __value);

	/**
	 * Wczytuje z bazy danych liste zapisanych tras, pointer nalezy pozniej usunac
	 * @return wskaznik do "listy" trackow
	 */
	DbEnumerator* ReadTracksN();

	/**
	 * sekcja funkcji statystycznych
	 */

	float GetAvrageSpeed();
	float GetMaxSpeed();
	int GetCalories();
	int GetFurthestRun();
	int GetTotalDistance();
	TimeSpan GetLongestRun();
	TimeSpan GetTotalTime();
	/**
	 * Usuwa wszystko
	 * @return true- jak sie udalo ,false inaczej
	 */
	bool DeleteAll();

	/**
	 * Zwraca ilosc kolumn
	 */
	bool Empty();

};

#endif /* DATABASESCANNER_H_ */

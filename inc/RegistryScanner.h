/*
 * RegistryScanner.h
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#ifndef REGISTRYSCANNER_H_
#define REGISTRYSCANNER_H_

#include <FBase.h>
#include <FIo.h>

using namespace Tizen::Base;
using namespace Tizen::Io;

/**
 * @class 	RegistryScanner
 * @brief	Klasa obsluguje rejestr,przed uzyciem powinna byc skonstruowana przez Construct,inaczej wszystko sie wywali -.-
 * 			Przed zczytaniem czegos z rejestru trzeba ustawic odpowiednia sekcje poprze SetSection
 * @note	Metoda SetUp powinna zostac odpalona kiedy pierwszy raz uruchamiamy aplikacje
 * 			Sprawdzic czy to dziala,ale sie kompiluje !
 * 			Info:Bool jest zapisywany jako int 0-false 1-true
 * 			!! Wrazie problemow dodac biblioteke FIo
 * @relates Options
 */

class RegistryScanner {
private:
	Registry _reg;
	String _section;

public:
	RegistryScanner();
	virtual ~RegistryScanner();

	bool Construct();
	/**
	 * @details	Funkcja ta powinna byc odpalona przy pierwszym uruchomieniu! Tworzy wszystkie potrzebne sekcje i pliki ini.
	 * @return 	true jak wszystko zaladuje poprawnie (czyli zawsze )
	 */
	bool SetUP();//jak pierwsszy odpalasz

	bool SetSection(String __section);//odrazu tez ja tworzy jak cos ;p
	String GetSection();
	bool RemoveSection(String __section);

	bool Set(String __key,int __value);
	bool Set(String __key,double __value);
	bool Set(String __key,float __value);
	bool Set(String __key,String __value);
	bool Set(String __key,bool __value);

	bool Add(String __key,int __value);
	bool Add(String __key,double __value);
	bool Add(String __key,float __value);
	bool Add(String __key,String __value);
	bool Add(String __key,bool __value);

	int GetInt(String __key);
	double GetDouble(String __key);
	float GetFloat(String __key);
	String GetString(String __key);
	bool GetBool(String __key);

	bool Save();
};

#endif /* REGISTRYSCANNER_H_ */

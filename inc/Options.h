/*
 * Options.h
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <FBase.h>
#include "RegistryScanner.h"

using namespace Tizen::Base;

/**
 * @class 	Options
 * @brief 	Klasa zajmujaca sie ladowaniem/zapisywaniem opcji, funkcje maja postac
 * 		  	Get<nazwaKlasy>_<nazwazmiennej>();
 * 		  	Set<nazwaKlasy>_<nazwazmiennej>();
 * 			Przed rozpoczecia pracy nalezy odpalic Construct();
 * @example SetVibe_isActive();
 * @note	Klasa uzglednia obsluge klas:Vibe,Personalities
 * @version 0.001 alpha
 */
class Options {
private:
	RegistryScanner* _reg;
	String _section;
	String _key;
	bool _save;
public:
	Options();
	virtual ~Options();

	void Construct();
	void SaveChanges();

	//Class Vibe
	bool GetVibe_isActivated();
	bool SetVibe_isActivated(bool __value);
	int GetVibe_vibrationLevel();
	bool SetVibe_vibrationLevel(int __value);
	int GetVibe_vibrationDistance();
	bool SetVibe_vibrationDistance(int __value);

	//Class Personalities
	int GetPersonalities_weight();
	bool SetPersonalities_weight(int __value);
	int GetPersonalities_height();
	bool SetPersonalities_height(int __value);

};

#endif /* OPTIONS_H_ */

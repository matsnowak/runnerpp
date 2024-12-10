/*
 * Personalities.h
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#ifndef PERSONALITIES_H_
#define PERSONALITIES_H_

#include "Options.h"

/**
 * @class 	Personalities
 * @brief	Klasa przetrzymujaca dane osobowe,posiada same metody getXXX, bo wszystkie zmiany beda robione w Opcjach
 * 			i tym sie zajmie inna klasa. Oczywiscie musi zostac wywolany Construct *
 */


class Personalities {
private:
	int _weight;
	int _height;

public:
	Personalities();
	virtual ~Personalities();

	void Construct();

	int GetWeight();
	int GetHeight();
	/**
	 * @return Zwraca Body Mass Index
	 */
	float GetBMI();
};

#endif /* PERSONALITIES_H_ */

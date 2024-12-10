/*
 * Vibe.h
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#ifndef VIBE_H_
#define VIBE_H_
/**
 *@class Vibe
 *@brief Klasa kt�ra powoduje wibracje telefonu
 */
#include <FBase.h>
#include <FSystem.h>

#include "Options.h"

using namespace Tizen::System;

/**
 * @class	Vibe - obsluguje wibracje telefonu
 * @remarks Zapisywane opcje _state (int-enum dokladnie) _vibrationLevel(int)
 * @relates Options
 */
class Vibe {
private:
	bool _isActivated;
	int _vibrationLevel;
	int _vibrationDistance;
	Vibrator* _pVibe;
	int _n;
public:
	Vibe();
	virtual ~Vibe();

	/**
	 * @brief Trzeba skonstruowac, zeby mogla pobrac opcje
	 */
	void Construct();
	/**
	 * @brief Jesli _state==VIBRATE to vibruje raz w okresie 500ms,jesli nie to nie wibruje
	 */
	void Vibrate(float __value);
};

#endif /* VIBE_H_ */

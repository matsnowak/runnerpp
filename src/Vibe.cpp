/*
 * Vibe.cpp
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#include "Vibe.h"

Vibe::Vibe():_pVibe(null){
}

Vibe::~Vibe() {
	if(_pVibe!=null) delete _pVibe;
}

void
Vibe::Construct(){
	Options options;
	options.Construct();
	_isActivated=options.GetVibe_isActivated();
	_vibrationLevel=options.GetVibe_vibrationLevel();
	_vibrationDistance=options.GetVibe_vibrationDistance();
	_n=1;

	_pVibe = new Vibrator();
	_pVibe->Construct();
}

void
Vibe::Vibrate(float __distance){
	if(_isActivated){//jezeli z opcji wynika ze mozemy vibrowac to vibrujemy
		if(_n*_vibrationDistance<=__distance){
			_pVibe->Start(1000,_vibrationLevel);
			_n++;
		}
	}
}

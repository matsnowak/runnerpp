/*
 * Personalities.cpp
 *
 *  Created on: 2010-07-20
 *      Author: Pavel
 */

#include "Personalities.h"

Personalities::Personalities():
	_weight(0),
	_height(0)
{}

Personalities::~Personalities() {
}

void
Personalities::Construct(){
	Options options;
	options.Construct();
	_weight=options.GetPersonalities_weight();
	_height=options.GetPersonalities_height();
}

int
Personalities::GetWeight(){
	return _weight;
}

int
Personalities::GetHeight(){
	return _height;
}


float
Personalities::GetBMI(){
	return _weight/(_height*_height);
}

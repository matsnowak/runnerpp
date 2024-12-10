/*
 * Vertex.cpp
 *
 *  Created on: 2010-07-17
 *      Author: Pavel
 */

#include "Graph/Vertex.h"

Vertex::Vertex(float __x,float __y,float __z) {
	_x=__x;
	_y=__y;
	_z=__z;

}

Vertex::~Vertex() {
	// TODO Auto-generated destructor stub
}

void
Vertex::reset(){
	_x=0.0f;
	_y=0.0f;
	_z=0.0f;
}

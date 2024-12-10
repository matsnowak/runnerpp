/*
 * GraphVertex.cpp
 *
 *  Created on: 2010-07-19
 *      Author: Pavel
 */

#include "Graph/GraphVertex.h"

GraphVertex::GraphVertex(float __x,float __y,float __z,float __percentage):Vertex(__x,__y,__z){
	_red=__percentage;
	_blue=1.0f-__percentage;
}

GraphVertex::~GraphVertex() {
}

GraphVertex::GraphVertex(const GraphVertex& graphVertex):
	Vertex(graphVertex._x,graphVertex._y,graphVertex._z),_red(graphVertex._red),_blue(graphVertex._blue){
}

void
GraphVertex::Reset(){
	_x=0.0f;
	_y=0.0f;
	_z=0.0f;
	_red=0.0f;
	_blue=0.0f;
}

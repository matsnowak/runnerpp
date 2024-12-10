/*
 * Vertex.h
 *
 *  Created on: 2010-07-17
 *      Author: Pavel
 */

#ifndef VERTEX_H_
#define VERTEX_H_

class Vertex {
public:
	float _x;
	float _y;
	float _z;
	Vertex(float __x,float __y,float __z);
	virtual ~Vertex();
	virtual void reset();
};

#endif /* VERTEX_H_ */

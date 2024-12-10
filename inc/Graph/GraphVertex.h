/*
 * GraphVertex.h
 *
 *  Created on: 2010-07-19
 *      Author: Pavel
 */

#ifndef GRAPHVERTEX_H_
#define GRAPHVERTEX_H_
/**
 * Klasa pomocnicza przy rysowaniu trasy,
 * pretrzymuje wyskalowane wspolrzedne i odcien odicnka
 */
#include "Vertex.h"
class GraphVertex : public Vertex{
public:
	float _red;//odcien koloru czerwonego
	float _blue;//odcien koloru niebieskiego

	GraphVertex(float __x,float __y,float __z,float __percentage);
	GraphVertex(const GraphVertex& graphVertex);
	virtual ~GraphVertex();
	void Reset();


};

#endif /* GRAPH_VERTEX_H_ */

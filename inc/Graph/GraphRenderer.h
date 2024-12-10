/*
 * GraphRenderer.h
 *
 *  Created on: Jun 20, 2013
 *      Author: Pavel
 */

#ifndef GRAPHRENDERER_H_
#define GRAPHRENDERER_H_
#include <FUiIme.h>
#include <FGraphics.h>
#include <gl.h>
#include <FGrpIGlRenderer.h>
#include <FGraphicsOpengl.h>

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <gl.h>
#include <FMedia.h>
#include "Vertex.h"

class GraphRenderer: public Tizen::Graphics::Opengl::IGlRenderer {
public:
	GraphRenderer();
	virtual ~GraphRenderer();

	enum CameraType {
		CT_GLOBAL, CT_TRACK
	};

	void SetSpeedInfo(Tizen::Ui::Controls::Label* label);


	//IGlRenderer
	virtual bool InitializeGl(void);
	virtual bool TerminateGl(void);

	virtual bool Draw(void);

	virtual bool Pause(void);
	virtual bool Resume(void);

	virtual int GetTargetControlWidth(void);
	virtual int GetTargetControlHeight(void);
	virtual void SetTargetControlWidth(int width);
	virtual void SetTargetControlHeight(int height);

	/**
	 * Creepy VOODOO MAGIC MAN !
	 * @param __eyex		tam z kad patrzymy x
	 * @param __eyey		tam z kad patrzymy y
	 * @param __eyez		tam z kad patrzymy z
	 * @param __centerx		tam gdzie patrzymy x
	 * @param __centery		tam gdzie patrzymy y
	 * @param __centerz		tam gdzie patrzymy z
	 * @param __upx			wektor kamery x
	 * @param __upy			wektor kamery y
	 * @param __upz			wektor kamery z
	 */
	void LookAt(float a,
			float b, float c,
			float d, float e,
			float f, float g,
			float h, float i);

	void DrawCube(float __x, float __y, float __z, float red, float green,
			float blue, float size);

	/**
	 * Rotacja kamery,zoom itd.
	 */
	//zwraca wspolrzedne kamer
	float GetCameraX();
	float GetCameraY();
	float GetCameraZ();

	//zmienianie nachylenia kamery
	void RotateLeft();
	void RotateRight();
	void GoUp();
	void GoDown();

	void ZoomIn();
	void ZoomOut();

	//funkcje sprawdzajace czy nie wyszlismy poza zakres danych warosci
	void CheckRadius();
	void CheckAlfa();
	void CheckBeta();

	bool IsInGlobalCameraType();
	void SetDefaultGlobal();
	void SetDefaultTrack();

private:
	void InitializeTrack();
	void UpdateCenterPoint();
	void UpdateLabels();

	CameraType _cameraType;
	float _radius; //promien sfery
	float _radiusGlobal;
	float _radiusTrack;
	float _alfa; //katy potrzebne do opisu sfery w stopniach
	float _beta;
	float _dim; //przekatna calego obiektu
	float _degreeAlfa; //o jaki sotpien obracamy
	float _degreeBeta; //o jaki stopien podnosimy
	float _zoomingValue; //o ile sie przyblizamy
	float _scaleValueXZ; //skalowanie
	float _scaleValueY;
	int _pointsCount;
	Vertex _centerPoint;
	int _currPoint;

	Tizen::Ui::Controls::Label* _pSpeedInfo;


	void SetDefault();
	float* _pColors;
	float* _pVerticles;

	int _colorArray;
	int _verticlesArray;

	int _width;
	int _height;
	int __angle;
};

#endif /* GRAPHRENDERER_H_ */

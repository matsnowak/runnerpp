/*
 * GraphRenderer.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: Pavel
 */

#include "Graph/GraphRenderer.h"
#include "RunnerPP.h"
#include <FBase.h>

using namespace Tizen::Base::Utility;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Media;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Graphics::Opengl;
using namespace Tizen::Base::Collection;

GraphRenderer::GraphRenderer() :
		 _width(480), _height(854),_cameraType(CT_GLOBAL),
		_dim(4.0f), _alfa(179.0f), _beta(80.0f), _degreeBeta(4.0f),
		_degreeAlfa(4.0f), _zoomingValue(0.05f),_centerPoint(0,0,0),
		_currPoint(0),
		_pSpeedInfo(null){
	// TODO Auto-generated constructor stub

}

GraphRenderer::~GraphRenderer() {
	if (_pColors)
		delete[] _pColors;
	if (_pVerticles)
		delete[] _pVerticles;

}
bool GraphRenderer::InitializeGl(void) {
	AppLog("init GL");

	float topY = 0.0;
	float bottomY = 0.0;
	float leftX = 0.0;
	float rightX = 0.0;
	float aspect = 0.0;

	glViewport(0, 0, GetTargetControlWidth(), GetTargetControlHeight());

	glShadeModel(GL_SMOOTH);
	//glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //kolor tla - czarny

	aspect = (float) GetTargetControlWidth() / GetTargetControlHeight();
	//AppLog("w:%d h:%d",_pBitmap->GetWidth(),_pBitmap->GetHeight());
	topY = 0.005 * Math::Tan(60 * 3.14 / 360.0); //obliczanie prespektyw i takich tam
	bottomY = -topY;
	leftX = bottomY * aspect;
	rightX = topY * aspect;

	glMatrixMode(GL_PROJECTION); //wybor macierzy perspektywy
	glFrustumf(rightX, leftX, topY, bottomY, 0.05f, 100.0f); //tworzenie perspektywy blisko-0.1 daleko -10

	glEnable(GL_DEPTH_TEST); //aktywacja glebi
	glDepthMask(GL_TRUE);

	InitializeTrack();
	return true;
}

void GraphRenderer::InitializeTrack() {
	RunnerPP* run =
			static_cast<RunnerPP*>(Tizen::App::Application::GetInstance());
	Track* __track = run->GetTrack();

//wyznaczenie scalowania
	if (__track->GetMaxLongitude() - __track->GetMinLongitude() <= 0.001)
		_scaleValueXZ = 1000;
	else if (__track->GetMaxLongitude() - __track->GetMinLongitude() <= 0.01)
		_scaleValueXZ = 100;
	else if (__track->GetMaxLongitude() - __track->GetMinLongitude() <= 0.1)
		_scaleValueXZ = 10;
	else
		_scaleValueXZ = 1;

	_scaleValueY = 1000;

//srednich warosci
	float midAltitude, midLongitude, midLatitude;
	midAltitude = (__track->GetMaxAltitude() + __track->GetMinAltitude()) / 2;
	midLongitude = (__track->GetMaxLongitude() + __track->GetMinLongitude())
			/ 2;
	midLatitude = (__track->GetMaxLatitude() + __track->GetMinLatitude()) / 2;

	float temp1, temp2, temp3;
	temp1 = (__track->GetMaxAltitude() - midAltitude) / _scaleValueY;
	temp2 = (__track->GetMaxLongitude() - midLongitude) * _scaleValueXZ;
	temp3 = (__track->GetMaxLatitude() - midLatitude) * _scaleValueXZ;
//AppLog("altitude:%f longitude:%f latitude:%f",temp1,temp2,temp3);

//szukamy promienia sfery
	if (temp2 > temp3) {
		if (temp2 > temp1)
			_radius = 10 * temp2;
		else
			_radius = 10 * temp1;
	} else {
		if (temp3 > temp1)
			_radius = 10 * temp3;
		else
			_radius = 10 * temp1;
	}

	_dim = 4 * _radius;
	_zoomingValue = 0.05 * _radius;
	_radius *= 3;
	_radiusGlobal = _radius;

//AppLog("scaleXZ:%f scaleY:%f radius:%f zoom:%f",_scaleValueXZ,_scaleValueY,_radius,_zoomingValue);

	_pColors = new float[__track->GetCount() * 4];
	_pVerticles = new float[__track->GetCount() * 3];
	_pointsCount = __track->GetCount();

	TrackPoint* point;

	IEnumeratorT<TrackPoint*>* pIterator;
	pIterator = __track->GetEnumeratorN();

	pIterator->Reset();
	if (pIterator->MoveNext() == E_SUCCESS) { //wskazuje na pierwszy
		pIterator->GetCurrent(point);
		//pierwszy wieszcholek
		_pVerticles[0] = (float) (midLongitude - (point->GetLongitude()))
				* _scaleValueXZ;
		_pVerticles[1] = (midAltitude - (point->GetAltitude())) / _scaleValueY;
		_pVerticles[2] = (float) (midLatitude - (point->GetLatitude()))
				* _scaleValueXZ;
		// pierwszy kolor niebieski calkiem
		_pColors[0] = 0.0f;
		_pColors[1] = 0.0f;
		_pColors[2] = 1.0f;
	}
	float speed;
	float maxSpeed = __track->GetMaxSpeed();
	int i = 1;
	while (pIterator->MoveNext() == E_SUCCESS) {
		pIterator->GetCurrent(point);
		_pVerticles[3 * i] = (float) (midLongitude - (point->GetLongitude()))
				* _scaleValueXZ;
		_pVerticles[3 * i + 1] = (midAltitude - (point->GetAltitude()))
				/ _scaleValueY;
		_pVerticles[3 * i + 2] = (float) (midLatitude - (point->GetLatitude()))
				* _scaleValueXZ;
		// pierwszy kolor niebieski calkiem
		_pColors[4 * i] = point->GetSpeed() / maxSpeed;
		_pColors[4 * i + 1] = 0.0f;
		_pColors[4 * i + 2] = 1.0f - (point->GetSpeed() / maxSpeed);
		//AppLog("%f",point->GetSpeed());
		i++;
	}
	delete pIterator;
}

//Obliczenia kamery , creepy voodoo magic men !
void GraphRenderer::LookAt(GLfloat __eyex, GLfloat __eyey, GLfloat __eyez,
		GLfloat __centerx, GLfloat __centery, GLfloat __centerz, GLfloat __upx,
		GLfloat __upy, GLfloat __upz) {
	GLfloat m[16];
	GLfloat x[3], y[3], z[3];
	GLfloat mag;

	/* Make rotation matrix */

	/* Z vector */
	z[0] = __eyex - __centerx;
	z[1] = __eyey - __centery;
	z[2] = __eyez - __centerz;
	mag = Math::Sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
	if (mag) { /* mpichler, 19950515 */
		z[0] /= mag;
		z[1] /= mag;
		z[2] /= mag;
	}

	/* Y vector */
	y[0] = __upx;
	y[1] = __upy;
	y[2] = __upz;

	/* X vector = Y cross Z */
	x[0] = y[1] * z[2] - y[2] * z[1];
	x[1] = -y[0] * z[2] + y[2] * z[0];
	x[2] = y[0] * z[1] - y[1] * z[0];

	/* Recompute Y = Z cross X */
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];

	/* mpichler, 19950515 */
	/* cross product gives area of parallelogram, which is < 1.0 for
	 * non-perpendicular unit-length vectors; so normalize x, y here
	 */

	mag = Math::Sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	if (mag) {
		x[0] /= mag;
		x[1] /= mag;
		x[2] /= mag;
	}

	mag = Math::Sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag) {
		y[0] /= mag;
		y[1] /= mag;
		y[2] /= mag;
	}

#define M(row,col)  m[col*4+row]
	M(0, 0) = x[0];
	M(0, 1) = x[1];
	M(0, 2) = x[2];
	M(0, 3) = 0.0;
	M(1, 0) = y[0];
	M(1, 1) = y[1];
	M(1, 2) = y[2];
	M(1, 3) = 0.0;
	M(2, 0) = z[0];
	M(2, 1) = z[1];
	M(2, 2) = z[2];
	M(2, 3) = 0.0;
	M(3, 0) = 0.0;
	M(3, 1) = 0.0;
	M(3, 2) = 0.0;
	M(3, 3) = 1.0;
#undef M
	glMultMatrixf(m);

	/* Translate Eye to Origin */
	glTranslatef(-__eyex, -__eyey, -__eyez);

}

bool GraphRenderer::TerminateGl(void) {
	if(eglGetError() != EGL_SUCCESS)
		AppLog("Cos sie wyjebało ;D");
	return true;
}

const GLfloat ONEP = GLfloat(+1.0f);
const GLfloat ONEN = GLfloat(-1.0f);
const GLfloat ZERO = GLfloat( 0.0f);

bool GraphRenderer::Draw(void) {

	glViewport(0, 0, _width, _height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	LookAt(GetCameraX() + _centerPoint._x, GetCameraY() + _centerPoint._y,
			GetCameraZ() + _centerPoint._z, _centerPoint._x, _centerPoint._y,
			_centerPoint._z, 0, 1, 0);

	//Rysowanie Trasy ----------

	DrawCube(_pVerticles[0], _pVerticles[1], _pVerticles[2], 1.0f, 1.0f, 1.0f,
			0.005f);
	glLineWidth(5.0f);
	glEnableClientState(GL_VERTEX_ARRAY); //dezaktywacja obslugi tablicy wierzcholkow
	glEnableClientState(GL_COLOR_ARRAY); //aktywacja obslugi tablicy kolor�w

	glVertexPointer(3, GL_FLOAT, 0, _pVerticles);
	glColorPointer(4, GL_FLOAT, 0, _pColors);

	glDrawArrays(GL_LINE_STRIP, 0, _pointsCount);

	glDisableClientState(GL_VERTEX_ARRAY); //dezaktywacja obslugi tablicy wierzcholkow
	glDisableClientState(GL_COLOR_ARRAY); //aktywacja obslugi tablicy kolor�w

	glLineWidth(5.0f);
	glColor4f(0, 0, 0, 0);
	///dodajemy kolorowy znacznik :p
	if (_cameraType == CT_TRACK) {
		if (_currPoint != 0 && _currPoint != (_pointsCount - 1)) {
			DrawCube(_pVerticles[_currPoint * 3],
					_pVerticles[_currPoint * 3 + 1],
					_pVerticles[_currPoint * 3 + 2], _pColors[_currPoint * 4],
					_pColors[_currPoint * 4 + 1], _pColors[_currPoint * 4 + 2],
					0.002);
		}
	}

	glColor4f(0, 0, 0, 0);
	DrawCube(_pVerticles[_pointsCount * 3 - 3],
			_pVerticles[_pointsCount * 3 - 2],
			_pVerticles[_pointsCount * 3 - 1], 1.0f, 0.0f, 0.0f, 0.005f);

	glFlush();

	return true;
}

bool GraphRenderer::IsInGlobalCameraType() {
	return _cameraType == CT_GLOBAL;
}

void GraphRenderer::DrawCube(float __x, float __y, float __z, float red,
		float green, float blue, float size) {
	GLfloat cube[] = { //wspolrzedne szescinu
			__x - size, __y - size, __z + size, //3
			__x + size, __y - size, __z + size, //2
			__x - size, __y + size, __z + size, //0
			__x + size, __y + size, __z + size, //1
			__x - size, __y + size, __z - size, //4
			__x + size, __y + size, __z - size, //5
			__x - size, __y - size, __z - size, //7
			__x + size, __y - size, __z - size, //6
			__x + size, __y - size, __z + size, //2
			__x + size, __y + size, __z - size, //5
			__x + size, __y + size, __z + size, //1
			__x - size, __y + size, __z - size, //4
			__x - size, __y + size, __z + size, //0
			__x - size, __y - size, __z - size, //7
			__x - size, __y - size, __z + size, //3
			__x + size, __y - size, __z + size, //2
			};

	glColor4f(red, green, blue, 0.0f);

	glEnableClientState(GL_VERTEX_ARRAY); //aktywacja tablicy
	glVertexPointer(3, GL_FLOAT, 0, cube);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);
	glDisableClientState(GL_VERTEX_ARRAY); //dezaktywacja
}

//Wyliczanie wspolrzednych
float GraphRenderer::GetCameraX() {
	//x=r*sin(alfa)*cos(beta)
	return _radius * Math::Sin((double) (_alfa * Math::GetPi()) / 180)
			* Math::Cos((double) _beta * Math::GetPi() / 180);
}
float GraphRenderer::GetCameraY() {
	//y=r*cos(alfa)
	return _radius * Math::Cos((double) (_alfa * Math::GetPi()) / 180);
}

float GraphRenderer::GetCameraZ() {
	//z=r*sin(alfa)*sin(beta)
	return _radius * Math::Sin((double) (_alfa * Math::GetPi()) / 180)
			* Math::Sin((double) _beta * Math::GetPi() / 180);
}

//obsluga katow i promienia
void GraphRenderer::GoUp() {
	_alfa += _degreeAlfa;
	if (_alfa > 179)
		_alfa = 179;
	if (_alfa < 1)
		_alfa = 1;
	//AppLog("alfa:%f",_alfa);
}

void GraphRenderer::GoDown() {
	_alfa -= _degreeAlfa;
	CheckAlfa();
}

void GraphRenderer::CheckAlfa() {
	if (_alfa > 179)
		_alfa = 179;
	if (_alfa < 1)
		_alfa = 1;
	//AppLog("alfa:%f",_alfa);
}

void GraphRenderer::RotateLeft() {
	_beta += _degreeBeta;
	CheckBeta();
}

void GraphRenderer::RotateRight() {
	_beta -= _degreeBeta;
	CheckBeta();
}

void GraphRenderer::CheckBeta() {
	if (_beta > 360)
		_beta = 0;
	if (_beta < 0)
		_beta = 360;
}

void GraphRenderer::ZoomIn() {
	if (_cameraType == CT_GLOBAL) {
		_radius += _zoomingValue;
		CheckRadius();
	} else {
		_currPoint--;
		if (_currPoint < 0)
			_currPoint = 0;
		UpdateCenterPoint();
	}
}

void GraphRenderer::ZoomOut() {
	if (_cameraType == CT_GLOBAL) {
		_radius -= _zoomingValue;
		CheckRadius();
	} else {
		_currPoint++;
		if (_currPoint >= _pointsCount)
			_currPoint = _pointsCount - 1;
		UpdateCenterPoint();
	}
}

void GraphRenderer::CheckRadius() {
	if (_radius > _dim)
		_radius = _dim;
	if (_radius < 0)
		_radius = 0.001;
	//AppLog("rad:%f",_radius);
}

void GraphRenderer::UpdateCenterPoint() {
	_centerPoint._x = _pVerticles[_currPoint * 3];
	_centerPoint._y = _pVerticles[_currPoint * 3 + 1];
	_centerPoint._z = _pVerticles[_currPoint * 3 + 2];
	UpdateLabels();
}

void GraphRenderer::SetDefault() {
	_alfa = 179.0f;
	_beta = 80.0f;
	_degreeBeta = 4.0f;
	_degreeAlfa = 4.0f;
}

void GraphRenderer::SetDefaultGlobal() {
	_cameraType = CT_GLOBAL;
	_centerPoint._x = 0.0f;
	_centerPoint._y = 0.0f;
	_centerPoint._z = 0.0f;
	_radius = _radiusGlobal;
	_currPoint = 0;
	SetDefault();
}

void GraphRenderer::SetDefaultTrack() {
	_cameraType = CT_TRACK;
	_radius = 1.0f;
	UpdateCenterPoint();
	SetDefault();
}

void GraphRenderer::SetSpeedInfo(Tizen::Ui::Controls::Label* label) {
	_pSpeedInfo = label;
}

void GraphRenderer::UpdateLabels() {
	float tmp;
	Tizen::Base::String str;
	Tizen::App::Application *pApp = Tizen::App::Application::GetInstance();
	pApp->GetAppResource()->GetString("IDS_SPEED_SMALL", str);
	RunnerPP *run =
			static_cast<RunnerPP*>(Tizen::App::Application::GetInstance());
	Track *track = run->GetTrack();
	TrackPoint *tp;
	tp = track->GetTrackPointAt(_currPoint);
	tmp = tp->GetSpeed();
	tmp *= 100;
	int tmpI = (int) tmp;
	tmp = (float) tmpI / 100;
	str.Append(tmp);

	str.Append(" km/h");

	_pSpeedInfo->SetText(str);
}

bool GraphRenderer::Pause(void) {
	if(eglGetError() != EGL_SUCCESS)
		AppLog("Cos sie wyjebało ;D");

	return true;
}

bool GraphRenderer::Resume(void) {
	if(eglGetError() != EGL_SUCCESS)
		AppLog("Cos sie wyjebało ;D");

	return true;
}

int GraphRenderer::GetTargetControlWidth(void) {
	// TODO:
	// Return target control width
	AppLog("cos sie dzieje w g");
	return _width;
}

int GraphRenderer::GetTargetControlHeight(void) {
	// TODO:
	// Return target control height
	AppLog("cos sie dzieje h g");
	return _height;
}

void GraphRenderer::SetTargetControlWidth(int width) {
	// TODO:
	// Assign target control width
	AppLog("cos sie dzieje w");
	_width = width;
}

void GraphRenderer::SetTargetControlHeight(int height) {
	// TODO:
	// Assign target control height
	AppLog("cos sie dzieje h");
	_height = height;
}


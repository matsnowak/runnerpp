/*
 * Graph.h
 *
 *  Created on: Jul 22, 2010
 *      Author: Pavel
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <gl.h>
#include <FMedia.h>

#include "Graph/GraphVertex.h"
#include "IBaseForm.h"
#include "Graph/GraphRenderer.h"
#include <FGrpGlPlayer.h>


class Graph :
	public IBaseForm,
	public Tizen::Ui::ITouchEventListener,
	public Tizen::Ui::IActionEventListener
	//public Tizen::Base::Runtime::ITimerEventListener
{
public:
	Graph();
	virtual ~Graph();

	/**
	 * FORM STUFF
	 */
	result OnInitializing(void);
	bool Initialize();

	/**
	 * ITouchEventListener STUFF
	 */
	void OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	void OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	void OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	void OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	//nie implementowane
	void OnTouchDoublePressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){};
	void OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){};
	void OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo){};

	//IActionEventListener
	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	//ITime
	//void OnTimerExpired  ( Tizen::Base::Runtime::Timer &  timer );

	Tizen::Graphics::Opengl::GlPlayer* GetPlayer();
private:

	GraphRenderer* _pGraphRenderer;
	Tizen::Graphics::Opengl::GlPlayer* _pPlayer;

	/**
	 *zmienne dotyczace kontroli dotyku
	 */
	Tizen::Graphics::Point 	_lastStartingPoint;//ostatnia pozycja z ktorej startowalismy
	Tizen::Graphics::Point	_lastPoint;//ostatnia pozycja na jakiej byl palec

	Tizen::Graphics::Point	_lastZoomedPoint1;//punkty potrzebne do zumowania
	Tizen::Graphics::Point	_lastZoomedPoint2;

	enum touchStatus //enum do rozpoznawania akcji
	{
		TS_NONE,
		TS_MOVE,
		TS_ZOOM
	} _touchStatus;

	/**
	 * Buttons
	 */
	static const int ID_TO_MAINMENU = 100;
	static const int ID_LEFT_ARROW = 101;
	static const int ID_SAVE = 102;
	static const int ID_CHANGE_MAP_STYLE = 200;

	Tizen::Base::Runtime::Timer* _pTimer;
	Tizen::Graphics::Bitmap* _pMapTrack;
	Tizen::Graphics::Bitmap* _pMapGlobal;
	Tizen::Ui::Controls::Button* _pChangeMap;
	Tizen::Ui::Controls::Label* _pSpeedInfo;
};

#endif /* GRAPH_H_ */

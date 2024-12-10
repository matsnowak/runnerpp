/*
 * RunForm.h
 *
 *  Created on: 2010-07-28
 *      Author: Mateusz
 */

#ifndef RUNFORM_H_
#define RUNFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FIo.h>
#include <FMedia.h>
#include <FLocations.h>

#include "GpsLocationListener.h"
#include "IBaseForm.h"
#include "Run.h"
#include "ILockedForm.h"
#include "cmath"


using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Base;

class RunForm: public IBaseForm,
		public Tizen::Ui::IActionEventListener,
		public Tizen::Base::Runtime::ITimerEventListener,
		public ILockedForm {

	// Lifecycle
public:
	RunForm();
	virtual ~RunForm();

	bool Initialize();
	result OnDraw();
	result OnInitializing();
	result OnTerminating();

	void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void OnTimerExpired(Tizen::Base::Runtime::Timer & timer);

	void Lock(int lockReason);
	void Unlock(int lockReason);

	void SendSomethingToForm(int something);

	// Attributes
private:
	Bitmap* _pBackground;

	static const int ID_START = 100;
	static const int ID_PAUSE = 101;
	static const int ID_END = 102;
	static const int ID_CANCEL = 103;
	static const int ID_TO_MENU = 104;


	// Buttons
	Button* _pStartButton;
	Button* _pPauseButton;
	Button* _pEndButton;
	Button* _pCancelButton;
	Button* _pToMainMenu;

	// Labels
	EnrichedText* _pTimeText;
	TextElement* _pTimeTextString;

	EnrichedText* _pTime;
	TextElement* _pTimeString;

	EnrichedText* _pCaloriesText;
	TextElement* _pCaloriesTextString;


	EnrichedText* _pCalories;
	TextElement* _pCaloriesString;
	Integer		_calories;
	String		_CaloriesText;

	EnrichedText* _pDistanceText;
	TextElement* _pDistanceTextString;

	EnrichedText* _pDistance;
	TextElement* _pDistanceString;
	Integer		_distance;
	String		_DistanceText;

	EnrichedText* _pKm;
	TextElement* _pKMString;

	EnrichedText* _pSpeed;
	TextElement* _pSpeedString;
	float		_speed;
	String		_SpeedText;

	// Fonts
	Font* _pLabelsFont;
	Font* _pVariablesFont;
	Font* _pKmlFont;
	Font* _pSpeedFont;

	Run* _pRun;
	GpsLocationListener *_gpsLocationListener;

	Label* _pNSatelitesLabel;

	TimeSpan _span;

	Tizen::Base::Runtime::Timer _timer;
	Tizen::Base::String _watchText;
	Tizen::Base::String _currSpeedText;
	Tizen::Base::String _avgSpeedText;
	Tizen::Base::String _distanceText;

	static const int INTERVAL = 50;
    void _updateCalories();
    void _updateSpeed();
    void _updateDistance();
    void _updateWatch();
    float _round100(float f);
    float _round(float f);
    void vibrate_on_end();

    Popup * _signalSearching;
    bool _isLocked;

};

#endif /* RUNFORM_H_ */

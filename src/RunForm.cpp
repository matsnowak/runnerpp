/*
 * RunForm.cpp
 *
 *  Created on: 2010-07-28
 *      Author: Mateusz
 */

#include "RunForm.h"
#include "RunnerPP.h"
#include "FormMgr.h"
#include "Utils.h"
#include <FSystem.h>


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;
using namespace Tizen::System;


RunForm::RunForm() :
	_pBackground(null), _span(0), _isLocked(true),_signalSearching(null){
	// TODO Auto-generated constructor stub

}

RunForm::~RunForm() {
	if (null != _gpsLocationListener) {
		delete _gpsLocationListener;
		_gpsLocationListener = null;
	}

	if (null != _pRun) {
		delete _pRun;
		_pRun = null;
	}

}

result RunForm::OnTerminating() {
	if (null != _pBackground) {
		delete _pBackground;
		_pBackground = null;
	}
	if(_pLabelsFont!=null) delete _pLabelsFont;
	if(_pVariablesFont!= null) delete _pVariablesFont;
	if(_pKmlFont!= null) delete _pKmlFont;
	if(_pSpeedFont!= null) delete _pSpeedFont;
	if(_pTimeString!= null) delete _pTimeString;
	if(_pTime!= null) delete _pTime;
	if(_pCaloriesText!= null) delete _pCaloriesText;
	if(_pCaloriesTextString!= null) delete _pCaloriesTextString;
	if(_pDistanceText!= null) delete _pDistanceText;
	if(_pDistanceTextString!= null) delete _pDistanceTextString;
	if(_pTimeTextString!= null) delete _pTimeTextString;
	if(_pDistanceString != null) delete _pDistanceString;
	if(_pKMString!= null) delete _pKMString;
	if(_pCaloriesString!= null) delete _pCaloriesString;
	if(_pSpeedString!= null) delete _pSpeedString;
	if(_pTimeText!= null) delete _pTimeText;
	if(_pCalories!= null) delete _pCalories;
	if(_pDistance!= null) delete _pDistance;
	if(_pKm != null) delete _pKm;
	if(_pSpeed!= null) delete _pSpeed;
	if(_signalSearching) delete _signalSearching;

	Tizen::System::PowerManager::KeepScreenOnState (false,false);
	return E_SUCCESS;
}

void RunForm::OnActionPerformed(const Tizen::Ui::Control & source, int actionId) {
	switch (actionId) {
	case ID_START: {
		if (RUN_STATE_NOT_STARTED_YET == _pRun->GetState()) {
			_pRun->Start();
		}

		if (RUN_STATE_PAUSED == _pRun->GetState()) {
			_pRun->Resume();
			_timer.Start(INTERVAL);
		}
		_pEndButton->SetShowState(true);
		_pStartButton->SetShowState(false);
		_pToMainMenu->SetShowState(false);
		RequestRedraw(true);
	}
		break;

	case ID_END: {
		if (RUN_STATE_RUNNING == _pRun->GetState()) {
			_pRun->Pause();
			_pRun->End();
			_gpsLocationListener->RemoveListener(_pRun);
			_gpsLocationListener->RemoveLockedForm(this);
			Frame *pFrame =
					Application::GetInstance()->GetAppFrame()->GetFrame();
			FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl(
					"FormMgr"));
			pFormMgr->SendUserEvent(FormMgr::REQUEST_TRACKSTATSFORM, null);
		}
	}
		break;

	case ID_CANCEL: {
		_pRun->Pause();
		_pRun->End();

		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl(
				"FormMgr"));

		if (RUN_STATE_NOT_STARTED_YET == _pRun->GetState()) {
			RunnerPP *run=static_cast<RunnerPP*>(Application::GetInstance());
			run->TrackSaved();//w tym momecie robimy abort czyli nie ma trasy do zapisania
			pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		} else if (RUN_STATE_RUNNING == _pRun->GetState()) {
			pFormMgr->SendUserEvent(FormMgr::REQUEST_TRACKSTATSFORM, null);
		}

	}
		break;
	case ID_TO_MENU: {
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl(
				"FormMgr"));
		pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		break;

	}
	default:
		break;
	}
}

bool RunForm::Initialize() {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"Run");
	SetBackgroundColor(Color(0,0,0,0));
	return true;
}

result RunForm::OnInitializing() {
	Image image;
	result r = image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	_gpsLocationListener = new GpsLocationListener();
	if (null !=_gpsLocationListener) {
		r = _gpsLocationListener->Construct();
		_pRun = new Run();
		if (null != _pRun) {
			r = _pRun->Construct();
			_gpsLocationListener->AddListener(_pRun);
			_timer.Construct(*this);
			_timer.Start(INTERVAL);
			if (IsFailed(r)) {
				AppLogException("Nie utworzylem pRun");
				return r;
			}
			_gpsLocationListener->AddLockedForm(this);
		}

	}

	/* Guziczki */

	/* StartButton */
	Bitmap* pStartBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Run/runStart.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	_pStartButton = new Button();
	r = _pStartButton->Construct(Rectangle(210, 900, 300, 300));
	AddControl(*_pStartButton);
	_pStartButton->SetActionId(ID_START);
	_pStartButton->AddActionEventListener(*this);
	_pStartButton->SetNormalBitmap(Point(0,0), *pStartBitmap);
	_pStartButton->SetNormalBackgroundBitmap(*pStartBitmap);

	/* EndButton */
	Bitmap* pEndBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Run/runEnd.png", BITMAP_PIXEL_FORMAT_ARGB8888);
	_pEndButton = new Button();
	r = _pEndButton->Construct(Rectangle(210, 900, 300, 300));
	AddControl(*_pEndButton);
	_pEndButton->SetActionId(ID_END);
	_pEndButton->AddActionEventListener(*this);
	_pEndButton->SetNormalBitmap(Point(0,0), *pEndBitmap);
	_pEndButton->SetNormalBackgroundBitmap(*pEndBitmap);
	_pEndButton->SetShowState(false);

	/* LeftButton */
	Bitmap* pLeftBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/leftArrow.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	_pToMainMenu = new Button();
	_pToMainMenu->Construct(Rectangle(0, 1130 ,150,90));
	AddControl(*_pToMainMenu);
	_pToMainMenu->AddActionEventListener(*this);
	_pToMainMenu->SetActionId(ID_TO_MENU);
	_pToMainMenu->SetNormalBitmap(Point(0,0),*pLeftBitmap);
	_pToMainMenu->SetNormalBackgroundBitmap(*pLeftBitmap);
	_pToMainMenu->SetShowState(true);

	delete pLeftBitmap;
	/* Fonts */
	_pLabelsFont = GetPavelFont(FONT_STYLE_BOLD,30 * SCALE_FACTOR);

	_pVariablesFont = new Font();
	r = _pVariablesFont->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf", FONT_STYLE_BOLD, 50 * SCALE_FACTOR);

	_pKmlFont = new Font();
	r = _pKmlFont->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf", FONT_STYLE_BOLD, 90 * SCALE_FACTOR);

	_pSpeedFont = new Font();
	r = _pSpeedFont->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf", FONT_STYLE_BOLD, 180 * SCALE_FACTOR);

	String str;
	Application* pApp = Application::GetInstance();

	pApp->GetAppResource()->GetString("IDS_TIME", str);

	/* Labels */
	_pTimeText = new EnrichedText();
	r = _pTimeText->Construct(Dimension(140 * SCALE_FACTOR, 50 * SCALE_FACTOR));
	_pTimeText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pTimeTextString = new TextElement();
	_pTimeTextString->Construct(str);
	_pTimeTextString->SetFont(*_pLabelsFont);
	_pTimeTextString->SetTextColor(Color::COLOR_WHITE);
	_pTimeText->Add(*_pTimeTextString);

	_pTime = new EnrichedText();
	r = _pTime->Construct(Dimension(230 * SCALE_FACTOR, 55 * SCALE_FACTOR));
	_pTime->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pTimeString = new TextElement();
	_pTimeString->Construct(L"00:00:00");
	_pTimeString->SetFont(*_pVariablesFont);
	_pTimeString->SetTextColor(Color::COLOR_WHITE);
	_pTime->Add(*_pTimeString);

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_CALORIES", str);

	_pCaloriesText = new EnrichedText();
	r = _pCaloriesText->Construct(Dimension(140 * SCALE_FACTOR, 50 * SCALE_FACTOR));
	_pCaloriesText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pCaloriesTextString = new TextElement();
	_pCaloriesTextString->Construct(str);
	_pCaloriesTextString->SetFont(*_pLabelsFont);
	_pCaloriesTextString->SetTextColor(Color::COLOR_WHITE);
	_pCaloriesText->Add(*_pCaloriesTextString);

	_pCalories = new EnrichedText();
	r = _pCalories->Construct(Dimension(230 * SCALE_FACTOR, 55 * SCALE_FACTOR));
	_pCalories->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pCaloriesString = new TextElement();
	_pCaloriesString->Construct(L"   0   ");
	_pCaloriesString->SetFont(*_pVariablesFont);
	_pCaloriesString->SetTextColor(Color::COLOR_WHITE);
	_pCalories->Add(*_pCaloriesString);

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_DISTANCE", str);

	_pDistanceText = new EnrichedText();
	r = _pDistanceText->Construct(Dimension(160 * SCALE_FACTOR, 50 * SCALE_FACTOR));
	_pDistanceText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pDistanceTextString = new TextElement();
	_pDistanceTextString->Construct(str);
	_pDistanceTextString->SetFont(*_pLabelsFont);
	_pDistanceTextString->SetTextColor(Color::COLOR_WHITE);
	_pDistanceText->Add(*_pDistanceTextString);

	_pDistance = new EnrichedText();
	r = _pDistance->Construct(Dimension(300 * SCALE_FACTOR, 55 * SCALE_FACTOR));
	_pDistance->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pDistanceString = new TextElement();
	_pDistanceString->Construct(L"  0 m  ");
	_pDistanceString->SetFont(*_pVariablesFont);
	_pDistanceString->SetTextColor(Color::COLOR_WHITE);
	_pDistance->Add(*_pDistanceString);

	_pKm = new EnrichedText();
	r = _pKm->Construct(Dimension(300 * SCALE_FACTOR, 100 * SCALE_FACTOR));
	_pKm->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pKMString = new TextElement();
	_pKMString->Construct(L"km/h");
	_pKMString->SetFont(*_pKmlFont);
	_pKMString->SetTextColor(Color::COLOR_WHITE);
	_pKm->Add(*_pKMString);

	_pSpeed = new EnrichedText();
	r = _pSpeed->Construct(Dimension(480 * SCALE_FACTOR, 300 * SCALE_FACTOR));
	_pSpeed->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pSpeedString = new TextElement();
	_pSpeedString->Construct(L" 0.0 ");
	_pSpeedString->SetFont(*_pSpeedFont);
	_pSpeedString->SetTextColor(Color::COLOR_WHITE);
	_pSpeed->Add(*_pSpeedString);

	Lock(0);
	Tizen::System::PowerManager::KeepScreenOnState(true,false);

	return r;
}

result RunForm::OnDraw() {
	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);

		pCanvas->DrawText(Point(50 * SCALE_FACTOR, 190 * SCALE_FACTOR), *_pTimeText);
		pCanvas->DrawText(Point(5 * SCALE_FACTOR, 225 * SCALE_FACTOR), *_pTime);

		pCanvas->DrawText(Point(290 * SCALE_FACTOR, 190 * SCALE_FACTOR), *_pCaloriesText);
		pCanvas->DrawText(Point(245 * SCALE_FACTOR, 225 * SCALE_FACTOR), *_pCalories);

		pCanvas->DrawText(Point(160 * SCALE_FACTOR, 545 * SCALE_FACTOR), *_pDistanceText);
		pCanvas->DrawText(Point(90 * SCALE_FACTOR, 580 * SCALE_FACTOR), *_pDistance);

		pCanvas->DrawText(Point(90 * SCALE_FACTOR, 450 * SCALE_FACTOR), *_pKm);
		pCanvas->DrawText(Point(0 * SCALE_FACTOR, 280 * SCALE_FACTOR), *_pSpeed);
		delete pCanvas;
	}
	return GetLastResult();
}

void RunForm::_updateWatch() {
	_watchText.Clear();
	_span = _pRun->GetTime();
	if (_span.GetMinutes() < 10)
		_watchText.Append("0");

	_watchText.Append(_span.GetMinutes());
	_watchText.Append(":");
	if (_span.GetSeconds() < 10)
		_watchText.Append("0");

	_watchText.Append(_span.GetSeconds());
	_watchText.Append(":");
	if (_span.GetMilliseconds() / 10 < 10)
		_watchText.Append("0");

	_watchText.Append(_span.GetMilliseconds() / 10);
	_pTimeString->SetText(_watchText);
	_timer.Start(INTERVAL);
}
void RunForm::_updateDistance() {
	_distance = (int) (_round(_pRun->GetDistance()));
	_DistanceText.Clear();
	_DistanceText.Append(_distance.ToString());
	_DistanceText.Append(" m");
	_pDistanceString->SetText(_DistanceText);
}

void RunForm::_updateSpeed() {
	_speed = _round100(_pRun->GetCurrentSpeed());
	_SpeedText.Clear();
	if (_speed < 10.0)
		_SpeedText.Append(" ");

	_SpeedText.Append(_speed);
	if (_speed == (int) _speed)
		_SpeedText.Append(".0 ");
	else if(_SpeedText.GetLength()!=4) _SpeedText.Append(" ");
	_pSpeedString->SetText(_SpeedText);
}
void RunForm::_updateCalories() {
	_calories = _pRun->GetCalories();
	_CaloriesText.Clear();
	_CaloriesText.Append(_calories.ToString());
	_pCaloriesString->SetText(_CaloriesText);
}

void RunForm::OnTimerExpired(Tizen::Base::Runtime::Timer & timer) {
	_updateWatch();
	_updateSpeed();
	_updateDistance();
	_updateCalories();

	RequestRedraw(true);
}

float RunForm::_round100(float f) {
	// Zaokraglamy do czesci dziesietnych
	f *= 100;
	f += 0.5;
	f = floorf(f);
	f /= 100;
	return f;
}

void RunForm::SendSomethingToForm(int something) {

#ifdef ENABLE_SATELITES_NUMBER
	if (_signalSearching != null) {
		if (_pNSatelitesLabel != null) {
			_pNSatelitesLabel->SetText(Integer(something).ToString());
			_pNSatelitesLabel->RequestRedraw(true);
		}
	}
#endif //ENABLE_SATELITES_NUMBER
}

float RunForm::_round(float f) {
	// Zaokraglamy do calosci
	f += 0.5;
	f = floorf(f);
	return f;
}

void RunForm::Unlock(int argf) {
	if (_signalSearching != null) {
		_signalSearching->SetShowState(false);

		if (null != _signalSearching) {
			delete _signalSearching;
			_signalSearching = null;
		}
	}
}

void RunForm::vibrate_on_end() {
	Vibrator vibe;
	vibe.Construct();
	vibe.Start(1500, 100);
	Tizen::Base::Runtime::Thread::Sleep (1500);

}

void RunForm::Lock(int argf) {
	AppLog("Lock");
	switch (argf) {
	case LOCK_REASON_NO_LOCATION_FOUND:
		if (_pRun->IsRunning() == true) {
			vibrate_on_end();
			OnActionPerformed(*this, ID_END);

		} else {
			_signalSearching = new Popup();
			_signalSearching->Construct("IDP_POPUP1");
			_signalSearching->Show();
			_pCancelButton
					= static_cast<Button*> (_signalSearching->GetControl(L"IDC_BUTTON_1"));
					if (null != _pCancelButton) {
						_pCancelButton->SetActionId(ID_CANCEL);
						_pCancelButton->AddActionEventListener(*this);
					}
#ifdef ENABLE_SATELITES_NUMBER
					_pNSatelitesLabel = static_cast<Label*> (_signalSearching->GetControl(L"IDC_LABEL4"));
#endif //ENABLE_SATELITES_NUMBER

		}
			break;

			case LOCK_REASON_SIGNAL_LOST:
			{
		vibrate_on_end();
				OnActionPerformed(*this, ID_END);

			}
			break;

		}
}

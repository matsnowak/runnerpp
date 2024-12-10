/*
 * MainMenuForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "MainMenuForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;
using namespace Tizen::System;

MainMenuForm::MainMenuForm() :
	_pBackground(null)
#if defined(ADS)
	,_pAd(null),
	_pExit(null)
#endif
{}

MainMenuForm::~MainMenuForm() {
	if (null != _pBackground) {
		delete _pBackground;
		_pBackground = null;
	}
}

result MainMenuForm::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		delete pCanvas;
	}
	return r;
}

bool MainMenuForm::Initialize(void) {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"MainMenu");
	return true;
}

result MainMenuForm::OnInitializing(void) {
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	Bitmap* pRunBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/MainMenu/MMrun.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Bitmap* pStatsBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/MainMenu/MMStats.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Bitmap* pOptionsBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/MainMenu/MMoptions.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Bitmap* pInfoBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/MainMenu/MMinfo.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Bitmap* pExitBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/MainMenu/MMexit.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pRun = new Button();
	pRun->Construct(Rectangle(30, 250 ,300,300));
	AddControl(*pRun);
	pRun->SetActionId(ID_RUN);
	pRun->AddActionEventListener(*this);
	pRun->SetNormalBitmap(Point(0,0),*pRunBitmap);
	pRun->SetNormalBackgroundBitmap(*pRunBitmap);

	Button *pStats = new Button();
	pStats->Construct(Rectangle(390, 250,300,300));
	AddControl(*pStats);
	pStats->SetActionId(ID_STATS);
	pStats->AddActionEventListener(*this);
	pStats->SetNormalBitmap(Point(0,0),*pStatsBitmap);
	pStats->SetNormalBackgroundBitmap(*pStatsBitmap);

	Button *pOptions = new Button();
	pOptions->Construct(Rectangle(30, 630,300,300));
	AddControl(*pOptions);
	pOptions->SetActionId(ID_OPTIONS);
	pOptions->AddActionEventListener(*this);
	pOptions->SetNormalBitmap(Point(0,0),*pOptionsBitmap);
	pOptions->SetNormalBackgroundBitmap(*pOptionsBitmap);

	Button *pInfo = new Button();
	pInfo->Construct(Rectangle(390, 630,300,300));
	AddControl(*pInfo);
	pInfo->SetActionId(ID_INFO);
	pInfo->AddActionEventListener(*this);
	pInfo->SetNormalBitmap(Point(0,0),*pInfoBitmap);
	pInfo->SetNormalBackgroundBitmap(*pInfoBitmap);

	_pExit = new Button();
	_pExit->Construct(Rectangle(247,1000 ,225,150));
	AddControl(*_pExit);
	_pExit->SetActionId(ID_EXIT);
	_pExit->AddActionEventListener(*this);
	_pExit->SetNormalBitmap(Point(0,0),*pExitBitmap);
	_pExit->SetNormalBackgroundBitmap(*pExitBitmap);
	_pExit->SetShowState(true);

	AppLog("%d %d",GetClientAreaBounds().width,GetClientAreaBounds().height);

	delete pRunBitmap;
	delete pStatsBitmap;
	delete pOptionsBitmap;
	delete pInfoBitmap;
	delete pExitBitmap;

	return GetLastResult();//to moze byc klopotliwe,obadac
}

result MainMenuForm::OnTerminating(void) {
	if (null != _pBackground) {
		delete _pBackground;
		_pBackground = null;
	}
	return E_SUCCESS;
}

void MainMenuForm::OnActionPerformed(const Tizen::Ui::Control& source,
		int actionId) {
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	//AppLog("ActionPerformance");
	switch (actionId) {
	case ID_RUN:
		if (pFormMgr != null)
			CheckGpsState();
			if (_isGpsEnabled == true) {
				pFormMgr->SendUserEvent(FormMgr::REQUEST_RUNFORM, null);
			} else {
				AppResource *pAppRes = Application::GetInstance()->GetAppResource();
				String msgTitle, msgText;
				if (pAppRes != null) {
					pAppRes->GetString("IDS_MSG_TITLE", msgTitle);
					pAppRes->GetString("IDS_MSG_TEXT", msgText);

				}
				MessageBox *msg = new MessageBox();
				msg->Construct(msgTitle, msgText, MSGBOX_STYLE_OK, 0);
				int modalResult = 0;
				msg->ShowAndWait(modalResult);
				if (msg != null) {
					delete msg;
					msg = null;
				}
			}
		break;
	case ID_STATS:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_STATSFORM, null);
		break;
	case ID_OPTIONS:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_OPTIONSFORM, null);
		break;
	case ID_INFO:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_ABOUTFORM, null);
		break;
	case ID_EXIT:
		Application::GetInstance()->Terminate();
		break;
	}
}

result MainMenuForm::CheckGpsState() {
	bool value;
	result r = E_SUCCESS;
	String key(L"GPSEnabled");

	r = Tizen::System::SettingInfo::GetValue(key, value);
	TryCatch(r == E_SUCCESS, , "MySettingInfo: To get a value is failed");

	_isGpsEnabled = value;

	return E_SUCCESS;

	CATCH:
	return r;
}

#if defined(ADS)
void
MainMenuForm::OnComunicationError(result r, const Tizen::Base::String& desc)
{
	if (r == Smaato::AdSDK::AdContainer::E_NO_AD_AVAILABLE)
	{
		// Currently no ad available
		AppLog("Currently no ad available");
	}
	else
	{

		// Communication error
		AppLog("Comunication error occured: %S", desc.GetPointer());
	}
}

void
MainMenuForm::OnNewAdAvailable(Smaato::AdSDK::AdContainer& adContainer)
{
	_pExit->SetShowState(false);
	_pAd->SetShowState(true);
	RequestRedraw();

}
#endif

/*
 * SavingFormCF.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "SavingFormCF.h"
#include "DatabaseScanner.h"
#include "RunnerPP.h"
#include "Utils.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

SavingFormCF::SavingFormCF() :
	_pBackground(null),
	_pTimer(null)
{
}

SavingFormCF::~SavingFormCF() {
}

result SavingFormCF::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);

		Tizen::Graphics::Font* font = GetPavelFont(FONT_STYLE_PLAIN,100);

		EnrichedText text;
		text.Construct(Dimension(400, 150));
		text.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		TextElement napis;

		String str;
		Application* pApp = Application::GetInstance();
		pApp->GetAppResource()->GetString("IDS_SAVING",str);


		napis.Construct(str);
		napis.SetFont(*font);
		napis.SetTextColor(Color::COLOR_WHITE);
		text.Add(napis);
		pCanvas->DrawText(Point(40, 350), text);

		delete font;
		delete pCanvas;
	}

	_pTimer = new Tizen::Base::Runtime::Timer();
	_pTimer->Construct(*this);
	_pTimer->Start(50);
	return r;

}

bool SavingFormCF::Initialize(void) {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"SavingFormCF");
	return true;
}

result SavingFormCF::OnInitializing(void) {
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);


	return E_SUCCESS;//moze byc klopotliwe ?
}

result SavingFormCF::OnTerminating(void) {
	if(_pBackground!=null)
		delete _pBackground;
	if(_pTimer)
		delete _pTimer;
	return E_SUCCESS;
}

void
SavingFormCF::OnTimerExpired (Tizen::Base::Runtime::Timer &timer){
	DatabaseScanner sc;
	sc.Construct();
	RunnerPP *run = static_cast<RunnerPP* > (Application::GetInstance());
	while(!sc.SaveD(run->GetTrack())){
		MessageBox mesBox;
		String top,message;
		AppResource *pAppResource = Application::GetInstance()->GetAppResource();
		if (pAppResource) {
			pAppResource->GetString("IDS_ERROR", top);
			pAppResource->GetString("IDS_ERROR_MSG_ZAPIS_DO_BAZY", message);
		}
		mesBox.Construct(top,message,MSGBOX_STYLE_YESNO,30000);
		int i;
		mesBox.ShowAndWait(i);
		if(i==MSGBOX_RESULT_NO) break;
	}
	run->TrackSaved();
	run->ClearTrack();

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));

	if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_CHOOSETRACKFORM, null);

}


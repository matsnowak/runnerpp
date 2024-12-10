/*
 * TrackStatsForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "TrackStatsForm.h"
#include "FormMgr.h"
#include "RunnerPP.h"
#include "Utils.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

TrackStatsForm::TrackStatsForm():
		_pBackground(null),
		_pTime(null),
		_pDistance(null),
		_pCalories(null),
		_pMaxSpeed(null),
		_pAvrageSpeed(null),
		_pFormName(null)
{
}

TrackStatsForm::~TrackStatsForm()
{
}

result
TrackStatsForm::OnDraw(void)
{
	result r = E_SUCCESS;
	RunnerPP* run =static_cast<RunnerPP*>(Application::GetInstance());
	Track* pTrack=run->GetTrack();

	Canvas* pCanvas = GetCanvasN();
	if(pCanvas != null)
	{
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0,(150 * SCALE_FACTOR) + 30),*_pFormName);
		pCanvas->DrawText(Point(0,235 * SCALE_FACTOR),*_pTime);
		pCanvas->DrawText(Point(0,330 * SCALE_FACTOR),*_pDistance);
		pCanvas->DrawText(Point(0,450 * SCALE_FACTOR),*_pCalories);
		pCanvas->DrawText(Point(0,540 * SCALE_FACTOR),*_pMaxSpeed);
		pCanvas->DrawText(Point(0,630 * SCALE_FACTOR),*_pAvrageSpeed);
		//tu sobie porysujemy ;P

		EnrichedText text;
		text.Construct(Dimension(480 * SCALE_FACTOR, 50 * SCALE_FACTOR));
		text.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		text.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
		text.SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
		text.SetTextAbbreviationEnabled(true);

		Font font48;
		font48.Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf",FONT_STYLE_PLAIN,48 * SCALE_FACTOR);

		Font font100;
		font100.Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf",FONT_STYLE_PLAIN,100 * SCALE_FACTOR);

		String display;

		display.Append(pTrack->GetTotalTime().GetHours());
		display.Append(L" h ");
		display.Append(pTrack->GetTotalTime().GetMinutes());
		display.Append(L" m ");
		display.Append(pTrack->GetTotalTime().GetSeconds());
		display.Append(L" s");

		TextElement textTotalTime;
		textTotalTime.Construct(display);
		textTotalTime.SetTextColor(Color::COLOR_WHITE);
		textTotalTime.SetFont(font48);

		text.RemoveAllTextElements(false);
		text.Add(textTotalTime);
		pCanvas->DrawText(Point(0,275 * SCALE_FACTOR), text);


		EnrichedText textBig;
		textBig.Construct(Dimension(480 * SCALE_FACTOR, 100 * SCALE_FACTOR));
		textBig.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		textBig.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
		textBig.SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
		textBig.SetTextAbbreviationEnabled(true);

		display.Clear();
		display.Append((float)pTrack->GetDistance()/1000);
		display.Append(L" km");

		TextElement textDistance;
		textDistance.Construct(display);
		textDistance.SetTextColor(Color::COLOR_WHITE);
		textDistance.SetFont(font100);

		textBig.Add(textDistance);
		pCanvas->DrawText(Point(0,360 * SCALE_FACTOR), textBig);

		display.Clear();
		display.Append(pTrack->GetCalories());
		display.Append(L" kcal");

		TextElement textCalories;
		textCalories.Construct(display);
		textCalories.SetTextColor(Color::COLOR_WHITE);
		textCalories.SetFont(font48);

		text.RemoveAllTextElements(false);
		text.Add(textCalories);
		pCanvas->DrawText(Point(0,480 * SCALE_FACTOR), text);


		display.Clear();
		display.Format(6,L"%f",pTrack->GetMaxSpeed());
		display.Append(L" km/h");

		TextElement textMaxSpeed;
		textMaxSpeed.Construct(display);
		textMaxSpeed.SetTextColor(Color::COLOR_WHITE);
		textMaxSpeed.SetFont(font48);

		text.RemoveAllTextElements(false);
		text.Add(textMaxSpeed);
		pCanvas->DrawText(Point(0,580 * SCALE_FACTOR), text);

		display.Clear();
		display.Format(6,L"%f",pTrack->GetAvrageSpeed());
		display.Append(L" km/h");

		TextElement textAvrageSpeed;
		textAvrageSpeed.Construct(display);
		textAvrageSpeed.SetTextColor(Color::COLOR_WHITE);
		textAvrageSpeed.SetFont(font48);

		text.RemoveAllTextElements(false);
		text.Add(textAvrageSpeed);
		pCanvas->DrawText(Point(0,670 * SCALE_FACTOR), text);

		delete pCanvas;
	}

	return r;

}

bool
TrackStatsForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	SetName(L"TrackStatsForm");
	return true;
}

void TrackStatsForm::CreateText(String id, EnrichedText *& eText, Font *& pFont)
{
    String str;
    Application *pApp = Application::GetInstance();
	eText->Construct(Dimension(480 * SCALE_FACTOR, 40 * SCALE_FACTOR));
	eText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	eText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	eText->SetTextWrapStyle(TEXT_WRAP_NONE);

    pApp->GetAppResource()->GetString(id, str);
    TextElement* text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    eText->Add(*text);
}

void TrackStatsForm::CreateTexts()
{
    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,35 * SCALE_FACTOR);

    _pTime = new EnrichedText();
    CreateText("IDS_TIME_SMALL", _pTime, pFont);

    _pDistance = new EnrichedText();
    CreateText("IDS_DISTANCE_SMALL", _pDistance, pFont);

    _pCalories = new EnrichedText();
    CreateText("IDS_CALORIES_SMALL", _pCalories, pFont);

    _pMaxSpeed = new EnrichedText();
    CreateText("IDS_MAX_SPEED_SMALL", _pMaxSpeed, pFont);

    _pAvrageSpeed = new EnrichedText();
    CreateText("IDS_AVRAGE_SPEED_SMALL", _pAvrageSpeed, pFont);

    delete pFont;
}

result
TrackStatsForm::OnInitializing(void)
{
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	Bitmap* pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(380, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
	delete pToMainMenuBitmap;

	Bitmap* pToChooseFormBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toChooseForm.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToChooseForm = new Button();
	pToChooseForm->Construct(Rectangle(190, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToChooseForm);
	pToChooseForm->AddActionEventListener(*this);
	pToChooseForm->SetActionId(ID_TO_CHOOSEFORM);
	pToChooseForm->SetNormalBitmap(Point(0,0),*pToChooseFormBitmap);
	pToChooseForm->SetNormalBackgroundBitmap(*pToChooseFormBitmap);
	delete pToChooseFormBitmap;

	Bitmap* pRightArrowBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/rightArrow.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pRightArrow = new Button();
	pRightArrow->Construct(Rectangle(GetClientAreaBounds().width-150, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pRightArrow);
	pRightArrow->AddActionEventListener(*this);
	pRightArrow->SetActionId(ID_RIGHT_ARROW);
	pRightArrow->SetNormalBitmap(Point(0,0),*pRightArrowBitmap);
	pRightArrow->SetNormalBackgroundBitmap(*pRightArrowBitmap);
	delete pRightArrowBitmap;

	Bitmap* pSaveBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/TrackStats/saveCoordinates.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pSave = new Button();
	pSave->Construct(Rectangle(0, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pSave);
	pSave->AddActionEventListener(*this);
	pSave->SetActionId(ID_SAVE);
	pSave->SetNormalBitmap(Point(0,0),*pSaveBitmap);
	pSave->SetNormalBackgroundBitmap(*pSaveBitmap);
	delete pSaveBitmap;

    CreateTexts();

    _pFormName = new EnrichedText();
    _pFormName->Construct(Dimension(480 * SCALE_FACTOR, 100 * SCALE_FACTOR));
    _pFormName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    _pFormName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
    _pFormName->SetTextWrapStyle(TEXT_WRAP_NONE);

    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,50 * SCALE_FACTOR);


    String str;
    Application* pApp = Application::GetInstance();
    pApp->GetAppResource()->GetString("IDS_TRACK_STATS", str);
    TextElement *text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    _pFormName->Add(*text);
    delete pFont;

	return GetLastResult();//moze byc klopotliwe ?
}

result
TrackStatsForm::OnTerminating(void)
{
	if(_pBackground!=null)
		delete _pBackground;
	if(_pTime){
		_pTime->RemoveAllTextElements(true);
		delete _pTime;
	}
	if(_pDistance){
		_pDistance->RemoveAllTextElements(true);
		delete _pDistance;
	}
	if(_pCalories){
		_pCalories->RemoveAllTextElements(true);
		delete _pCalories;
	}
	if(_pMaxSpeed){
		_pMaxSpeed->RemoveAllTextElements(true);
		delete _pMaxSpeed;
	}
	if(_pAvrageSpeed){
		_pAvrageSpeed->RemoveAllTextElements(true);
		delete _pAvrageSpeed;
	}
	if(_pFormName){
		_pFormName->RemoveAllTextElements(true);
		delete _pFormName;
	}
	return E_SUCCESS;
}

void
TrackStatsForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId){
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_CHOOSEFORM:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_EXIT_TO_CHOOSEFORM, null);
		break;
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_EXIT_TO_MAINMENU, null);
		break;
	case ID_RIGHT_ARROW:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_GRAPHFORM, null);
		break;
	case ID_SAVE:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_SAVEFORM, null);
		break;

	default:
		break;
	}
}

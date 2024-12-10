/*
 * StatsForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "StatsForm.h"
#include "DatabaseScanner.h"
#include "Utils.h"
#include "IBaseForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

StatsForm::StatsForm():
		_pBackground(null),
		_pFormName(null),
		_pTotalTime(null),
		_pTotalDistance(null),
		_pTotalCalories(null),
		_pMaxSpeed(null),
		_pAvrageSpeed(null),
		_pLongestRun(null),
		_pFurthestRun(null)
{
}

StatsForm::~StatsForm()
{
}

result
StatsForm::OnDraw(void)
{
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if(pCanvas != null)
	{
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0,150 * SCALE_FACTOR), *_pFormName);
		pCanvas->DrawText(Point(0,235 * SCALE_FACTOR),*_pTotalDistance);
		pCanvas->DrawText(Point(0,310 * SCALE_FACTOR),*_pTotalTime);
		pCanvas->DrawText(Point(0,385 * SCALE_FACTOR),*_pTotalCalories);
		pCanvas->DrawText(Point(0,455 * SCALE_FACTOR),*_pLongestRun);
		pCanvas->DrawText(Point(0,525 * SCALE_FACTOR),*_pFurthestRun);
		pCanvas->DrawText(Point(0,600 * SCALE_FACTOR),*_pAvrageSpeed);
		pCanvas->DrawText(Point(0,670 * SCALE_FACTOR),*_pMaxSpeed);

		DatabaseScanner* sc;
		sc=new DatabaseScanner;
		sc->Construct();

		float distance=0.f;
		TimeSpan time(0);
		float calories=0.0f;
		float avrageSpeed=0.0f;
		float furthestRun=0.0f;
		TimeSpan longestRun(0);
		float maxSpeed=0.0f;
		if(!sc->Empty()){
			distance=(float)sc->GetTotalDistance()/1000;
			time=sc->GetTotalTime();
			calories=sc->GetCalories();
			avrageSpeed=sc->GetAvrageSpeed();
			furthestRun=(float)sc->GetFurthestRun()/1000;
			longestRun=sc->GetLongestRun();
			maxSpeed=sc->GetMaxSpeed();
		}
		delete sc;


		EnrichedText text;
		text.Construct(Dimension(480 * SCALE_FACTOR, 50 * SCALE_FACTOR));
		text.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
		text.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
		text.SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
		text.SetTextAbbreviationEnabled(true);

		Font* font = new Font();
		font->Construct(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Fonts/geosans.ttf",FONT_STYLE_PLAIN,30 * SCALE_FACTOR);

		String display;
		//distance
		display.Append(distance);
		display.Append(L" km");
		TextElement textDistance;
		textDistance.Construct(display);
		textDistance.SetTextColor(Color::COLOR_WHITE);
		textDistance.SetFont(*font);

		text.Add(textDistance);
		pCanvas->DrawText(Point(0,268 * SCALE_FACTOR), text);
		//time
		display.Clear();
		display.Append(time.GetHours());
		display.Append(L" h ");
		display.Append(time.GetMinutes());
		display.Append(L" m ");
		display.Append(time.GetSeconds());
		display.Append(L" s");

		TextElement textTotalTime;
		textTotalTime.Construct(display);
		textTotalTime.SetTextColor(Color::COLOR_WHITE);
		textTotalTime.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textTotalTime);
		pCanvas->DrawText(Point(0,338 * SCALE_FACTOR), text);
		//calories
		display.Clear();
		display.Append(calories);
		display.Append(L" kcal");

		TextElement textCalories;
		textCalories.Construct(display);
		textCalories.SetTextColor(Color::COLOR_WHITE);
		textCalories.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textCalories);
		pCanvas->DrawText(Point(0,412 * SCALE_FACTOR), text);
		//najdluzszy bieg [km]
		display.Clear();
		display.Append(furthestRun);
		display.Append(L" km");

		TextElement textFurthestRun;
		textFurthestRun.Construct(display);
		textFurthestRun.SetTextColor(Color::COLOR_WHITE);
		textFurthestRun.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textFurthestRun);
		pCanvas->DrawText(Point(0,485 * SCALE_FACTOR), text);
		//najdluzszy bieg [sek]
		display.Clear();
		display.Append(longestRun.GetHours());
		display.Append(L" h ");
		display.Append(longestRun.GetMinutes());
		display.Append(L" m ");
		display.Append(longestRun.GetSeconds());
		display.Append(L" s");

		TextElement textLongestRun;
		textLongestRun.Construct(display);
		textLongestRun.SetTextColor(Color::COLOR_WHITE);
		textLongestRun.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textLongestRun);
		pCanvas->DrawText(Point(0,558 * SCALE_FACTOR), text);
		//srednia predkosc
		display.Clear();
		display.Format(6,L"%f",avrageSpeed);
		display.Append(L" km/h");

		TextElement textAvrageSpeed;
		textAvrageSpeed.Construct(display);
		textAvrageSpeed.SetTextColor(Color::COLOR_WHITE);
		textAvrageSpeed.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textAvrageSpeed);
		pCanvas->DrawText(Point(0,630 * SCALE_FACTOR), text);

		//srednia predkosc
		display.Clear();
		display.Format(6,L"%f",maxSpeed);
		display.Append(L" km/h");

		TextElement textMaxSpeed;
		textMaxSpeed.Construct(display);
		textMaxSpeed.SetTextColor(Color::COLOR_WHITE);
		textMaxSpeed.SetFont(*font);

		text.RemoveAllTextElements(false);
		text.Add(textMaxSpeed);
		pCanvas->DrawText(Point(0,702 * SCALE_FACTOR), text);

		delete font;
		delete pCanvas;
	}

	return r;
	return E_SUCCESS;
}

bool
StatsForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	SetName(L"StatsForm");
	return true;
}

result
StatsForm::OnInitializing(void)
{
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);


	Bitmap* pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(290, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
	delete pToMainMenuBitmap;

	Bitmap* pToChooseTrackBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toChooseForm.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToChooseTrack = new Button();
	pToChooseTrack->Construct(Rectangle(GetClientAreaBounds().width-150, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToChooseTrack);
	pToChooseTrack->AddActionEventListener(*this);
	pToChooseTrack->SetActionId(ID_TO_CHOOSE_TRACK);
	pToChooseTrack->SetNormalBitmap(Point(0,0),*pToChooseTrackBitmap);
	pToChooseTrack->SetNormalBackgroundBitmap(*pToChooseTrackBitmap);
	delete pToChooseTrackBitmap;

	_pFormName = new EnrichedText();
	_pFormName->Construct(Dimension(480 * SCALE_FACTOR, 100 * SCALE_FACTOR));
	_pFormName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pFormName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	_pFormName->SetTextWrapStyle(TEXT_WRAP_NONE);

	Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,50 * SCALE_FACTOR);

	String str;
	Application* pApp = Application::GetInstance();

	pApp->GetAppResource()->GetString("IDS_STATS", str);
	TextElement *text = new TextElement();
	text->Construct(str);
	text->SetFont(*pFont);
	text->SetTextColor(Color::COLOR_WHITE);
	_pFormName->Add(*text);

	delete pFont;

	CreateTexts();

	return E_SUCCESS;//moze byc klopotliwe ?
}

result
StatsForm::OnTerminating(void)
{
	if(_pBackground!=null)
		delete _pBackground;
	if(_pFormName != null){
		_pFormName->RemoveAllTextElements(true);
		delete _pFormName;
	}
	if(_pTotalTime){
		_pTotalTime->RemoveAllTextElements(true);
		delete _pTotalTime;
	}
	if(_pTotalDistance){
		_pTotalDistance->RemoveAllTextElements(true);
		delete _pTotalDistance;
	}
	if(_pTotalCalories){
		_pTotalCalories->RemoveAllTextElements(true);
		delete _pTotalCalories;
	}
	if(_pLongestRun){
		_pLongestRun->RemoveAllTextElements(true);
		delete _pLongestRun;
	}
	if(_pFurthestRun){
		_pFurthestRun->RemoveAllTextElements(true);
		delete _pFurthestRun;
	}
	if(_pMaxSpeed){
		_pMaxSpeed->RemoveAllTextElements(true);
		delete _pMaxSpeed;
	}
	if(_pAvrageSpeed){
		_pAvrageSpeed->RemoveAllTextElements(true);
		delete _pAvrageSpeed;
	}

	return E_SUCCESS;
}

void
StatsForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId){
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		break;
	case ID_TO_CHOOSE_TRACK:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_CHOOSETRACKFORM, null);
		break;
	default:
		break;
	}

}

void StatsForm::CreateText(String id, EnrichedText *& eText, Font *& pFont)
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

void StatsForm::CreateTexts()
{
    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,35 * SCALE_FACTOR);

    _pTotalTime = new EnrichedText();
    CreateText("IDS_TOTAL_TIME_SMALL", _pTotalTime, pFont);

    _pTotalDistance = new EnrichedText();
    CreateText("IDS_TOTAL_DISTANCE_SMALL", _pTotalDistance, pFont);

    _pTotalCalories = new EnrichedText();
    CreateText("IDS_CALORIES_SMALL", _pTotalCalories, pFont);

    _pLongestRun = new EnrichedText();
    CreateText("IDS_LONGEST_RUN_SMALL", _pLongestRun, pFont);

    _pFurthestRun = new EnrichedText();
    CreateText("IDS_FURTHEST_RUN_SMALL", _pFurthestRun, pFont);

    _pMaxSpeed = new EnrichedText();
    CreateText("IDS_TOTAL_MAX_SPEED_SMALL", _pMaxSpeed, pFont);

    _pAvrageSpeed = new EnrichedText();
    CreateText("IDS_TOTAL_AVRAGE_SPEED_SMALL", _pAvrageSpeed, pFont);

    delete pFont;
}

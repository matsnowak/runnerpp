/*
 * AboutForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "IntroForm.h"
#include "Options.h"
#include "Utils.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

IntroForm::IntroForm() :
	_pBackground(null) {
}

IntroForm::~IntroForm() {
}

result IntroForm::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0,(150 * SCALE_FACTOR) + 30),*_pGreeting);
		pCanvas->DrawText(Point(0,250 * SCALE_FACTOR),*_pWeightAndHeight);
		pCanvas->DrawText(Point(40 * SCALE_FACTOR,(520 * SCALE_FACTOR) + 30),*_pInformation);
		delete pCanvas;
	}

	return r;

}

bool IntroForm::Initialize(void) {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"IntroForm");
	return true;
}

void IntroForm::WelcomeText()
{
	String str;
	Application* pApp = Application::GetInstance();
    _pGreeting = new EnrichedText();
    _pGreeting->Construct(Dimension(480 * SCALE_FACTOR, 100 * SCALE_FACTOR));
    _pGreeting->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    _pGreeting->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
    _pGreeting->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN, 50 * SCALE_FACTOR);
    pApp->GetAppResource()->GetString("IDS_GREETING", str);
    TextElement *text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    _pGreeting->Add(*text);
    delete pFont;
}

result IntroForm::OnInitializing(void) {
	_pOptions= new Options();
	_pOptions->Construct();
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	String str;
	Application* pApp = Application::GetInstance();

	Bitmap* pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Intro/ok.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(165 * SCALE_FACTOR, (612 * SCALE_FACTOR) + 50 ,150 * SCALE_FACTOR,150 * SCALE_FACTOR));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);

	delete pToMainMenuBitmap;

	_pWeightImput = new Slider();
	pApp->GetAppResource()->GetString("IDS_WEIGHT", str);
	str.Append(" [kg] :");

	_pWeightImput->Construct(Rectangle(40 * SCALE_FACTOR, 270 * SCALE_FACTOR, 400 * SCALE_FACTOR, 100 * SCALE_FACTOR), BACKGROUND_STYLE_NONE, true, 10, 200);
	_pWeightImput->SetTitleText(str);
	_pWeightImput->SetTitleTextColor(Color::COLOR_WHITE);
	_pWeightImput->SetValue(_pOptions->GetPersonalities_weight());
	_pWeightImput->AddAdjustmentEventListener(*this);

	AddControl(*_pWeightImput);

	_pHeightImput = new Slider();

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_HEIGHT", str);
	str.Append(" [cm] :");

	_pHeightImput->Construct(Rectangle(40 * SCALE_FACTOR, 370 * SCALE_FACTOR, 400 * SCALE_FACTOR, 100 * SCALE_FACTOR), BACKGROUND_STYLE_NONE,true, 100, 230);
	_pHeightImput->SetTitleText(str);
	_pHeightImput->SetTitleTextColor(Color::COLOR_WHITE);
	_pHeightImput->SetValue(_pOptions->GetPersonalities_height());
	_pHeightImput->AddAdjustmentEventListener(*this);

	AddControl(*_pHeightImput);
    WelcomeText();


    _pWeightAndHeight = new EnrichedText();
    _pWeightAndHeight->Construct(Dimension(480 * SCALE_FACTOR, 50 * SCALE_FACTOR));
    _pWeightAndHeight->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    _pWeightAndHeight->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
    _pWeightAndHeight->SetTextWrapStyle(TEXT_WRAP_NONE);

    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN, 30 * SCALE_FACTOR);


    pApp->GetAppResource()->GetString("IDS_IMPUT_INFO", str);
    TextElement *text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    _pWeightAndHeight->Add(*text);

    _pInformation = new EnrichedText();
    _pInformation->Construct(Dimension(400 * SCALE_FACTOR, 150 * SCALE_FACTOR));
    _pInformation->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    _pInformation->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
    _pInformation->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);


    pApp->GetAppResource()->GetString("IDS_INFORMATION", str);
    text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    _pInformation->Add(*text);

    delete pFont;


    return GetLastResult();
}

result IntroForm::OnTerminating(void) {
	if(_pBackground!=null)
		delete _pBackground;
	if(_pOptions!=null)
		delete _pOptions;
	if(_pGreeting){
		_pGreeting->RemoveAllTextElements(true);
		delete _pGreeting;
	}
	if(_pWeightAndHeight){
		_pWeightAndHeight->RemoveAllTextElements(true);
		delete _pWeightAndHeight;
	}
	if(_pInformation){
		_pInformation->RemoveAllTextElements(true);
		delete _pInformation;
	}
	return E_SUCCESS;
}

void IntroForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		break;

	default:
		break;
	}
}

void
IntroForm::OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment){
	if(&source==_pHeightImput) _pOptions->SetPersonalities_height(adjustment);
	else if(&source==_pWeightImput) _pOptions->SetPersonalities_weight(adjustment);
}

/*
 * OptionsForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "OptionsForm.h"
#include "DatabaseScanner.h"
#include "Utils.h"
#include <FBase.h>
#include <FGraphics.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

OptionsForm::OptionsForm():
		_pBackground(null),
		_pFormName(null)
{
}

OptionsForm::~OptionsForm()
{
}

result
OptionsForm::OnDraw(void)
{
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if(pCanvas != null)
	{
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0,150), *_pFormName);
		delete pCanvas;
	}
	_pScrollPanel->RequestRedraw();
	return r;

}

bool
OptionsForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	SetName(L"OptionsForm");
	SetBackgroundColor(Color(0,0,0,0));
	return true;
}

result
OptionsForm::OnInitializing(void)
{
	_pOptions= new Options();
	_pOptions->Construct();
	_showVibe=_pOptions->GetVibe_isActivated();
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	String str;
	Application* pApp = Application::GetInstance();

	Bitmap* pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(290, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
	delete pToMainMenuBitmap;


	_pScrollPanel = new ScrollPanel();
	_pScrollPanel->Construct(Rectangle(40, 200, 400, 500));

	// Poczatek element�w na ScrollPanel

	_pWeightImput = new Slider();

	pApp->GetAppResource()->GetString("IDS_WEIGHT", str);
	str+=" [kg] :";

	_pWeightImput->Construct(Rectangle(0, 0, 400, 100), BACKGROUND_STYLE_NONE, true, 10, 200);
	_pWeightImput->SetTitleText(str);
	_pWeightImput->SetTitleTextColor(Color::COLOR_WHITE);
	_pWeightImput->SetValue(_pOptions->GetPersonalities_weight());
	_pWeightImput->AddAdjustmentEventListener(*this);

	_pScrollPanel->AddControl(*_pWeightImput);

	_pHeightImput = new Slider();

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_HEIGHT", str);
	str+=" [cm] :";
	_pHeightImput->Construct(Rectangle(0, 140, 400, 75), BACKGROUND_STYLE_NONE,true, 100, 230);
	_pHeightImput->SetTitleText(str);
	_pHeightImput->SetTitleTextColor(Color::COLOR_WHITE);
	_pHeightImput->SetValue(_pOptions->GetPersonalities_height());
	_pHeightImput->AddAdjustmentEventListener(*this);

	_pScrollPanel->AddControl(*_pHeightImput);

	_pVibe = new Button();
	_pVibe->Construct(Rectangle(0,260,400,100),L"");
	_pVibe->AddActionEventListener(*this);
	_pVibe->SetActionId(ID_ON_OFF);

	_pScrollPanel->AddControl(*_pVibe);

	CreateOnOffBitmaps();

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_VIBRATION_LEVEL", str);
	str+=" :";

	_pVibeImputLevel= new Slider();
	_pVibeImputLevel->Construct(Rectangle(0, 380, 400, 75),BACKGROUND_STYLE_NONE,true,1,100);
	_pVibeImputLevel->SetValue(_pOptions->GetVibe_vibrationLevel());
	_pVibeImputLevel->SetTitleText(str);
	_pVibeImputLevel->SetTitleTextColor(Color::COLOR_WHITE);
	_pVibeImputLevel->AddAdjustmentEventListener(*this);
	_pVibeImputLevel->SetShowState(false);

	_pScrollPanel->AddControl(*_pVibeImputLevel);

	str.Clear();
	pApp->GetAppResource()->GetString("IDS_VIBRATE_EACH", str);
	str+=" [m] :";

	_pVibeImputDistance= new Slider();
	_pVibeImputDistance->Construct(Rectangle(0, 500, 400, 75),BACKGROUND_STYLE_NONE,true,100,750);
	_pVibeImputDistance->SetValue(_pOptions->GetVibe_vibrationDistance());
	_pVibeImputDistance->SetTitleText(str);
	_pVibeImputDistance->SetTitleTextColor(Color::COLOR_WHITE);
	_pVibeImputDistance->AddAdjustmentEventListener(*this);

	_pScrollPanel->AddControl(*_pVibeImputDistance);

	pApp->GetAppResource()->GetString("IDS_DELETE_DATABASE", str);
	Bitmap* pClearDBBitmap = CreateBitmapText(str,300,100,30);

	_pClearDB = new Button();
	_pClearDB->Construct(Rectangle(50,620,300,100),L"");
	_pClearDB->SetNormalBackgroundBitmap(*pClearDBBitmap);
	_pClearDB->SetNormalBitmap(Point(0,0),*pClearDBBitmap);
	_pClearDB->AddActionEventListener(*this);
	_pClearDB->SetActionId(ID_CLEAR_DB);
	delete pClearDBBitmap;
	VibeOnOff();

	_pScrollPanel->AddControl(*_pClearDB);

	_pFormName = new EnrichedText();
	_pFormName->Construct(Dimension(480, 100));
	_pFormName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	_pFormName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	_pFormName->SetTextWrapStyle(TEXT_WRAP_NONE);

	Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,50);


	pApp->GetAppResource()->GetString("IDS_OPTIONS", str);
	TextElement *text = new TextElement();
	text->Construct(str);
	text->SetFont(*pFont);
	text->SetTextColor(Color::COLOR_WHITE);
	_pFormName->Add(*text);

	delete pFont;

	//koniec elementow na ScrollPanel

	AddControl(*_pScrollPanel);

	RequestRedraw(true);
	return GetLastResult();//moze byc klopotliwe ?
}

void
OptionsForm::VibeOnOff(){
	if(_showVibe){
		_pVibe->SetNormalBackgroundBitmap(*_pON);
		_pVibe->SetNormalBitmap(Point(0,0),*_pON);
	}
	else{
		_pVibe->SetNormalBackgroundBitmap(*_pOFF);
		_pVibe->SetNormalBitmap(Point(0,0),*_pOFF);
	}
}

result
OptionsForm::OnTerminating(void)
{
	if(_pBackground!=null)
		delete _pBackground;
	if(_pFormName != null){
		_pFormName->RemoveAllTextElements(true);
		delete _pFormName;
	}
	if(_pOptions!=null)
		delete _pOptions;
	if(_pON!=null)
		delete _pON;
	if(_pOFF!=null)
		delete _pOFF;

	return E_SUCCESS;
}

void
OptionsForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId){
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	String top,message;
	AppResource *pAppResource = Application::GetInstance()->GetAppResource();
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		break;
	case ID_ON_OFF:
		_showVibe=!_showVibe;
		VibeOnOff();
		_pOptions->SetVibe_isActivated(_showVibe);
		RequestRedraw();
		break;
	case ID_CLEAR_DB:
		MessageBox* pBox;
		pBox= new MessageBox();
		if (pAppResource) {
			pAppResource->GetString("IDS_WARNING", top);
			pAppResource->GetString("IDS_DELETE_DB", message);
		}
		pBox->Construct(top,message,MSGBOX_STYLE_OKCANCEL,100000);
		int result;
		pBox->ShowAndWait(result);
		if(result==MSGBOX_RESULT_OK){
			DatabaseScanner* pDS;
			pDS=new DatabaseScanner();
			pDS->Construct();
			pDS->DeleteAll();
			delete pDS;
		}
		delete pBox;

		break;
	default:
		break;
	}
}

void
OptionsForm::OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment){
	if(&source==_pHeightImput) _pOptions->SetPersonalities_height(adjustment);
	else if(&source==_pWeightImput) _pOptions->SetPersonalities_weight(adjustment);
	else if(&source==_pVibeImputLevel)_pOptions->SetVibe_vibrationLevel(adjustment);
	else _pOptions->SetVibe_vibrationDistance(adjustment);
}


Bitmap*
OptionsForm::CreateBitmapText(String str, int width,int height,int size){
	Canvas canvas;
	canvas.Construct(Rectangle(0,0,width,height));
	Font* Font = GetPavelFont(FONT_STYLE_BOLD,size);

	EnrichedText eText;
	eText.Construct(Dimension(width, height));
	eText.SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
	eText.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	eText.SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);

	TextElement text ;
	text.Construct(str);
	text.SetFont(*Font);
	text.SetTextColor(Color::COLOR_WHITE);
	eText.Add(text);

	canvas.DrawText(Point(0,0),eText);
	Bitmap* bit = new Bitmap();
	bit->Construct(canvas,Rectangle(0,0,width,height));
	delete Font;
	return bit;
}

void
OptionsForm::CreateOnOffBitmaps(){
	String str;
	Application* pApp = Application::GetInstance();

	pApp->GetAppResource()->GetString("IDS_VIBRATION_ON_OFF", str);
	Bitmap* tmp = CreateBitmapText(str,250,100,30);
	Image img;
	img.Construct();
	Bitmap* tmpOn = img.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Options/on.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Bitmap* tmpOff = img.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Options/off.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	_pON = new Bitmap();
	_pON->Construct(Dimension(400,100),BITMAP_PIXEL_FORMAT_ARGB8888);
	_pON->Merge(Point(0,0),*tmp,Rectangle(0,0,250,100));
	_pON->Merge(Point(250,0),*tmpOn,Rectangle(0,0,150,100));

	_pOFF = new Bitmap();
	_pOFF->Construct(Dimension(400,100),BITMAP_PIXEL_FORMAT_ARGB8888);
	_pOFF->Merge(Point(0,0),*tmp,Rectangle(0,0,250,100));
	_pOFF->Merge(Point(250,0),*tmpOff,Rectangle(0,0,150,100));

	delete tmp;
	delete tmpOn;
	delete tmpOff;
}

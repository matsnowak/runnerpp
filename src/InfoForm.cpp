/*
 * AboutForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "InfoForm.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;
using namespace Tizen::Web::Controls;

#include <FWeb.h>

InfoForm::InfoForm() :
	_pBackground(null),
	_pWeb(null)
{
}

InfoForm::~InfoForm() {
}

result InfoForm::OnDraw(void) {
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if (pCanvas != null) {
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		delete pCanvas;
	}

	return r;

}

bool InfoForm::Initialize(void) {
	Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"InfoForm");
	return true;
}

result InfoForm::OnInitializing(void) {
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	Bitmap* pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png",BITMAP_PIXEL_FORMAT_ARGB8888);

	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(290, 1130 ,150,90));
	AddControl(*pToMainMenu);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);

	delete pToMainMenuBitmap;

	_pWeb = new Web();
	_pWeb->Construct(Rectangle(0,250,GetClientAreaBounds().width,GetClientAreaBounds().height-250-90));
	AddControl(*_pWeb);
	String tmp = "file://"+Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Info/help_";
	String str;
	Application *pApp = Application::GetInstance();
	pApp->GetAppResource()->GetString("IDS_APP_LANG", str);
	tmp.Append(str);
	tmp.Append(".html");
	_pWeb->LoadUrl(tmp);


	return GetLastResult();//moze byc klopotliwe ?
}

result InfoForm::OnTerminating(void) {
	if(_pBackground!=null)
		delete _pBackground;
	return E_SUCCESS;
}

void InfoForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {

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
	RequestRedraw(true);
}

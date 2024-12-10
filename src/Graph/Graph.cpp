/*
 * OpenGLForm.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: Administrator
 */

#include "Graph/Graph.h"
#include "RunnerPP.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Graphics::Opengl;

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Graphics::Opengl;
using namespace Tizen::Ui;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Media;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Utility;
using namespace Tizen::Graphics::Opengl;
using namespace Tizen::Base::Collection;

#include <FGraphics.h>
#include <FGraphicsOpengl.h>

Graph::Graph() :
		_pMapGlobal(null),_pMapTrack(null),
			_pSpeedInfo(null),_pPlayer(null),_pGraphRenderer(null){
}

Graph::~Graph() {
	if(_pMapGlobal)
		delete _pMapGlobal;
	if(_pMapTrack)
		delete _pMapTrack;
	if(_pPlayer){
		_pPlayer->Stop();
		delete _pPlayer;
	}
	if(_pGraphRenderer){
		delete _pGraphRenderer;
	}
}

result Graph::OnInitializing(void) {
	result r = E_SUCCESS;
	Form::OnInitializing();
	/**
	 * Inicjacja TouchEventListenera
	 */
	AddTouchEventListener(*this); //dodajemy Listenera, teraz bedziemy mieli kontrole
	Touch touch;
	touch.SetMultipointEnabled(*this, true);//odpalamy Multitouch


	Image* pImage = new Image();
	pImage->Construct();

	Bitmap* pLeftArrowBitmap = pImage->DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/leftArrow.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Button *pLeftArrow = new Button();
	pLeftArrow->Construct(Rectangle(0, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pLeftArrow);
	pLeftArrow->SetActionId(ID_LEFT_ARROW);
	pLeftArrow->AddActionEventListener(*this);
	pLeftArrow->SetNormalBitmap(Point(0,0),*pLeftArrowBitmap);
	pLeftArrow->SetNormalBackgroundBitmap(*pLeftArrowBitmap);
	delete pLeftArrowBitmap;

	Bitmap* pToMainMenuBitmap = pImage->DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	Button *pToMainMenu = new Button();
	pToMainMenu->Construct(Rectangle(290, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*pToMainMenu);
	pToMainMenu->SetActionId(ID_TO_MAINMENU);
	pToMainMenu->AddActionEventListener(*this);
	pToMainMenu->SetNormalBitmap(Point(0,0),*pToMainMenuBitmap);
	pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
	delete pToMainMenuBitmap;

	_pMapGlobal = pImage->DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Graph/mapGlobal.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	_pMapTrack = pImage->DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/Graph/mapTrack.png",BITMAP_PIXEL_FORMAT_ARGB8888);
	_pChangeMap = new Button();
	_pChangeMap->Construct(Rectangle(GetClientAreaBounds().width-150, GetClientAreaBounds().height-90, 150, 90));
	AddControl(*_pChangeMap);
	_pChangeMap->SetActionId(ID_CHANGE_MAP_STYLE);
	_pChangeMap->AddActionEventListener(*this);
	_pChangeMap->SetNormalBitmap(Point(0,0),*_pMapTrack);
	_pChangeMap->SetNormalBackgroundBitmap(*_pMapTrack);

	delete pImage;

	_pSpeedInfo = new Label();
	_pSpeedInfo->Construct(Rectangle(0,0,480,30),"");
	_pSpeedInfo->SetTextConfig(30,LABEL_TEXT_STYLE_NORMAL);
	_pSpeedInfo->SetShowState(false);
	_pSpeedInfo->SetTextHorizontalAlignment( ALIGNMENT_LEFT);
	AddControl(*_pSpeedInfo);

	_pGraphRenderer = new GraphRenderer();
	_pGraphRenderer->SetSpeedInfo(_pSpeedInfo);

	_pPlayer = new Tizen::Graphics::Opengl::GlPlayer();
	_pPlayer->Construct(Tizen::Graphics::Opengl::EGL_CONTEXT_CLIENT_VERSION_1_X, this);

	_pPlayer->SetFps(-1);
	_pPlayer->SetEglAttributePreset(Tizen::Graphics::Opengl::EGL_ATTRIBUTES_PRESET_RGB565);

	_pPlayer->Start();

	_pPlayer->SetIGlRenderer(_pGraphRenderer);


	return r;
}

Tizen::Graphics::Opengl::GlPlayer*
Graph::GetPlayer(){
	return _pPlayer;
}

bool Graph::Initialize() {
	Form::Construct(FORM_STYLE_NORMAL);

	return true;
}

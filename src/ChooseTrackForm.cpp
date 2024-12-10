/*
 * ChooseTrackForm.cpp
 *
 *  Created on: 2010-07-25
 *      Author: Pavel
 */

#include "ChooseTrackForm.h"
#include "RunnerPP.h"
#include "Utils.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Media;
using namespace Tizen::Graphics;

ChooseTrackForm::ChooseTrackForm():
		_pBackground(null),
		_pFormName(null)
{
}

ChooseTrackForm::~ChooseTrackForm()
{
}

result
ChooseTrackForm::OnDraw(void)
{
	result r = E_SUCCESS;

	Canvas* pCanvas = GetCanvasN();
	if(pCanvas != null)
	{
		pCanvas->DrawBitmap(Rectangle(0, 60,GetClientAreaBounds().width,GetClientAreaBounds().height), *_pBackground);
		pCanvas->DrawText(Point(0,150),*_pFormName);
		delete pCanvas;
	}
	return r;
}

bool
ChooseTrackForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_INDICATOR);
	SetName(L"ChooseTrackForm");
	return true;
}

void ChooseTrackForm::LoadList()
{
    DatabaseScanner db;
    db.Construct();
    DbEnumerator *pEnum = db.ReadTracksN();
    if(pEnum!=null){

		pEnum->Reset();
		int id;
		long long int ticks;
		TimeSpan* span;
		DateTime* date;
		String dateView;
		while(pEnum->MoveNext()==E_SUCCESS){
			pEnum->GetIntAt(0,id);
			pEnum->GetInt64At(1,ticks);
			span= new TimeSpan(ticks);
			//tworzenie ladnej polskiej daty ;P
				date= new DateTime();
				date->SetValue(*span);
				dateView.Clear();

				if(date->GetDay()<10) dateView.Append('0');;
				dateView.Append(date->GetDay());

				dateView.Append(L"/");
				if(date->GetMonth()<10)	dateView.Append('0');
				dateView.Append(date->GetMonth());

				dateView.Append(L"/");
				dateView.Append(date->GetYear());

				dateView.Append(L"  ");
				if(date->GetHour()<10)dateView.Append('0');
				dateView.Append(date->GetHour());

				dateView.Append(L":");
				if(date->GetMinute()<10)dateView.Append('0');
				dateView.Append(date->GetMinute());

				dateView.Append(L":");
				if(date->GetSecond()<10) dateView.Append('0');
				dateView.Append(date->GetSecond());

				delete span;
				delete date;

			_pList->AddItem(&dateView,null,null,null,id);

		}
	}
    _pList->ScrollToBottom();
}

void ChooseTrackForm::UpdateList()
{
    _pList->RemoveAllItems();
    LoadList();
}

result
ChooseTrackForm::OnInitializing(void)
{
	Image image;
	image.Construct();
	_pBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/background.png", BITMAP_PIXEL_FORMAT_ARGB8888);

	String str;
	Application* pApp = Application::GetInstance();
	pApp->GetAppResource()->GetString("IDS_EMPTY_LIST", str);

	Bitmap* pListBackground = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/listBackground.png", BITMAP_PIXEL_FORMAT_ARGB8888);
	_pList = new List();
	_pList->Construct(Rectangle(20, 200, 440, 500), LIST_STYLE_NUMBER,LIST_ITEM_SINGLE_TEXT, 50, 0, 440, 0);
	_pList->SetFocusedItemBackgroundBitmap(*pListBackground);
	_pList->SetTextOfEmptyList(str);
	delete pListBackground;

    LoadList();

    AddControl(*_pList);
    ///////////////////
    //_pList->AddItemEventListener(*this);
    //////////////////
    Bitmap *pToMainMenuBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/toMainMenu.png", BITMAP_PIXEL_FORMAT_ARGB8888);
    Button *pToMainMenu = new Button();
    pToMainMenu->Construct(Rectangle(290, GetClientAreaBounds().height-90, 150, 90));
    AddControl(*pToMainMenu);
    pToMainMenu->AddActionEventListener(*this);
    pToMainMenu->SetActionId(ID_TO_MAINMENU);
    pToMainMenu->SetNormalBitmap(Point(0, 0), *pToMainMenuBitmap);
    pToMainMenu->SetNormalBackgroundBitmap(*pToMainMenuBitmap);
    delete pToMainMenuBitmap;
    Bitmap *pLeftArrowBitmap = image.DecodeN(Tizen::App::App::GetInstance()->GetAppRootPath()+"/res/leftArrow.png", BITMAP_PIXEL_FORMAT_ARGB8888);
    Button *pLeftArrow = new Button();
    pLeftArrow->Construct(Rectangle(0, GetClientAreaBounds().height-90, 150, 90));
    AddControl(*pLeftArrow);
    pLeftArrow->AddActionEventListener(*this);
    pLeftArrow->SetActionId(ID_LEFT_ARROW);
    pLeftArrow->SetNormalBitmap(Point(0, 0), *pLeftArrowBitmap);
    pLeftArrow->SetNormalBackgroundBitmap(*pLeftArrowBitmap);
    delete pLeftArrowBitmap;
    _pFormName = new EnrichedText();
    _pFormName->Construct(Dimension(480, 100));
    _pFormName->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    _pFormName->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
    _pFormName->SetTextWrapStyle(TEXT_WRAP_NONE);
    Font *pFont = GetPavelFont(FONT_STYLE_PLAIN,50);
    str.Clear();
    pApp->GetAppResource()->GetString("IDS_RUNNING_DATABASE", str);
    TextElement *text = new TextElement();
    text->Construct(str);
    text->SetFont(*pFont);
    text->SetTextColor(Color::COLOR_WHITE);
    _pFormName->Add(*text);
    delete pFont;
    _pContextMenu = new ListContextMenu();
    _pContextMenu->Construct(*_pList, *this);
    str.Clear();
    pApp->GetAppResource()->GetString("IDS_SHOW", str);
    _pContextMenu->AddItem(str, ID_SHOW);
    str.Clear();
    pApp->GetAppResource()->GetString("IDS_DELETE", str);
    _pContextMenu->AddItem(str, ID_DELETE);
    _pContextMenu->SetShowState(false);
    return GetLastResult();
}

result
ChooseTrackForm::OnTerminating(void)
{
	if(_pBackground!=null)
		delete _pBackground;
	if(_pFormName){
		_pFormName->RemoveAllTextElements(true);
		delete _pFormName;
	}
	if(_pContextMenu)
		delete _pContextMenu;
	return E_SUCCESS;
}

void
ChooseTrackForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId){
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_MENUFORM, null);
		break;
	case ID_LEFT_ARROW:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_STATSFORM, null);
		break;
	case ID_TRACKSTATS:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_TRACKSTATSFORM, null);
		break;
	default:
		break;
	}
}

void
ChooseTrackForm::ShowTrack(int id){
	DatabaseScanner sc;
	sc.Construct();
	RunnerPP* run =static_cast<RunnerPP*> (Application::GetInstance());
	run->SetTrack(sc.ReadN(id));
	OnActionPerformed(*this,ID_TRACKSTATS);
}

void
ChooseTrackForm::OnShowStateChanged(bool show)
{
 if(!show) RequestRedraw();
}

void
ChooseTrackForm::OnListContextMenuAction(int &actionId, int &itemId)
{
 int lol = itemId;
 if(actionId == ID_SHOW){
	 ShowTrack(lol);
 } else if(actionId == ID_DELETE){
    DeleteTrack(lol);
 }
}

void
ChooseTrackForm::DeleteTrack(int itemId)
{
    String title,msg;

    Application *pApp = Application::GetInstance();
    pApp->GetAppResource()->GetString("IDS_TRACK_DELETE", msg);
    pApp->GetAppResource()->GetString("IDS_WARNING", title);
    MessageBox mBox;
    mBox.Construct(title,msg,MSGBOX_STYLE_OKCANCEL,10000);
    int result;
    mBox.ShowAndWait(result);
    if(result == MSGBOX_RESULT_OK ){
    	DatabaseScanner sc;
    	sc.Construct();
    	if(!sc.Delete(itemId)){
    		 pApp->GetAppResource()->GetString("IDS_TRACK_DELETION_FAIL", msg);
    		 pApp->GetAppResource()->GetString("IDS_ERROR", title);
    	} else {
    		pApp->GetAppResource()->GetString("IDS_TRACK_DELETION_SUCCESS", msg);
    		pApp->GetAppResource()->GetString("IDS_SUCCESS", title);
    	}
    	MessageBox mBox2;
    	mBox2.Construct(title,msg,MSGBOX_STYLE_OK,10000);
    	mBox2.ShowAndWait(result);
    	UpdateList();
    	RequestRedraw(true);
    }
}

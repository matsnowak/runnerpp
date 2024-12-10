/**
 * Name        : RunnerPP
 * Version     : 
 * Vendor      : 
 * Description : 
 */

#include "RunnerPP.h"
#include "FormMgr.h"
#include "DatabaseScanner.h"
#include "RegistryScanner.h"
#include "Graph/Graph.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

RunnerPP::RunnerPP():
	_pTrack(null),
	_newTrack(false)
{
}

RunnerPP::~RunnerPP()
{
}

Application*
RunnerPP::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new RunnerPP();
}

bool
RunnerPP::OnAppInitializing(AppRegistry& appRegistry)
{
	//inicjalizacja

	Tizen::Ui::Controls::Frame* pAppMainFrame = new Tizen::Ui::Controls::Frame();
			pAppMainFrame->Construct();
			pAppMainFrame->SetName(L"MainFrame");
			AddFrame(*pAppMainFrame);
	FormMgr *pFormMgr = new FormMgr();
	pFormMgr->Initialize();
	GetAppFrame()->GetFrame()->AddControl(*pFormMgr);


	AppResource *pAppResource = Application::GetInstance()->GetAppResource();
	String test;
	result r;
	if(pAppResource==null){
		pFormMgr->SetStarterForm(FormMgr::REQUEST_ERRORFORM, null);
		return true;
	}

	if(!Database::Exists(L"/Home/dbTracks.db")){
		//AppLog("Tworzymy !");
		DatabaseScanner* ds;
		ds=new DatabaseScanner();
		ds->Construct();
		int i;
		while(!ds->SetUp()){
			MessageBox mesBox;
			String top,message;
			AppResource *pAppResource = Application::GetInstance()->GetAppResource();
			if (pAppResource) {
				pAppResource->GetString("IDS_ERROR", top);
				pAppResource->GetString("IDS_ERROR_MSG_SETUPDB", message);
			}
			mesBox.Construct(top,message,MSGBOX_STYLE_YESNO,30000);
			mesBox.ShowAndWait(i);
			if(i==MSGBOX_RESULT_NO) break;
		}
		RegistryScanner* rs;
		rs= new RegistryScanner();
		rs->Construct();
		while(!rs->SetUP()){
			MessageBox mesBox;
			String top,message;
			AppResource *pAppResource = Application::GetInstance()->GetAppResource();
			if (pAppResource) {
				pAppResource->GetString("IDS_ERROR", top);
				pAppResource->GetString("IDS_ERROR_MSG_SETUPRS", message);
			}
			mesBox.Construct(top,message,MSGBOX_STYLE_YESNO,10000);
			mesBox.ShowAndWait(i);
			if(i==MSGBOX_RESULT_NO) break;
		}
		delete rs;
		delete ds;
		pFormMgr->SetStarterForm(FormMgr::REQUEST_INTROFORM, null);
	}
	else pFormMgr->SetStarterForm(FormMgr::REQUEST_MENUFORM, null);
	return true;

}

bool
RunnerPP::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	if(_pTrack!=null) delete _pTrack;
	_pTrack=null;
	return true;
}

void
RunnerPP::OnForeground(void)
{
	Graph* g= dynamic_cast<Graph*>(GetAppFrame()->GetFrame()->GetCurrentForm());
	if(g){
		g->GetPlayer()->Resume();
		AppLog("started Player");
	}
}

void
RunnerPP::OnBackground(void)
{
	Graph* g= dynamic_cast<Graph*>(GetAppFrame()->GetFrame()->GetCurrentForm());
	if(g){
		g->GetPlayer()->Pause();
		AppLog("stopped Player");
	}
}

void
RunnerPP::OnLowMemory(void)
{
	MessageBox mesBox;
	String top,message;
	AppResource *pAppResource = Application::GetInstance()->GetAppResource();
	if (pAppResource) {
		pAppResource->GetString("IDS_WARNING", top);
		pAppResource->GetString("IDS_BRAK_PAMIECI", message);
	}
	mesBox.Construct(top,message,MSGBOX_STYLE_OK,30000);
	mesBox.Show();
	Terminate();
}

void
RunnerPP::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	if(batteryLevel==BATTERY_CRITICAL || batteryLevel ==BATTERY_EMPTY){
		MessageBox mesBox;
		String top,message;
		AppResource *pAppResource = Application::GetInstance()->GetAppResource();
		if (pAppResource) {
			pAppResource->GetString("IDS_WARNING", top);
			pAppResource->GetString("IDS_SLABA_BATERIA", message);
		}
		mesBox.Construct(top,message,MSGBOX_STYLE_OK,30000);
		mesBox.Show();
		Terminate();
	}
}

void
RunnerPP::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
RunnerPP::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}

Track* RunnerPP::GetTrack(){
	return _pTrack;
}

void RunnerPP::SetTrack(Track* __value){
	ClearTrack();
	_pTrack=__value;
}

void RunnerPP::ClearTrack(){
	if(_pTrack!=null) delete _pTrack;
	_pTrack=null;
}

void RunnerPP::NewTrack(){
	_newTrack=true;
}

void RunnerPP::TrackSaved(){
	_newTrack=false;
}

bool
RunnerPP::NeedToBeSaved(){
	return _newTrack;
}


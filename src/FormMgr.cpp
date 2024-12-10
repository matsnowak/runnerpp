/*
 * FormMgr.cpp
 *
 *  Created on: 2010-07-27
 *      Author: Mateusz
 */

#include "FormMgr.h"
#include "IBaseForm.h"
#include "MainMenuForm.h"
#include "ChooseTrackForm.h"
#include "StatsForm.h"
#include "OptionsForm.h"
#include "StatsForm.h"
#include "IntroForm.h"
#include "InfoForm.h"
#include "RunForm.h"
#include "RunnerPP.h"
#include "SaveForm.h"
#include "SavingFormMM.h"
#include "SavingFormCF.h"
#include "Graph/Graph.h"

FormMgr::FormMgr() :
	_pCurrentForm(null)
{}

FormMgr::~FormMgr() {
	// TODO Auto-generated destructor stub
}

bool FormMgr::Initialize(void) {
	result r = E_SUCCESS;
	r = Form::Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR);
	SetName(L"FormMgr");

	return true;
}

bool FormMgr::SetStarterForm(RequestId requestId,
		Tizen::Base::Collection::IList* pArgs) {
	Form *pCurrentForm =Application::GetInstance()->GetAppFrame()->GetFrame()->GetCurrentForm();
	if (pCurrentForm == this)
		SwitchToForm(requestId, pArgs);
	else
		return false;

	return true;
}

void FormMgr::OnUserEventReceivedN(RequestId requestId,
		Tizen::Base::Collection::IList* pArgs) {
	SwitchToForm(requestId, pArgs);
}

void FormMgr::SwitchToForm(RequestId requestId,
		Tizen::Base::Collection::IList* pArgs) {
	RunnerPP* run =static_cast<RunnerPP*>(Application::GetInstance());
	Frame *pFrame = run->GetAppFrame()->GetFrame();
	IBaseForm* pTempForm = null;

	switch (requestId) {
	case REQUEST_MENUFORM:
		pTempForm = new MainMenuForm();
		break;
	case REQUEST_RUNFORM:
		pTempForm = new RunForm();
		break;
	case REQUEST_STATSFORM:
		pTempForm = new StatsForm();
		break;
	case REQUEST_OPTIONSFORM:
		pTempForm = new OptionsForm();
		break;
	case REQUEST_CHOOSETRACKFORM:
		pTempForm = new ChooseTrackForm();
		break;
	case REQUEST_ABOUTFORM:
		pTempForm = new InfoForm();
		break;
	case REQUEST_TRACKSTATSFORM:
		pTempForm = new TrackStatsForm();
		break;
	case REQUEST_GRAPHFORM:
		pTempForm = new Graph();
		break;
	case REQUEST_EXIT_TO_CHOOSEFORM:
		if(run->NeedToBeSaved()){
			pTempForm=new SavingFormCF();
		}
		else pTempForm=new ChooseTrackForm();
		break;
	case REQUEST_EXIT_TO_MAINMENU:
		if(run->NeedToBeSaved()){
					pTempForm=new SavingFormMM();
		}
		else pTempForm=new MainMenuForm();
		break;
	case REQUEST_INTROFORM:
		pTempForm= new IntroForm();
		break;
	case REQUEST_SAVEFORM:
		pTempForm= new SaveForm();
		break;
	default:
		return;
		break;
	}

	pTempForm->Initialize();
	pFrame->AddControl(*pTempForm);
	pFrame->SetCurrentForm(*pTempForm);
	pTempForm->Draw();
	pTempForm->Show();
	if (_pCurrentForm != null) {
		pFrame->RemoveControl(*_pCurrentForm);
	}
	_pCurrentForm = pTempForm;

}

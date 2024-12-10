#include "Graph/Graph.h"
#include "FormMgr.h"
#include "RunnerPP.h"

using namespace Tizen::Ui::Controls;

void Graph::OnActionPerformed(const Tizen::Ui::Control& source, int actionId) {
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	FormMgr *pFormMgr = static_cast<FormMgr *> (pFrame->GetControl("FormMgr"));
	switch (actionId) {
	case ID_TO_MAINMENU:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_EXIT_TO_MAINMENU, null);
		break;
	case ID_LEFT_ARROW:
		if (pFormMgr != null)
			pFormMgr->SendUserEvent(FormMgr::REQUEST_TRACKSTATSFORM, null);
		break;
	case ID_CHANGE_MAP_STYLE:
		if (_pGraphRenderer->IsInGlobalCameraType()){
			_pGraphRenderer->SetDefaultTrack();
			_pChangeMap->SetNormalBitmap(Tizen::Graphics::Point(0,0),*_pMapGlobal);
			_pChangeMap->SetNormalBackgroundBitmap(*_pMapGlobal);
			_pSpeedInfo->SetShowState(true);
		} else {
			_pGraphRenderer->SetDefaultGlobal();
			_pChangeMap->SetNormalBitmap(Tizen::Graphics::Point(0,0),*_pMapTrack);
			_pChangeMap->SetNormalBackgroundBitmap(*_pMapTrack);
			_pSpeedInfo->SetShowState(false);

		}
		//RequestRedraw(true);
		break;
	default:
		break;
	}
}

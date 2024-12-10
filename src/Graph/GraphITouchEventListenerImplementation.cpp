#include "Graph/Graph.h"
#include <FApp.h>


using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Utility;
using namespace Tizen::App;

void
Graph::OnTouchMoved(const Tizen::Ui::Control &source,const Tizen::Graphics::Point &currentPosition,const TouchEventInfo &touchInfo) {

		if(_touchStatus==TS_NONE) return; //nie ma co robic z zerowa ilosci palcow
		else if(_touchStatus==TS_MOVE){
			float delta_y,delta_x;
			double tan;
					//obliczanie przesuniecia
					if(_lastStartingPoint.x==touchInfo.GetStartPosition().x && _lastStartingPoint.y==touchInfo.GetStartPosition().y){
						delta_y = touchInfo.GetCurrentPosition().y-_lastPoint.y;
						delta_x = touchInfo.GetCurrentPosition().x-_lastPoint.x;
						_lastPoint.SetPosition(touchInfo.GetCurrentPosition().x,touchInfo.GetCurrentPosition().y);
					}
					else{
						delta_y = touchInfo.GetCurrentPosition().y-touchInfo.GetStartPosition().y;
						delta_x = touchInfo.GetCurrentPosition().x-touchInfo.GetStartPosition().x;
						_lastStartingPoint.SetPosition(touchInfo.GetStartPosition().x,touchInfo.GetStartPosition().y);
					}
					if(delta_x ==0)	return;
					tan = delta_y/delta_x;
					if(tan<=1 && tan>=-1){
						if(delta_x>0) {
							_pGraphRenderer->RotateRight();
						}
						else {
							_pGraphRenderer->RotateLeft();
						}
					}
					else{
						if(delta_y>0){
							_pGraphRenderer->GoUp();
						}
						else {
							_pGraphRenderer->GoDown();
						}
					}
		}
		else if(_touchStatus==TS_ZOOM){
			//zooming
			Touch touch;
			IList *touchList = null;
			touchList = touch.GetTouchInfoListN(*this);

			if (touchList && touchList->GetCount()==2)//sprawdzenie dla bezpieczenstwa
			{
				TouchInfo *touch1 = static_cast<TouchInfo *>(touchList->GetAt(0));
				TouchInfo *touch2 = static_cast<TouchInfo *>(touchList->GetAt(1));
				if(touch1 && touch2)
				{
					// tylko jak wczesniej mielismy je zarejestrowane
					if(_lastZoomedPoint1.x != 0 && _lastZoomedPoint1.y != 0 &&
					   _lastZoomedPoint2.x != 0 && _lastZoomedPoint2.y != 0)
					{
						// find rate of zooming
						double hyp1 = Math::Sqrt(Math::Pow(_lastZoomedPoint1.x-_lastZoomedPoint2.x,2)+Math::Pow(_lastZoomedPoint1.y-_lastZoomedPoint2.y,2));
						double hyp2 = Math::Sqrt(Math::Pow(touch1->position.x-touch2->position.x,2)+Math::Pow(touch1->position.y-touch2->position.y,2));
						double zoomRate = hyp2/hyp1;
						//AppLog("zoomrate:%f",zoomRate);
						if(zoomRate>=1)	_pGraphRenderer->ZoomOut();
						else _pGraphRenderer->ZoomIn();
					}
					_lastZoomedPoint1 = touch1->position;
					_lastZoomedPoint2 = touch2->position;
				}
			touchList->RemoveAll(true);
			delete touchList;
			}
		}
		//RequestRedraw(true);
		//TODO sprawdzicz czy potrzebny redraw !
}

void
Graph::OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo){
	_lastStartingPoint.x = touchInfo.GetStartPosition().x;
	_lastStartingPoint.y = touchInfo.GetStartPosition().y;

	Touch touch;
	IList *touchList = null;
	touchList = touch.GetTouchInfoListN(*this);
	if (touchList)
	{
		// 0-nic 1-rotacje 2- zoom
		switch(touchList->GetCount())
		{
		case 0:
			_touchStatus = TS_NONE;
			break;
		case 1:
			_touchStatus = TS_MOVE;
			break;
		case 2:
			_touchStatus= TS_ZOOM;
			break;

		}
		touchList->RemoveAll(true);//czyscimy liste
		delete touchList;
	}
	else {
		_touchStatus = TS_NONE;
	}
}

void
Graph::OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const TouchEventInfo &touchInfo){
	_touchStatus= TS_NONE;
}

void
Graph::OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition,const TouchEventInfo &touchInfo){
	MessageBox mesBox;
	String message;
	AppResource *pAppResource = Application::GetInstance()->GetAppResource();
	if (pAppResource) {
		pAppResource->GetString("IDS_GRAPH_INFO", message);
	}
	mesBox.Construct("INFO",message,MSGBOX_STYLE_OK ,30000);
	mesBox.SetTitleTextColor(Tizen::Graphics::Color(250,250,250,250));
	int i;
	mesBox.ShowAndWait(i);
}

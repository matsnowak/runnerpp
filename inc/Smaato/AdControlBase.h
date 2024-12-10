/*
 * AdControlBase.h
 *
 *  Created on: 07.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ADCONTROLBASE_H_
#define ADCONTROLBASE_H_

#include <FUi.h>
#include <FBase.h>
#include <FGraphics.h>
#include "IAdResponseListener.h"
#include "AdUserData.h"
#include "AdContainer.h"


namespace Smaato
{
	namespace AdSDK
	{
		class HttpConnector;
		class AdControlBase
		: public Tizen::Ui::Controls::Panel
		, private Tizen::Ui::ITouchEventListener
		, private IAdResponseListener
		, private Tizen::Base::Runtime::ITimerEventListener
		{
		public:
			AdControlBase();
			virtual ~AdControlBase();

		// Implementation
		public:
			virtual bool Initialize(const Tizen::Graphics::Rectangle &rect);
			virtual result OnInitializing(void);
			virtual result OnTerminating(void);

			virtual result OnDraw(void);

		protected:
			virtual void OpenLandingPage();
			virtual result RequestNewAd();

		private:
			virtual void OnTouchDoublePressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
			virtual void OnTimerExpired (Tizen::Base::Runtime::Timer &timer);

		private:
			void SetAdContainer(const Smaato::AdSDK::AdContainer &adContainer);
			virtual void OnNewAdAvailable(Smaato::AdSDK::AdContainer& adContainer);
			virtual void OnComunicationError(result r, const Tizen::Base::String& desc);
			void ShowNextFrame();

		protected:
			AdUserData *__pUserData;
			HttpConnector *__pConnector;
			Tizen::Base::Runtime::Timer* __pRefreshTimer;
			bool __pTimerRunning;
			int __pRefreshTime;

		private:
			AdContainer *__pAdContainer;
			Tizen::Base::Runtime::Timer* __pTimer;
			bool __pGifAnimationRunning;
			const Tizen::Graphics::Bitmap* __pCurrentBitmap;
		};
	}
}

#endif /* ADCONTROLBASE_H_ */

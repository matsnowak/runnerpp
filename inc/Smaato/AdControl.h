/*
 * AdControl.h
 *
 *  Created on: 01.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ADCONTROL_H_
#define ADCONTROL_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include "AdControlBase.h"
#include "IAdResponseListener.h"
#include "AdDownloaderBase.h"

namespace Smaato {
	namespace AdSDK {
		/**
		 * \brief Tizen::Ui::Control used to display ads in a bada application
		 *
		 * This control can be used to create an ad enabled application based on bada.
		 * It has a property containing all the user information to be send to the server.
		 * The request for a new ad can be triggered by calling RequestNewAd().
		 * If a user touches the control the landing page of the ad is displayed and a click is counted.
		 * The following example shows the default usage of this control.
		 *
		 * \code
		 * __pAdControl = new Smaato::AdSDK::AdControl();
		 *
		 * __pAdControl->Initialize();    // Important!
		 * __pAdControl->SetBounds(10, 10, 460, 60);
		 *
		 * AdUserData& adUserData = __pAdControl->GetUserData();
		 *
		 * adUserData.SetAdSpaceId(0);    // Replace with your AdSpaceID
		 * adUserData.SetPublisherId(0);  // Replace with your PublisherID
		 *
		 * adUserData.SetAdType(AdUserData::AdTypeImage);
		 *
		 * this->AddControl(*__pAdControl);
		 * __pAdControl->Draw();
		 * __pAdControl->Show();
		 * \endcode
		 *
		 * The AdUserData can be retrieved through GetUserData().
		 * You have to replace the Ids with those you received through the Smaato Publisher Dashboard.
		 * You can set social and economic parameters via adUserData.
		 * Please refer to AdUserData for a complete list of supported parameters.
		 * The AdControl should be at least 320pix wide and 50pix high.
		 * This will allow you to download the biggest banner format for your device.
		 */
		class AdControl
		: public AdControlBase
		, public AdDownloaderBase
		{
		public:
			AdControl();
			virtual ~AdControl();

		public:
			/**
			 * \brief Initializes the AdContainer with the given rectangle
			 * @param rect The rectangle of the AdControl
			 * @return Returns if the initialization succeded
			 */
			virtual bool Initialize(const Tizen::Graphics::Rectangle &rect);

			/**
			 * \brief Returns a reference to the user data that has been set for this AdControl.
			 */
			virtual AdUserData& GetUserData();

			/**
			 * \brief Opens the landing page for the currently displayed banner.
			 * Please note that the AdControl listens to touch events and opens the landing page if the user clicks the ad.
			 * This method should only be used if a user can not click the ad (i.e. on feature phones).
			 */
			virtual void OpenLandingPage();

			/**
			 * \brief Requests a new ad from the server. The ad is loaded asynchronously so the interface will not block during load.
			 */
			virtual result RequestNewAd();

			/**
			 * \brief Adds a new ad response listener that is called when a new ad is received or when a comunication error occurred.
			 */
			virtual void AddAdResponseListener(Smaato::AdSDK::IAdResponseListener* responseListener);

			/**
			 * \brief Removes the given ad response listener.
			 */
			virtual void RemoveAdResponseListener(Smaato::AdSDK::IAdResponseListener* responseListener);

			/**
			 * \brief Starts the automatic reload of ads
			 */
			void StartAutomaticReload();

			/**
			 * \brief Stops the automatic reload of ads
			 */
			void StopAutomaticReload();
		};
	}
}

#endif /* ADCONTROL_H_ */

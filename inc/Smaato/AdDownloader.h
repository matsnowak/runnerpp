/*
 * AdDownloader.h
 *
 *  Created on: 09.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ADDOWNLOADER_H_
#define ADDOWNLOADER_H_

#include "IAdResponseListener.h"
#include "AdUserData.h"
#include "AdDownloaderBase.h"

namespace Smaato
{
	namespace AdSDK
	{
		class HttpConnector;

		/*!
		 * \brief Used to download ads from the Smaato server.
		 *
		 * This class can be used to create an ad enabled application based on bada.
		 * It is created to allow you to display banner ads in non UI based applications (i.e. games).
		 * If you want to integrate Smaato ads into your UI based application please consider using AdControl.<BR>
		 * AdDownloader has a property containing all the user information to be send to the server.
		 * The request for a new ad can be triggered by calling RequestNewAd().
		 * To receive downloaded ads you have to implement an IAdResponseListener and add it to the AdDownloader via AdDownloader::AddAdResponseListener.
		 * If a user touches the ad you have to call AdContainer::OpenLandingPage() for the landing page of the ad to display.<BR>
		 * The following code shows an example of usage.
		 *
		 * \code
		 * __pAdDownloader = new Smaato::AdSDK::AdDownloader();
		 *
		 * __pAdDownloader->Initialize();    // Important!
		 *
		 * AdUserData& adUserData = __pAdDownloader->GetUserData();
		 *
		 * adUserData.SetAdSpaceId(0);    // Replace with your AdSpaceID
		 * adUserData.SetPublisherId(0);  // Replace with your PublisherID
		 *
		 * adUserData.SetAdType(AdUserData::AdTypeImage);
		 *
		 * __pAdDownloader->AddAdResponseListener(this);
		 * __pAdDownloader->RequestNewAd();
		 * \endcode
		 *
		 * The AdUserData can be retrieved through GetUserData().
		 * You have to replace the Ids with those you received through the Smaato Publisher Dashboard.
		 * You can set social and economic parameters via adUserData.
		 * Please refer to AdUserData for a complete list of supported parameters.
		 */
		class AdDownloader : public AdDownloaderBase {
		public:
			AdDownloader();
			virtual ~AdDownloader();

		public:
			/**
			 * \brief Initializes the AdDownloader and prepares it to receive ads.
			 */
			void Initialize();

			/**
			 * \brief Returns the user specific settings.
			 * @return Reference to AdUserData.
			 */
			virtual AdUserData& GetUserData();

			/**
			 * \brief Requests a new ad from the Smaato server asynchronously.
			 * @return Result of the request.
			 */
			virtual result RequestNewAd();

			/**
			 * \brief Adds a new IAdResponseListener that gets called when a new ad is available or an error occurred during ad retrieval.
			 * @param responseListener The response listener to be added.
			 */
			virtual void AddAdResponseListener(IAdResponseListener* responseListener);

			/**
			 * \brief Removes a resonse listener from the AdDownloader.
			 * @param responseListener The response listener to be removed.
			 */
			virtual void RemoveAdResponseListener(IAdResponseListener* responseListener);

		private:
			HttpConnector* __pConnector;
			AdUserData __pUserData;
		};
	} // namespace AdSDK
} // namespace Smaato

#endif /* ADDOWNLOADER_H_ */

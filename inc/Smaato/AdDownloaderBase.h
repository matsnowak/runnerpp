/*
 * AdDownloaderBase
 *
 *  Created on: 25.05.2011
 *      Author: Gerrit Alves
 */

#ifndef IADDOWNLOADERBASE_H_
#define IADDOWNLOADERBASE_H_

#include "AdUserData.h"
#include "IAdResponseListener.h"

namespace Smaato
{
	namespace AdSDK
	{
		/**
		 * \brief Provides a common interface for all ad downloader classes
		 */
		class AdDownloaderBase
		{
		public:
			/**
			 * \brief Returns the user specific settings.
			 * @return Reference to AdUserData.
			 */
			virtual AdUserData& GetUserData() = 0;

			/**
			 * \brief Requests a new ad from the Smaato server asynchronously.
			 * @return Result of the request.
			 */
			virtual result RequestNewAd() = 0;

			/**
			 * \brief Adds a new IAdResponseListener that gets called when a new ad is available or an error occurred during ad retrieval.
			 * @param responseListener The response listener to be added.
			 */
			virtual void AddAdResponseListener(IAdResponseListener* responseListener) = 0;

			/**
			 * \brief Removes a response listener from the AdDownloader.
			 * @param responseListener The response listener to be removed.
			 */
			virtual void RemoveAdResponseListener(IAdResponseListener* responseListener) = 0;

			/**
			 * \brief Starts automatic location updates
			 */
			virtual void StartLocationUpdates();

			/**
			 * \brief Stops automatic location updates
			 */
			virtual void StopLocationUpdates();

			/**
			 * Activates or deactivates the creation of debug messages.
			 * Default is disabled.
			 * @param debugMsg
			 */
			void setDebugMsgActivated(bool debugMsg);

			/**
			 * Returns whether creation of debug messages is activated.
			 */
			bool debugMsgActivated();
		};
	}
}

#endif //IADDOWNLOADERBASE_H_

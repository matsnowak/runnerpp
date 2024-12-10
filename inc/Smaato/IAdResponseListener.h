/*
 * IAdResponseListener.h
 *
 *  Created on: 01.02.2011
 *      Author: Gerrit Alves
 */

#ifndef IADRESPONSELISTENER_H_
#define IADRESPONSELISTENER_H_

#include "AdContainer.h"
#include <FBase.h>

namespace Smaato
{
	namespace AdSDK
	{
		/**
		 * \brief Provides call back functions for new ads and comunication errors.
		 */
		class IAdResponseListener :
			public Tizen::Base::Runtime::IEventListener
		{
		public:
			/**
			 * \brief Callback function for new ad available
			 */
			virtual void OnNewAdAvailable(Smaato::AdSDK::AdContainer& adContainer) = 0;

			/**
			 * \brief Callback function for comunication error
			 */
			virtual void OnComunicationError(result r, const Tizen::Base::String& desc) = 0;
		};
	}
}

#endif /* IADRESPONSELISTENER_H_ */

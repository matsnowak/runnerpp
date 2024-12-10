/*
 * AdContainer.h
 *
 *  Created on: 28.01.2011
 *      Author: Gerrit Alves
 */

#ifndef ADCONTAINER_H_
#define ADCONTAINER_H_

#include <FBase.h>
#include <FGraphics.h>
#include "AdContainerBase.h"

namespace Smaato
{
	namespace AdSDK
	{
		/*!
		  \brief Container that holds a single ad received from the server

		  This container is created every time a new ad is received from the Smaato server.
		  It contains the ad image to be displayed in your application as well as the click through url that should be opened when the user clicks the ad.<BR>
		  The AdContainer is supplied in the IAdResponseListener::OnNewAdAvailable method. In this method you can retrieve the ad image with the following code:
		  \code
			Tizen::Graphics::Bitmap* adImage = adContainer.GetAdImage();
		  \endcode
		  Please note that the method returns NULL is an error occurred.<BR>
		  If adContainer.IsTextAd() returns true you have received a text ad.
		  Text ads have to be rendered before they can be displayed.
		  \code
		  result r = adContainer.RenderTextAd(widthOfBanner, heightOfBanner);
		  if (r == E_SUCCESS)
		  {
			  Tizen::Graphics::Bitmap* adImage = adContainer.GetAdImage();
		  }
		  \endcode
		  You have to supply the width and height of the text banner you would like to create. After rendering the created image can be retrieved like an image ad.
		  */
		class AdContainer : public AdContainerBase {

		public:
			enum ErrorCodes
			{
				E_NO_AD_AVAILABLE = 42,
				E_UNKNOWN_PUBLISHER = 106,
				E_GENERAL_ERROR = 107
			};

		public:
			AdContainer();
			AdContainer(const AdContainer & adContainer);
			virtual ~AdContainer();

		// Implementation
		public:
			/**
			 * \brief Returns the url of the ad image.
			 */
			const Tizen::Base::String &GetAdUrl() const;

			/**
			 * \brief Returns the text of an text ad.
			 */
			const Tizen::Base::String &GetAdText() const;

			/**
			 * \brief Returns the url that should be opened when the ad is clicked.
			 */
			const Tizen::Base::String &GetClickUrl() const;

			/**
			 * \brief Returns the received ad image
			 * If the received ad is a animated gif the current frame of the animation will be returned.
			 * If the received ad is a text ad you have to call RenderTextAd(int width, int height) first to prepare the image.
			 */
			const Tizen::Graphics::Bitmap *GetAdImage() const;

			/**
			 * \brief Returns the animated ad image
			 */
			Smaato::AdSDK::AnimatedGif *GetAnimatedAdImage() const;

			/**
			 * \brief Returns whether the contained ad is a text ad.
			 */
			bool IsTextAd() const;

			/**
			 * \brief Returns whether the contained ad is a animated gif.
			 */
			bool IsAnimatedAd() const;

			/**
			 * \brief Returns the error code if an error occured.
			 */
			int GetErrorCode() const;

			/**
			 * \brief Returns the error string if an error occured.
			 */
			const Tizen::Base::String& GetErrorString() const;

			/**
			 * \brief Opens the landing page in the phones browser.
			 */
			void ClickThrough();

			/**
			 * \brief Renders the text ad with the supplied width and height.
			 * \param width The width of the created banner image.
			 * \param height The height of the created banner image.
			 */
			result RenderTextAd(int width, int height);

		};
	}
}

#endif /* ADCONTAINER_H_ */

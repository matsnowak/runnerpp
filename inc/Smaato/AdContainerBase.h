/*
 * AdContainerBase.h
 *
 *  Created on: 09.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ADCONTAINERBASE_H_
#define ADCONTAINERBASE_H_

#include <FBase.h>
#include <FGraphics.h>
#include "AnimatedGif.h"

namespace Smaato
{
	namespace AdSDK
	{
		class AdContainerBase : public Tizen::Base::Object {
					friend class XMLParser;
					friend class HttpConnector;

		public:
			AdContainerBase();
			AdContainerBase(const AdContainerBase & adContainerBase);
			virtual ~AdContainerBase();

		private:
			void SetAdUrl(const Tizen::Base::String &adUrl);
			void SetAdText(const Tizen::Base::String &adText);
			void SetClickUrl(const Tizen::Base::String &clickUrl);
			void AddBeaconUrl(const Tizen::Base::String &beaconUrl);
			const Tizen::Base::Collection::ArrayList &GetBeaconUrls() const;
			int GetBeaconCount() const;
			Tizen::Base::String GetBeaconString(int index) const;
			void SetAdImage(Tizen::Graphics::Bitmap *adImage);
			void SetAnimatedGif(Smaato::AdSDK::AnimatedGif *adImage);
			void setErrorCode(int errorCode);
			void setErrorString(const Tizen::Base::String& errorCode);

		protected:
			Tizen::Graphics::Bitmap* loadImageN(const Tizen::Base::String& image) const;

		protected:
			Tizen::Base::String __pAdUrl;
			Tizen::Base::String __pAdText;
			Tizen::Base::String __pClickUrl;
			Tizen::Base::Collection::ArrayList __pBeaconUrls;
			Tizen::Graphics::Bitmap *__pAdImage;
			AnimatedGif* __pAnimatedAdImage;
			int __pErrorCode;
			Tizen::Base::String __pErrorString;
		};
	}
}

#endif /* ADCONTAINERBASE_H_ */

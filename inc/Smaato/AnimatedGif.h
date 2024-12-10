/*
 * AnimatedGif.h
 *
 *  Created on: 04.02.2011
 *      Author: Gerrit Alves
 */

#ifndef ANIMATEDGIF_H_
#define ANIMATEDGIF_H_

#include <FBase.h>
#include <FGraphics.h>
#include <FUi.h>

namespace Smaato
{
	namespace AdSDK
	{
		class AnimatedGif {
		public:
			AnimatedGif();
			AnimatedGif(const AnimatedGif& other);
			virtual ~AnimatedGif();

		public:
			void decodeAnimatedGif(Tizen::Base::ByteBuffer* buffer);
			const Tizen::Base::Collection::ArrayList& GetAnimationFrames() const;
			const Tizen::Ui::Controls::AnimationFrame* GetFirstFrame() const;
			const Tizen::Ui::Controls::AnimationFrame* GetCurrentFrame() const;
			const Tizen::Ui::Controls::AnimationFrame* GetNextFrame() const;
			const Tizen::Ui::Controls::AnimationFrame* GetFrameAt(int index) const;
			int GetFrameCount() const;

		protected:
			bool findSingleImage(Tizen::Base::ByteBuffer *buffer, int& start, int& end, double& duration, Tizen::Graphics::Rectangle& rect);
			bool findApplicationExtension(Tizen::Base::ByteBuffer *buffer, int& start, int& end);
			Tizen::Base::ByteBuffer * removeSelectionN(Tizen::Base::ByteBuffer *buffer, int start, int end);

		public:
			result SaveToFile(const Tizen::Base::String& filename, const Tizen::Base::ByteBuffer& buffer);

		protected:
			Tizen::Base::Collection::ArrayList __pFrameList;
			mutable int __pCurrentFrame;
		};
	}
}


#endif /* ANIMATEDGIF_H_ */

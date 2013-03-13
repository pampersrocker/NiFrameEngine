// NiFrameRenderer.h

#pragma once

#include "NiFrameRendererPCH.h"

namespace NiFrame
{
	namespace Renderer
	{
		class NiFrameRenderDevice
		{
		public:

			virtual void Init(  ) = 0;

			virtual bool IsRunning() const = 0;

			virtual void UseWindow() = 0;

			virtual void BeginRendering() = 0;

			virtual void EndRendering() = 0;

			virtual void Clear( bool clearPixel , bool clearDepth ) = 0;


		private:

		};
	}
}

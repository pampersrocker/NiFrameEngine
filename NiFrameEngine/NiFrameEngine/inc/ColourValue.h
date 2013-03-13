#pragma once
#ifndef ColourValue_h__
#define ColourValue_h__

#include "NiFrameEnginePCH.h"
#include "NiFramePrerequisites.h"

namespace NiFrame
{
	namespace Renderer
	{
		/**
		\brief Class to store a Color Value containing Red, Green, Blue and Alpha values.
		
		\remark The range of the colors is normally between 0.0 and 1.0
		
		*/
		class ColorValue
		{
		public:
			ColorValue();

			ColorValue(const Real& value, const Real& alpha = NiFrame::RealHelper::ONE);

			ColorValue(const Real& red, const Real& green, const Real& blue, const Real& alpha = NiFrame::RealHelper::ONE);

			~ColorValue();

			NiFrame::Real Red, Green, Blue, Alpha;

		private:
		
		};
	}
}

#endif // ColourValue_h__


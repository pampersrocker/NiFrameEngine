#include "NiFrameRendererPCH.h"


namespace NiFrame
{
	namespace Renderer
	{
#ifdef USE_DOUBLE_PRECISSIOM
	const Real RealHelper::ZERO = 0.0;
	const Real RealHelper::ONE = 1.0;
	const Real RealHelper::NEGATIVE_ONE = -1.0;

#else
	const Real RealHelper::ZERO = 0.0f;
	const Real RealHelper::ONE = 1.0f;
	const Real RealHelper::NEGATIVE_ONE = -1.0f;

#endif // USE_DOUBLE_PRECISSIOM

	}
}



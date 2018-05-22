#include "NFEnginePCH.hpp"
#include "NFPrerequisites.hpp"

namespace nfe
{
#ifdef USE_DOUBLE_PRECISION
  const Real RealHelper::ZERO = 0.0;
  const Real RealHelper::ONE = 1.0;
  const Real RealHelper::NEGATIVE_ONE = -1.0;

#else
  const Real RealHelper::ZERO = 0.0f;
  const Real RealHelper::ONE = 1.0f;
  const Real RealHelper::NEGATIVE_ONE = -1.0f;

#endif // USE_DOUBLE_PRECISSION
}
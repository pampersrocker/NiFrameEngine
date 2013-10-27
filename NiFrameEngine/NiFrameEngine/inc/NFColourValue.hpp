#pragma once
#ifndef ColourValue_h__
#define ColourValue_h__

#include "NFEnginePCH.hpp"
#include "NFPrerequisites.hpp"

namespace nfe
{

	/**
	\brief Class to store a Color Value containing Red, Green, Blue and Alpha values.
		
	\remark The range of the colors is normally between 0.0 and 1.0
		
	*/
	class ColorValue
	{
	public:
		ColorValue();

		ColorValue(const Real& value, const Real& alpha = RealHelper::ONE);

		ColorValue(const Real& red, const Real& green, const Real& blue, const Real& alpha = RealHelper::ONE);

		~ColorValue();

		Real Red, Green, Blue, Alpha;

	private:
		
	};
}

#endif // ColourValue_h__


#pragma once
#ifndef StringUtils_h__
#define StringUtils_h__

#include "NiFrameEnginePCH.hpp"

namespace NiFrame
{
	class StringUtils
	{
	public:


		static String ToString( unsigned int );
		static String ToString( int );
		static String ToString( Real );

	private:

		StringUtils() {}
		~StringUtils() {}

	};

}

#endif // StringUtils_h__
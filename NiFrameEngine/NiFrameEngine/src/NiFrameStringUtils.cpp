#include "NiFrameEnginePCH.hpp"
#include "NiFrameStringUtils.hpp"

namespace NiFrame
{


	NiFrame::String StringUtils::ToString( unsigned int value )
	{
		return std::to_string( value );
	}

	NiFrame::String StringUtils::ToString( int value )
	{
		return std::to_string( value );
	}

	NiFrame::String StringUtils::ToString( Real value )
	{
		return std::to_string( value );
	}

}
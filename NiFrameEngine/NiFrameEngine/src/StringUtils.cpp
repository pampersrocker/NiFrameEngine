#include "NiFrameEnginePCH.h"
#include "StringUtils.h"

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
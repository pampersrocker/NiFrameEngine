#include "NFEnginePCH.hpp"
#include "NFStringUtils.hpp"

namespace nfe
{


	nfe::String StringUtils::ToString( unsigned int value )
	{
		return std::to_string( value );
	}

	nfe::String StringUtils::ToString( int value )
	{
		return std::to_string( value );
	}

	nfe::String StringUtils::ToString( Real value )
	{
		return std::to_string( value );
	}

}
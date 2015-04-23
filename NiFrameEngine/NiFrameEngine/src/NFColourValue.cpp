#include "NFEnginePCH.hpp"
#include "NFColourValue.hpp"

namespace nfe
{

	ColorValue::ColorValue() :
		Red( RealHelper::ZERO ),
		Green( RealHelper::ZERO ),
		Blue( RealHelper::ZERO ),
		Alpha( RealHelper::ZERO )
	{
	}

	ColorValue::ColorValue( const Real& value, const Real& alpha /*= RealHelper::ONE*/ ) :
		Red( value ),
		Green( value ),
		Blue( value ),
		Alpha( alpha )
	{

	}

	ColorValue::ColorValue( 
		const Real& red, const Real& green, const Real& blue, const Real& alpha /*= RealHelper::ONE*/ ) :
	Red( red ),
		Green( green ),
		Blue( blue ),
		Alpha( alpha )
	{

	}

	ColorValue::~ColorValue()
	{

	}
}


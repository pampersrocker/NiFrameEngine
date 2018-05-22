#include "NFEnginePCH.hpp"
#include "Utils/NFRational.hpp"

using namespace nfe;


nfe::Rational::~Rational()
{

}

nfe::Rational::Rational() :
m_Nominator(0),
m_Denominator(0)
{

}

nfe::Rational::Rational( int32 nominator, int32 denominator ) :
m_Nominator(nominator),
m_Denominator(denominator)
{

}

void nfe::Rational::SetDenominator( nfe::int32 val )
{
  m_Denominator = val;
}

nfe::int32 nfe::Rational::GetDenominator() const
{
  return m_Denominator;
}

void nfe::Rational::SetNominator( nfe::int32 val )
{
  m_Nominator = val;
}

nfe::int32 nfe::Rational::GetNominator() const
{
  return m_Nominator;
}

nfe::Real nfe::Rational::AsReal() const
{
  return static_cast< Real >( m_Nominator ) / static_cast< Real >( m_Denominator );
}

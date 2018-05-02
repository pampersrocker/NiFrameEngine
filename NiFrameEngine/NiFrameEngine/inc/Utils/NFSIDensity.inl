#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Density
  //////////////////////////////////////////////////////////////////////////

  inline
    Density::Density() :
    m_Value( 0 )
  {

  }

  inline
    Density::Density( const Density& density ) :
    m_Value( density.m_Value )
  {

  }


  inline
    float Density::Value() const
  {
    return m_Value;
  }

  inline
    Density& Density::operator-=( const Density& density )
  {
    m_Value -= density.m_Value;
    return *this;
  }

  inline
    Density Density::operator-( const Density& density ) const
  {
    Density val( m_Value );
    val -= density;
    return val;
  }

  inline
    Density& Density::operator+=( const Density& density )
  {
    m_Value += density.m_Value;
    return *this;
  }

  inline
    Density Density::operator+( const Density& density ) const
  {
    Density val( m_Value );
    val += density;
    return val;
  }

  inline
    Density operator "" _D( long double pa )
  {
    return Density(static_cast<Real>(pa));
  }

  inline
    Density::Density( Real value ) :
    m_Value( value )
  {

  }

  inline
    Density Density::operator*( Real scalar ) const
  {
    Density val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    KgM2S2Mixin Density::operator*( const Acceleration& acceleration ) const
  {
    return KgM2S2Mixin( m_Value * acceleration.m_Value );
  }

  inline
    Density& Density::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Density Density::operator/( Real scalar ) const
  {
    Density val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Density& Density::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }
  inline
    nfe::Density Density::operator-( ) const
  {
    return Density( -m_Value );
  }
  inline
    nfe::Density Density::operator+( ) const
  {
    return Density( m_Value );
  }
}

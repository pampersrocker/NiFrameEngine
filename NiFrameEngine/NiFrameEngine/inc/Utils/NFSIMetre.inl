#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Metre
  //////////////////////////////////////////////////////////////////////////

  inline
    Metre::Metre( const Metre& metre ) :
    m_Value( metre.m_Value )
  {

  }

  inline
    float Metre::Value() const
  {
    return m_Value;
  }
  inline
    Metre& Metre::operator-=( const Metre& metre )
  {
    m_Value -= metre.m_Value;
    return *this;
  }
  inline
    Metre::Metre() :
    m_Value( 0 )
  {

  }

  inline
    nfe::KgM2Mixin Metre::operator*( const Density& density ) const
  {
    return KgM2Mixin( m_Value * density.m_Value );
  }

  inline
    Metre& Metre::operator=( const Metre& metre )
  {
    m_Value = metre.m_Value;
    return *this;
  }

  inline
    Metre Metre::operator-( const Metre& metre ) const
  {
    Metre val( m_Value );
    val -= metre;
    return val;
  }

  inline
    Metre& Metre::operator+=( const Metre& metre )
  {
    m_Value += metre.m_Value;
    return *this;
  }

  inline
    Metre Metre::operator+( const Metre& metre ) const
  {
    Metre val( m_Value );
    val += metre;
    return val;
  }

  inline
    Metre operator "" _m( long double pa )
  {
    return Metre( pa );
  }

  inline
    Metre::Metre( Real value ) :
    m_Value( value )
  {

  }

  inline
    Metre Metre::operator*( Real scalar ) const
  {
    Metre val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Pascal Metre::operator*( const KgM2S2Mixin& mixin ) const
  {
    return Pascal( m_Value * mixin.m_Value );
  }

  inline
    Metre& Metre::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Metre Metre::operator/( Real scalar ) const
  {
    Metre val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Metre& Metre::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }

  inline
    nfe::Metre Metre::operator-( ) const
  {
    return Metre( -m_Value );
  }
  inline
    nfe::Metre Metre::operator+( ) const
  {
    return Metre( m_Value );
  }
}

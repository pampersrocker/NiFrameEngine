#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // KgM2Mixin
  //////////////////////////////////////////////////////////////////////////

  inline
    float KgM2Mixin::Value() const
  {
    return m_Value;
  }

  inline
    nfe::KgM2Mixin Density::operator*( const Metre& metre ) const
  {
    return KgM2Mixin( m_Value * metre.m_Value );
  }


  inline
    KgM2Mixin& KgM2Mixin::operator-=( const KgM2Mixin& mixin )
  {
    m_Value -= mixin.m_Value;
    return *this;
  }

  inline
    KgM2Mixin KgM2Mixin::operator-( const KgM2Mixin& mixin ) const
  {
    KgM2Mixin val( m_Value );
    val -= mixin;
    return val;
  }

  inline
    KgM2Mixin& KgM2Mixin::operator+=( const KgM2Mixin& mixin )
  {
    m_Value += mixin.m_Value;
    return *this;
  }

  inline
    KgM2Mixin KgM2Mixin::operator+( const KgM2Mixin& mixin ) const
  {
    KgM2Mixin val( m_Value );
    val += mixin;
    return val;
  }

  inline
    KgM2Mixin::KgM2Mixin( Real value ) :
    m_Value( value )
  {

  }

  inline
    KgM2Mixin KgM2Mixin::operator*( Real scalar ) const
  {
    KgM2Mixin val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Pascal KgM2Mixin::operator*( const Acceleration& acceleration ) const
  {
    return Pascal( acceleration.m_Value * m_Value );
  }

  inline
    KgM2Mixin& KgM2Mixin::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    KgM2Mixin KgM2Mixin::operator/( Real scalar ) const
  {
    KgM2Mixin val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    KgM2Mixin& KgM2Mixin::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }
}

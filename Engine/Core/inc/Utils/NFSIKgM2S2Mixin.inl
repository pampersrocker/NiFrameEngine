#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // KgM2S2Mixin
  //////////////////////////////////////////////////////////////////////////

  inline
    float KgM2S2Mixin::Value() const
  {
    return m_Value;
  }


  inline
    KgM2S2Mixin& KgM2S2Mixin::operator-=( const KgM2S2Mixin& mixin )
  {
    m_Value -= mixin.m_Value;
    return *this;
  }

  inline
    KgM2S2Mixin KgM2S2Mixin::operator-( const KgM2S2Mixin& mixin ) const
  {
    KgM2S2Mixin val( m_Value );
    val -= mixin;
    return val;
  }

  inline
    KgM2S2Mixin& KgM2S2Mixin::operator+=( const KgM2S2Mixin& mixin )
  {
    m_Value += mixin.m_Value;
    return *this;
  }

  inline
    KgM2S2Mixin KgM2S2Mixin::operator+( const KgM2S2Mixin& mixin ) const
  {
    KgM2S2Mixin val( m_Value );
    val += mixin;
    return val;
  }

  inline
    KgM2S2Mixin::KgM2S2Mixin( Real value ) :
    m_Value( value )
  {

  }

  inline
    KgM2S2Mixin KgM2S2Mixin::operator*( Real scalar ) const
  {
    KgM2S2Mixin val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Pascal KgM2S2Mixin::operator*( const Metre& metre ) const
  {
    return Pascal( metre.m_Value * m_Value );
  }

  inline
    KgM2S2Mixin& KgM2S2Mixin::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    KgM2S2Mixin KgM2S2Mixin::operator/( Real scalar ) const
  {
    KgM2S2Mixin val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    KgM2S2Mixin& KgM2S2Mixin::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }


}

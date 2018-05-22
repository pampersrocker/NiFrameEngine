#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // M3_S2Mixin
  //////////////////////////////////////////////////////////////////////////

  inline
    M3_S2Mixin::M3_S2Mixin() :
    m_Value( 0 )
  {

  }

  inline
    M3_S2Mixin::M3_S2Mixin( const M3_S2Mixin& smetre ) :
    m_Value( smetre.m_Value )
  {

  }


  inline
    float M3_S2Mixin::Value() const
  {
    return m_Value;
  }

  inline
    M3_S2Mixin& M3_S2Mixin::operator-=( const M3_S2Mixin& smetre )
  {
    m_Value -= smetre.m_Value;
    return *this;
  }

  inline
    M3_S2Mixin M3_S2Mixin::operator-( const M3_S2Mixin& smetre ) const
  {
    M3_S2Mixin val( m_Value );
    val -= smetre;
    return val;
  }

  inline
    M3_S2Mixin& M3_S2Mixin::operator+=( const M3_S2Mixin& smetre )
  {
    m_Value += smetre.m_Value;
    return *this;
  }

  inline
    M3_S2Mixin M3_S2Mixin::operator+( const M3_S2Mixin& smetre ) const
  {
    M3_S2Mixin val( m_Value );
    val += smetre;
    return val;
  }

  inline
    M3_S2Mixin::M3_S2Mixin( Real value ) :
    m_Value( value )
  {

  }

  inline
    M3_S2Mixin M3_S2Mixin::operator*( Real scalar ) const
  {
    M3_S2Mixin val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    M3_S2Mixin& M3_S2Mixin::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    M3_S2Mixin M3_S2Mixin::operator/( Real scalar ) const
  {
    M3_S2Mixin val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    M3_S2Mixin& M3_S2Mixin::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }


  inline
    nfe::M3_S2Mixin M3_S2Mixin::operator-( ) const
  {
    return M3_S2Mixin( -m_Value );
  }
  inline
    nfe::M3_S2Mixin M3_S2Mixin::operator+( ) const
  {
    return M3_S2Mixin( m_Value );
  }
}

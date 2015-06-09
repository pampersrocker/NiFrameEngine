#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // SquareMetre
  //////////////////////////////////////////////////////////////////////////

  inline
    SquareMetre::SquareMetre() :
    m_Value( 0 )
  {

  }

  inline
    SquareMetre::SquareMetre( const SquareMetre& smetre ) :
    m_Value( smetre.m_Value )
  {

  }


  inline
    float SquareMetre::Value() const
  {
    return m_Value;
  }

  inline
    SquareMetre& SquareMetre::operator-=( const SquareMetre& smetre )
  {
    m_Value -= smetre.m_Value;
    return *this;
  }

  inline
    SquareMetre SquareMetre::operator-( const SquareMetre& smetre ) const
  {
    SquareMetre val( m_Value );
    val -= smetre;
    return val;
  }

  inline
    SquareMetre& SquareMetre::operator+=( const SquareMetre& smetre )
  {
    m_Value += smetre.m_Value;
    return *this;
  }

  inline
    SquareMetre SquareMetre::operator+( const SquareMetre& smetre ) const
  {
    SquareMetre val( m_Value );
    val += smetre;
    return val;
  }

  inline
    SquareMetre operator "" _m2( long double pa )
  {
    return SquareMetre( pa );
  }

  inline
    SquareMetre::SquareMetre( Real value ) :
    m_Value( value )
  {

  }

  inline
    SquareMetre SquareMetre::operator*( Real scalar ) const
  {
    SquareMetre val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    SquareMetre& SquareMetre::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    SquareMetre SquareMetre::operator/( Real scalar ) const
  {
    SquareMetre val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    SquareMetre& SquareMetre::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }


  inline
    nfe::SquareMetre SquareMetre::operator-( ) const
  {
    return SquareMetre( -m_Value );
  }
  inline
    nfe::SquareMetre SquareMetre::operator+( ) const
  {
    return SquareMetre( m_Value );
  }

  inline
  nfe::M3_S2Mixin SquareMetre::operator*( const Acceleration& accel ) const
  {
    return M3_S2Mixin( m_Value * accel.m_Value );
  }


}

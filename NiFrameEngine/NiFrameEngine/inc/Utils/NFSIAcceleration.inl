#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Acceleration
  //////////////////////////////////////////////////////////////////////////

  inline
    Acceleration::Acceleration( const Acceleration& accel ) :
    m_Value( accel.m_Value )
  {

  }


  inline
    Acceleration::Acceleration() :
    m_Value( 0 )
  {

  }

  inline
    float Acceleration::Value() const
  {
    return m_Value;
  }

  inline
    Acceleration& Acceleration::operator-=( const Acceleration& acceleration )
  {
    m_Value -= acceleration.m_Value;
    return *this;
  }

  inline
    Acceleration Acceleration::operator-( const Acceleration& acceleration ) const
  {
    Acceleration val( m_Value );
    val -= acceleration;
    return val;
  }

  inline
    Acceleration& Acceleration::operator+=( const Acceleration& acceleration )
  {
    m_Value += acceleration.m_Value;
    return *this;
  }

  inline
    Acceleration Acceleration::operator+( const Acceleration& acceleration ) const
  {
    Acceleration val( m_Value );
    val += acceleration;
    return val;
  }

  inline
    Acceleration operator "" _a( long double acceleration )
  {
    return Acceleration( acceleration );
  }

  inline
    Acceleration::Acceleration( Real value ) :
    m_Value( value )
  {

  }

  inline
    Acceleration Acceleration::operator*( Real scalar ) const
  {
    Acceleration val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    KgM2S2Mixin Acceleration::operator*( const Density& density ) const
  {
    return KgM2S2Mixin( m_Value * density.m_Value );
  }

  inline
    Pascal Acceleration::operator*( const KgM2Mixin& mixin ) const
  {
    return Pascal( m_Value * mixin.m_Value );
  }

  inline
    Acceleration& Acceleration::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Acceleration Acceleration::operator/( Real scalar ) const
  {
    Acceleration val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Acceleration& Acceleration::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }

  inline
    nfe::Acceleration Acceleration::operator-( ) const
  {
    return Acceleration( -m_Value );
  }
  inline
    nfe::Acceleration Acceleration::operator+( ) const
  {
    return Acceleration( m_Value );
  }

  inline
  nfe::M3_S2Mixin Acceleration::operator*( const SquareMetre& smetre ) const
  {
    return M3_S2Mixin( m_Value*smetre.m_Value );
  }


}

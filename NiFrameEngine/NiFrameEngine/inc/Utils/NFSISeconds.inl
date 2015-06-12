#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Seconds
  //////////////////////////////////////////////////////////////////////////

  inline
    Seconds::Seconds( const Seconds& accel ) :
    m_Value( accel.m_Value )
  {

  }


  inline
    Seconds::Seconds() :
    m_Value( 0 )
  {

  }

  inline
    float Seconds::Value() const
  {
    return m_Value;
  }


  inline
    Seconds& Seconds::operator-=( const Seconds& seconds )
  {
    m_Value -= seconds.m_Value;
    return *this;
  }

  inline
    Seconds Seconds::operator-( const Seconds& seconds ) const
  {
    Seconds val( m_Value );
    val -= seconds;
    return val;
  }

  inline
    Seconds& Seconds::operator+=( const Seconds& seconds )
  {
    m_Value += seconds.m_Value;
    return *this;
  }

  inline
    Seconds Seconds::operator+( const Seconds& seconds ) const
  {
    Seconds val( m_Value );
    val += seconds;
    return val;
  }

  inline
    Seconds operator "" _s( long double seconds )
  {
    return Seconds( seconds );
  }

  inline
    Seconds::Seconds( Real value ) :
    m_Value( value )
  {

  }

  inline
    Seconds Seconds::operator*( Real scalar ) const
  {
    Seconds val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Seconds& Seconds::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Seconds Seconds::operator/( Real scalar ) const
  {
    Seconds val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Seconds& Seconds::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }

  inline
    nfe::Seconds Seconds::operator-( ) const
  {
    return Seconds( -m_Value );
  }
  inline
    nfe::Seconds Seconds::operator+( ) const
  {
    return Seconds( m_Value );
  }

  inline
  nfe::Seconds Seconds::FromFloat( Real value )
  {
    return Seconds( value );
  }

  inline
    nfe::VolumeVelocity Seconds::operator*( const M3_S2Mixin& volvel ) const
  {
    return VolumeVelocity( m_Value * volvel.m_Value );
  }

  inline
  nfe::Volume Seconds::operator*( const VolumeVelocity& volvel ) const
  {
    return Volume( m_Value*volvel.m_Value );
  }




}

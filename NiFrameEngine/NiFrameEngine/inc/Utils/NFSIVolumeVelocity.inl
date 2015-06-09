#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // VolumeVelocity
  //////////////////////////////////////////////////////////////////////////

  inline
    VolumeVelocity::VolumeVelocity( const VolumeVelocity& accel ) :
    m_Value( accel.m_Value )
  {

  }


  inline
    VolumeVelocity::VolumeVelocity() :
    m_Value( 0 )
  {

  }

  inline
    float VolumeVelocity::Value() const
  {
    return m_Value;
  }


  inline
    VolumeVelocity& VolumeVelocity::operator-=( const VolumeVelocity& volumeVelocity )
  {
    m_Value -= volumeVelocity.m_Value;
    return *this;
  }

  inline
    VolumeVelocity VolumeVelocity::operator-( const VolumeVelocity& volumeVelocity ) const
  {
    VolumeVelocity val( m_Value );
    val -= volumeVelocity;
    return val;
  }

  inline
    VolumeVelocity& VolumeVelocity::operator+=( const VolumeVelocity& volumeVelocity )
  {
    m_Value += volumeVelocity.m_Value;
    return *this;
  }

  inline
    VolumeVelocity VolumeVelocity::operator+( const VolumeVelocity& volumeVelocity ) const
  {
    VolumeVelocity val( m_Value );
    val += volumeVelocity;
    return val;
  }

  inline
    VolumeVelocity operator "" _Q( long double volumeVelocity )
  {
    return VolumeVelocity( volumeVelocity );
  }

  inline
    VolumeVelocity::VolumeVelocity( Real value ) :
    m_Value( value )
  {

  }

  inline
    VolumeVelocity VolumeVelocity::operator*( Real scalar ) const
  {
    VolumeVelocity val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    VolumeVelocity& VolumeVelocity::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    VolumeVelocity VolumeVelocity::operator/( Real scalar ) const
  {
    VolumeVelocity val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    VolumeVelocity& VolumeVelocity::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }

  inline
    nfe::VolumeVelocity VolumeVelocity::operator-( ) const
  {
    return VolumeVelocity( -m_Value );
  }
  inline
    nfe::VolumeVelocity VolumeVelocity::operator+( ) const
  {
    return VolumeVelocity( m_Value );
  }

  inline
  VolumeVelocity& VolumeVelocity::operator=( const VolumeVelocity& vel )
  {
    m_Value = vel.m_Value;
    return *this;
  }




}

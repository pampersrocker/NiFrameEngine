#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Volume
  //////////////////////////////////////////////////////////////////////////

  inline
    Volume::Volume() :
    m_Value( 0 )
  {

  }

  inline
    Volume::Volume( const Volume& pascal ) :
    m_Value( pascal.m_Value )
  {

  }


  inline
    float Volume::Value() const
  {
    return m_Value;
  }

  inline
    Volume& Volume::operator-=( const Volume& pascal )
  {
    m_Value -= pascal.m_Value;
    return *this;
  }

  inline
    Volume Volume::operator-( const Volume& pascal ) const
  {
    Volume val( m_Value );
    val -= pascal;
    return val;
  }

  inline
    Volume& Volume::operator+=( const Volume& pascal )
  {
    m_Value += pascal.m_Value;
    return *this;
  }

  inline
    Volume Volume::operator+( const Volume& pascal ) const
  {
    Volume val( m_Value );
    val += pascal;
    return val;
  }

  inline
    Volume operator "" _m3( long double pa )
  {
    return Volume( pa );
  }

  inline
    Volume::Volume( Real value ) :
    m_Value( value )
  {

  }

  inline
    Volume Volume::operator*( Real scalar ) const
  {
    Volume val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Volume& Volume::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Volume Volume::operator/( Real scalar ) const
  {
    Volume val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Volume& Volume::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }


  inline
    nfe::Volume Volume::operator-( ) const
  {
    return Volume( -m_Value );
  }
  inline
    nfe::Volume Volume::operator+( ) const
  {
    return Volume( m_Value );
  }

  inline
    nfe::Acceleration Volume::operator/( const KgM2Mixin& mixin ) const
  {
    return Acceleration( m_Value / mixin.m_Value );
  }

  inline
    nfe::Metre Volume::operator/( const SquareMetre& smetre ) const
  {
    return Metre( m_Value / smetre.m_Value );
  }


}

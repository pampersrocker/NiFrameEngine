#pragma once

namespace nfe
{
  //////////////////////////////////////////////////////////////////////////
  // Pascal
  //////////////////////////////////////////////////////////////////////////

  inline
    Pascal::Pascal() :
    m_Value( 0 )
  {

  }

  inline
    Pascal::Pascal( const Pascal& pascal ) :
    m_Value( pascal.m_Value )
  {

  }


  inline
    float Pascal::Value() const
  {
    return m_Value;
  }

  inline
    Pascal& Pascal::operator-=( const Pascal& pascal )
  {
    m_Value -= pascal.m_Value;
    return *this;
  }

  inline
    Pascal Pascal::operator-( const Pascal& pascal ) const
  {
    Pascal val( m_Value );
    val -= pascal;
    return val;
  }

  inline
    Pascal& Pascal::operator+=( const Pascal& pascal )
  {
    m_Value += pascal.m_Value;
    return *this;
  }

  inline
    Pascal Pascal::operator+( const Pascal& pascal ) const
  {
    Pascal val( m_Value );
    val += pascal;
    return val;
  }

  inline
    Pascal operator "" _Pa( long double pa )
  {
    return Pascal( pa );
  }

  inline
    Pascal::Pascal( Real value ) :
    m_Value( value )
  {

  }

  inline
    Pascal Pascal::operator*( Real scalar ) const
  {
    Pascal val( m_Value );
    val *= scalar;
    return val;
  }

  inline
    Pascal& Pascal::operator*=( Real scalar )
  {
    m_Value *= scalar;
    return *this;
  }

  inline
    Pascal Pascal::operator/( Real scalar ) const
  {
    Pascal val( m_Value );
    val /= scalar;
    return val;

  }

  inline
    Pascal& Pascal::operator/=( Real scalar )
  {
    m_Value /= scalar;
    return *this;
  }


  inline
    nfe::Pascal Pascal::operator-( ) const
  {
    return Pascal( -m_Value );
  }
  inline
    nfe::Pascal Pascal::operator+( ) const
  {
    return Pascal( m_Value );
  }

  inline
    nfe::Acceleration Pascal::operator/( const KgM2Mixin& mixin ) const
  {
    return Acceleration( m_Value / mixin.m_Value );
  }
}

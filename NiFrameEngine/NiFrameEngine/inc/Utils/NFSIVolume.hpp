#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // m^3
  class NIFRAME_API Volume
  {
  public:

    Volume();
    Volume( const Volume& volume );


    Volume operator +( const Volume& volume ) const;
    Volume& operator +=( const Volume& volume );
    Volume operator -( const Volume& volume ) const;
    Volume& operator -=( const Volume& volume );

    Volume operator *( Real scalar ) const;
    Volume& operator *=( Real scalar );
    Volume operator /( Real scalar ) const;
    Volume& operator /=( Real scalar );

    Acceleration operator /( const KgM2Mixin& mixin ) const;

    Metre operator /( const SquareMetre& smetre ) const;

    Volume operator -( ) const;
    Volume operator +( ) const;

    FRIEND_SI;


    friend Volume operator "" _m3( long double value );



    float Value() const;

  private:
    explicit Volume( Real value );

    Real m_Value;
  };
}

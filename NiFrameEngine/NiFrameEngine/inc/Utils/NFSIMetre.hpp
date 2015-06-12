#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // m
  class NIFRAME_API Metre
  {
  public:

    explicit Metre( Real value );
    Metre();

    Metre( const Metre& metre );

    Metre& operator = ( const Metre& metre );

    Metre operator +( const Metre& Metre ) const;
    Metre& operator +=( const Metre& Metre );
    Metre operator -( const Metre& Metre ) const;
    Metre& operator -=( const Metre& Metre );

    Metre operator *( Real scalar ) const;
    Metre& operator *=( Real scalar );
    Metre operator /( Real scalar ) const;
    Metre& operator /=( Real scalar );

    Metre operator -( ) const;
    Metre operator +( ) const;

    Pascal operator *( const KgM2S2Mixin& mixin ) const;
    KgM2Mixin operator *( const Density& density ) const;
    SquareMetre operator *( const Metre& metre ) const;

    friend Metre operator "" _m( long double value );


    FRIEND_SI;


    float Value() const;

  private:

    Real m_Value;
  };
}

#pragma once

#include "NFEnginePCH.hpp"
namespace nfe
{
  // kg/(m^3)
  class NIFRAME_API Density
  {
  public:

    Density();
    Density( const Density& density );

    Density operator +( const Density& Density ) const;
    Density& operator +=( const Density& Density );
    Density operator -( const Density& Density ) const;
    Density& operator -=( const Density& Density );

    Density operator *( Real scalar ) const;
    Density& operator *=( Real scalar );
    Density operator /( Real scalar ) const;
    Density& operator /=( Real scalar );

    KgM2S2Mixin operator *( const Acceleration& acceleration ) const;
    KgM2Mixin operator *( const Metre& metre ) const;

    friend class KgM2S2Mixin;
    friend class Acceleration;
    friend class Metre;
    Density operator -( ) const;
    Density operator +( ) const;

    friend Density operator "" _D( long double value );


    float Value() const;

  private:
    explicit Density( Real value );

    Real m_Value;
  };
}

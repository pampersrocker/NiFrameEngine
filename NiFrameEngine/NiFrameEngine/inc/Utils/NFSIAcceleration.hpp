#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // m/s^2
  class NIFRAME_API Acceleration
  {
  public:

    Acceleration();

    Acceleration( const Acceleration& accel );

    Acceleration operator +( const Acceleration& Acceleration ) const;
    Acceleration& operator +=( const Acceleration& Acceleration );
    Acceleration operator -( const Acceleration& Acceleration ) const;
    Acceleration& operator -=( const Acceleration& Acceleration );

    Acceleration operator *( Real scalar ) const;
    Acceleration& operator *=( Real scalar );
    Acceleration operator /( Real scalar ) const;
    Acceleration& operator /=( Real scalar );

    KgM2S2Mixin operator *( const Density& density ) const;

    M3_S2Mixin operator *( const SquareMetre& smetre ) const;

    Pascal operator *( const KgM2Mixin& mixin ) const;


    Acceleration operator -( ) const;
    Acceleration operator +( ) const;

    friend class Density;
    friend class KgM2Mixin;
    friend class Pascal;
    friend class M3_S2Mixin;
    friend class SquareMetre;

    friend Acceleration operator "" _a( long double value );


    float Value() const;

  private:
    explicit Acceleration( Real value );

    Real m_Value;
  };
}

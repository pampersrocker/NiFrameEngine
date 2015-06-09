#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // m^2
  class NIFRAME_API M3_S2Mixin
  {
  public:

    M3_S2Mixin();
    M3_S2Mixin( const M3_S2Mixin& M3_S2Mixin );


    M3_S2Mixin operator +( const M3_S2Mixin& M3_S2Mixin ) const;
    M3_S2Mixin& operator +=( const M3_S2Mixin& M3_S2Mixin );
    M3_S2Mixin operator -( const M3_S2Mixin& M3_S2Mixin ) const;
    M3_S2Mixin& operator -=( const M3_S2Mixin& M3_S2Mixin );

    M3_S2Mixin operator *( Real scalar ) const;
    M3_S2Mixin& operator *=( Real scalar );
    M3_S2Mixin operator /( Real scalar ) const;
    M3_S2Mixin& operator /=( Real scalar );

    M3_S2Mixin operator -( ) const;
    M3_S2Mixin operator +( ) const;

    friend class Metre;
    friend class Acceleration;
    friend class Density;
    friend class KgM2Mixin;
    friend class KgM2S2Mixin;
    friend class SquareMetre;
    friend class Seconds;

    float Value() const;

  private:
    explicit M3_S2Mixin( Real value );

    Real m_Value;
  };
}

#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // m^2
  class NIFRAME_API SquareMetre
  {
  public:

    SquareMetre();
    SquareMetre( const SquareMetre& SquareMetre );


    SquareMetre operator +( const SquareMetre& SquareMetre ) const;
    SquareMetre& operator +=( const SquareMetre& SquareMetre );
    SquareMetre operator -( const SquareMetre& SquareMetre ) const;
    SquareMetre& operator -=( const SquareMetre& SquareMetre );

    SquareMetre operator *( Real scalar ) const;
    SquareMetre& operator *=( Real scalar );
    SquareMetre operator /( Real scalar ) const;
    SquareMetre& operator /=( Real scalar );

    SquareMetre operator -( ) const;
    SquareMetre operator +( ) const;

    M3_S2Mixin operator *( const Acceleration& accel ) const;

    friend class Metre;
    friend class Acceleration;
    friend class Density;
    friend class KgM2Mixin;
    friend class KgM2S2Mixin;

    friend SquareMetre operator "" _m2( long double value );



    float Value() const;

  private:
    explicit SquareMetre( Real value );

    Real m_Value;
  };
}

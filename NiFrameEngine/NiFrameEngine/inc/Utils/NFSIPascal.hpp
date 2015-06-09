#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  // kg/(m*s^2)
  class NIFRAME_API Pascal
  {
  public:

    Pascal();
    Pascal( const Pascal& pascal );


    Pascal operator +( const Pascal& pascal ) const;
    Pascal& operator +=( const Pascal& pascal );
    Pascal operator -( const Pascal& pascal ) const;
    Pascal& operator -=( const Pascal& pascal );

    Pascal operator *( Real scalar ) const;
    Pascal& operator *=( Real scalar );
    Pascal operator /( Real scalar ) const;
    Pascal& operator /=( Real scalar );

    Acceleration operator /( const KgM2Mixin& mixin ) const;

    Pascal operator -( ) const;
    Pascal operator +( ) const;

    friend class Metre;
    friend class Acceleration;
    friend class Density;
    friend class KgM2Mixin;
    friend class KgM2S2Mixin;

    friend Pascal operator "" _Pa( long double value );



    float Value() const;

  private:
    explicit Pascal( Real value );

    Real m_Value;
  };
}

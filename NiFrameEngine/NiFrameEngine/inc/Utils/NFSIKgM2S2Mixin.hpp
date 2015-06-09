#pragma once

namespace nfe
{
  // kg/(m^2*s^2)
  class NIFRAME_API KgM2S2Mixin
  {
  public:


    KgM2S2Mixin operator +( const KgM2S2Mixin& KgM2S2Mixin ) const;
    KgM2S2Mixin& operator +=( const KgM2S2Mixin& KgM2S2Mixin );
    KgM2S2Mixin operator -( const KgM2S2Mixin& KgM2S2Mixin ) const;
    KgM2S2Mixin& operator -=( const KgM2S2Mixin& KgM2S2Mixin );

    KgM2S2Mixin operator *( Real scalar ) const;
    KgM2S2Mixin& operator *=( Real scalar );
    KgM2S2Mixin operator /( Real scalar ) const;
    KgM2S2Mixin& operator /=( Real scalar );

    Pascal operator *( const Metre& metre ) const;

    friend class Metre;
    friend class Density;
    friend class Acceleration;

    float Value() const;

  private:
    explicit KgM2S2Mixin( Real value );

    Real m_Value;
  };
}

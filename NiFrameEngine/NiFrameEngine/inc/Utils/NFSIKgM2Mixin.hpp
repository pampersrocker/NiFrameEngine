#pragma once

namespace nfe
{
  // kg/(m^2)
  class NIFRAME_API KgM2Mixin
  {
  public:


    KgM2Mixin operator +( const KgM2Mixin& KgM2Mixin ) const;
    KgM2Mixin& operator +=( const KgM2Mixin& KgM2Mixin );
    KgM2Mixin operator -( const KgM2Mixin& KgM2Mixin ) const;
    KgM2Mixin& operator -=( const KgM2Mixin& KgM2Mixin );

    KgM2Mixin operator *( Real scalar ) const;
    KgM2Mixin& operator *=( Real scalar );
    KgM2Mixin operator /( Real scalar ) const;
    KgM2Mixin& operator /=( Real scalar );

    Pascal operator *( const Acceleration& acceleration ) const;

    friend class Acceleration;
    friend class Metre;
    friend class Density;
    friend class Pascal;


    float Value() const;

  private:
    explicit KgM2Mixin( Real value );

    Real m_Value;
  };
}

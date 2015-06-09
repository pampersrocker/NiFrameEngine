#pragma once

namespace nfe
{
  // s
  class NIFRAME_API Seconds
  {
  public:

    Seconds();

    Seconds( const Seconds& accel );

    Seconds operator +( const Seconds& Seconds ) const;
    Seconds& operator +=( const Seconds& Seconds );
    Seconds operator -( const Seconds& Seconds ) const;
    Seconds& operator -=( const Seconds& Seconds );

    Seconds operator *( Real scalar ) const;
    Seconds& operator *=( Real scalar );
    Seconds operator /( Real scalar ) const;
    Seconds& operator /=( Real scalar );


    Seconds operator -( ) const;
    Seconds operator +( ) const;

    VolumeVelocity operator*( const M3_S2Mixin& volvel ) const;

    friend class Density;
    friend class KgM2Mixin;
    friend class Pascal;

    friend Seconds operator "" _s( long double value );

    static Seconds FromFloat( Real value );


    float Value() const;

  private:
    explicit Seconds( Real value );

    Real m_Value;
  };
}

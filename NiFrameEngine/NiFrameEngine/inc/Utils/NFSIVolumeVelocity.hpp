#pragma once

namespace nfe
{
  // m^3/s
  class NIFRAME_API VolumeVelocity
  {
  public:

    VolumeVelocity();

    VolumeVelocity( const VolumeVelocity& accel );

    VolumeVelocity& operator = ( const VolumeVelocity& vel );

    VolumeVelocity operator +( const VolumeVelocity& VolumeVelocity ) const;
    VolumeVelocity& operator +=( const VolumeVelocity& VolumeVelocity );
    VolumeVelocity operator -( const VolumeVelocity& VolumeVelocity ) const;
    VolumeVelocity& operator -=( const VolumeVelocity& VolumeVelocity );

    VolumeVelocity operator *( Real scalar ) const;
    VolumeVelocity& operator *=( Real scalar );
    VolumeVelocity operator /( Real scalar ) const;
    VolumeVelocity& operator /=( Real scalar );


    VolumeVelocity operator -( ) const;
    VolumeVelocity operator +( ) const;

    friend class Density;
    friend class KgM2Mixin;
    friend class Pascal;
    friend class Seconds;

    friend VolumeVelocity operator "" _Q( long double value );


    float Value() const;

  private:
    explicit VolumeVelocity( Real value );

    Real m_Value;
  };
}

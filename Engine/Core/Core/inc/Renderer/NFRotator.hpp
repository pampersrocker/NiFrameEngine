#pragma once

#include "NFEnginePCH.hpp"

namespace nfe
{
  class NIFRAME_API Rotator
  {
  public:
    Rotator( const Radian& roll = Radian( 0 ), const Radian& pitch = Radian( 0 ), const Radian& yaw = Radian( 0 ) );
    ~Rotator();
    const nfe::Radian& Roll() const;
    void Roll( const nfe::Radian& val );
    const nfe::Radian& Pitch() const;
    void Pitch( const nfe::Radian& val );
    const nfe::Radian& Yaw() const;
    void Yaw( const nfe::Radian& val );

    Vector3 GetRadianVector() const;
    Vector3 GetDegreeVector() const;

  private:
    Radian m_Roll;
    Radian m_Pitch;
    Radian m_Yaw;
  };
}

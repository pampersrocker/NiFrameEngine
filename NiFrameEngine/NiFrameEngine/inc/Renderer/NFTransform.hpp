#pragma once

#include "NFEnginePCH.hpp"
#include "NFRotator.hpp"

namespace nfe
{
  class NIFRAME_DLL_EXPORT Transform
  {
  public:
    Transform(const Vector3& position = Vector3(0),
      const Rotator& rotation = Rotator(),
      const Vector3& scale = Vector3( 0 ) );
    ~Transform();

    const nfe::Vector3& Position() const;
    void Position( const nfe::Vector3& val );
    const nfe::Vector3& Scale() const;
    void Scale( const nfe::Vector3& val );
    const nfe::Rotator& Rotation() const;
    void Rotation( const nfe::Rotator& val );
  private:
    Vector3 m_Position;
    Rotator m_Rotation;
    Vector3 m_Scale;


  };
}

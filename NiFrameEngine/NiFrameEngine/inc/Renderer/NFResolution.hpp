#pragma once
#ifndef NiFrameResolution_h__
  #define NiFrameResolution_h__

  #include "NFEnginePCH.hpp"
  #include "NFStringableObject.hpp"
  #include "NFStringUtils.hpp"
  #include "Utils/NFRational.hpp"

namespace nfe
{
  class NIFRAME_DLL_EXPORT Resolution :
    public IStringableObject
  {
  public:
    Resolution();
    Resolution( Resolution&& rhs );

    Resolution( uint32 width, uint32 height, const Rational& refreshRate = Rational(60,1) );
    virtual ~Resolution();

    virtual String ToString() const override;

    uint32 GetWidth( void ) const;

    uint32 GetHeight( void ) const;

    const Rational& GetRefreshRate( void ) const;

  private:

    uint32 m_Width, m_Height;
    Rational m_RefreshRate;
  };
}

#endif  // NiFrameResolution_h__

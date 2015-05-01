#pragma once
#ifndef NiFrameResolution_h__
  #define NiFrameResolution_h__

  #include "NFEnginePCH.hpp"
  #include "NFStringableObject.hpp"
  #include "NFStringUtils.hpp"

namespace nfe
{
  class NIFRAME_DLL_EXPORT Resolution :
    public IStringableObject
  {
  public:
    Resolution();
    Resolution( Resolution&& rhs );

    Resolution( uint32 width, uint32 height, uint32 refreshRate = 60 );
    virtual ~Resolution();

    virtual String ToString() const override;

    uint32 GetWidth( void ) const;

    uint32 GetHeight( void ) const;

    uint32 GetRefreshRate( void ) const;

  private:

    uint32 m_Width, m_Height, m_RefreshRate;
  };
}

#endif  // NiFrameResolution_h__

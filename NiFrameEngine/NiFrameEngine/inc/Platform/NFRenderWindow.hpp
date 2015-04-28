#pragma once

#include "NFEnginePCH.hpp"
#include "Renderer/NFResolution.hpp"

namespace nfe
{
#ifdef WIN32
  typedef HWND NativeWindow;
#elif defined(ORBIS)
  // There is no actual Window on the PS4 but we need a type anyway
  typeodef uint32 NativeWindow;
#endif

  class NIFRAME_DLL_EXPORT RenderWindow
  {
  public:
    RenderWindow() = default;
    virtual ~RenderWindow();
    void Initialize( NativeWindow nativeWindow, const Resolution& resolution );
    const Resolution& GetResolution() const;
    virtual void SetResolution( const Resolution& resolution );

    NativeWindow GetNativeHandle() const;

  private:

    NativeWindow m_NativeHandle;
    Resolution m_Resolution;
  };

}

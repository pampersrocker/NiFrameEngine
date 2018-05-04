#pragma once

#include "NFEnginePCH.hpp"
#include "Renderer/NFResolution.hpp"

namespace nfe
{
#ifdef PLATFORM_WINDOWS
  typedef HWND NativeWindow;
#elif defined(PLATFORM_PS4)
  // There is no actual Window on the PS4 but we need a type anyway
  typedef uint32 NativeWindow;
#endif

  class NIFRAME_API RenderWindow
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

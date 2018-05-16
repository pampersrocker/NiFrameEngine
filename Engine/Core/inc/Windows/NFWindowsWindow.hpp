#pragma once

#include "Platform/NFPlatformTypes.hpp"

namespace nfe
{


  class NIFRAME_API WindowsWindow
  {
  public:
    WindowsWindow(const String& WindowName);
    virtual ~WindowsWindow();
    void Create(const Resolution& resolution);
    const Resolution& GetResolution() const;
    virtual void SetResolution(const Resolution& resolution);



    NFHandle GetNativeHandle() const;

  private:

    String WindowName;
    NFHandle m_NativeHandle;
    Resolution m_Resolution;
  };

  typedef WindowsWindow Window;

}

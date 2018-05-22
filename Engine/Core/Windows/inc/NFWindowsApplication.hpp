#pragma once

#include "Platform/NFPlatformTypes.hpp"
#include "NFSTL/NFVector.hpp"


namespace nfe
{
  class WindowsWindow;

  class NIFRAME_API WindowsApplication
  {
  public:
    WindowsApplication(NFInstance Instance);
    ~WindowsApplication();

    static LRESULT CALLBACK WindowProc(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam);


    static LPCTSTR ClassName;

    HINSTANCE GetInstance() const;
    ATOM GetRegisteredWindowClass() const;

    static WindowsApplication* Get();

    void RegisterWindow(WindowsWindow* Window);
    void UnregisterWindow(WindowsWindow* Window);

  private:

    static WindowsApplication* Application;

    Vector< WindowsWindow*> ActiveWindows;

    ATOM RegisteredClass;

    HINSTANCE Instance;
  };

}

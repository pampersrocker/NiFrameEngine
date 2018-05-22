#include "NFWindowsPCH.hpp"
#include "NFWindowsApplication.hpp"

LPCTSTR nfe::WindowsApplication::ClassName = "NFEngineWindow";


HINSTANCE nfe::WindowsApplication::GetInstance() const
{
  return Instance;
}


ATOM nfe::WindowsApplication::GetRegisteredWindowClass() const
{
  return RegisteredClass;
}

nfe::WindowsApplication* nfe::WindowsApplication::Get()
{
  return Application;
}


void nfe::WindowsApplication::RegisterWindow(WindowsWindow* Window)
{
  ActiveWindows.Add(Window);
}


void nfe::WindowsApplication::UnregisterWindow(WindowsWindow* Window)
{
  ActiveWindows.Remove(Window);
}

nfe::WindowsApplication* nfe::WindowsApplication::Application = nullptr;

nfe::WindowsApplication::WindowsApplication(NFInstance InInstance)
  : Instance(InInstance)
{
  Application = this;

  WNDCLASSEX ClassEx;
  MemZero(&ClassEx, sizeof(WNDCLASSEX));

  ClassEx.cbSize = sizeof(WNDCLASSEX);
  ClassEx.style = CS_DBLCLKS;
  ClassEx.lpfnWndProc = &WindowProc;
  ClassEx.cbClsExtra = 0;
  ClassEx.hInstance = Instance;
  ClassEx.hIcon = nullptr;
  ClassEx.hCursor = nullptr;
  ClassEx.hbrBackground = nullptr;
  ClassEx.lpszMenuName = nullptr;
  ClassEx.lpszClassName = ClassName;
  ClassEx.hIconSm = nullptr;

  RegisteredClass = ::RegisterClassEx(&ClassEx);

  NF_ASSERT(RegisteredClass != 0, "Failed to register windows class");
}


nfe::WindowsApplication::~WindowsApplication()
{
  Application = nullptr;
}

LRESULT CALLBACK nfe::WindowsApplication::WindowProc(HWND Handle, UINT Message, WPARAM WParam, LPARAM LParam)
{
  return DefWindowProc(Handle, Message, WParam, LParam);
}

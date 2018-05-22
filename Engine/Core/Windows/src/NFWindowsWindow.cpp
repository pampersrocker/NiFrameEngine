#include "NFEnginePCH.hpp"
#include "NFWindowsWindow.hpp"
#include "NFWindowsApplication.hpp"

void nfe::WindowsWindow::Create(const Resolution& Resolution)
{
  m_Resolution = Resolution;

  DWORD Style = 0
    | WS_BORDER // Add border
    | WS_CAPTION // Add title
    | WS_MAXIMIZEBOX // Add maximizebox
    | WS_MINIMIZEBOX // Add minimizebox
    | WS_VISIBLE // Window is per default visible (not minimized or maximized)
    ;


  DWORD ExtendedStyle = 0;
  ExtendedStyle |= WS_EX_APPWINDOW; // Show on taskbar
  ExtendedStyle |= WS_EX_LAYERED; // Support alpha blended windows
  ExtendedStyle |= WS_EX_LEFT; // Left sided orientation

  WindowsApplication* Application = WindowsApplication::Get();

  NF_ASSERT(Application, "Trying to create a window without an application.");

  m_NativeHandle = CreateWindowEx(
    ExtendedStyle,
    MAKEINTATOM(Application->GetRegisteredWindowClass()),
    WindowName.c_str(),
    Style,
    CW_USEDEFAULT,
    CW_USEDEFAULT,
    Resolution.GetWidth(),
    Resolution.GetHeight(),
    nullptr,
    nullptr,
    Application->GetInstance(),
    nullptr
  );

  NF_ASSERT(m_NativeHandle != INVALID_HANDLE_VALUE, "Failed to create window");
}

const nfe::Resolution& nfe::WindowsWindow::GetResolution() const
{
  return m_Resolution;
}

void nfe::WindowsWindow::SetResolution(const Resolution& resolution)
{
  m_Resolution = resolution;
  // TODO apply to window
}

NFHandle nfe::WindowsWindow::GetNativeHandle() const
{
  return m_NativeHandle;
}

nfe::WindowsWindow::WindowsWindow(const String& InWindowName)
  : WindowName(InWindowName)
{
  
}

nfe::WindowsWindow::~WindowsWindow()
{

}

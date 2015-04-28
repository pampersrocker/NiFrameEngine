#include "NFEnginePCH.hpp"
#include "Platform/NFRenderWindow.hpp"

using namespace nfe;


nfe::NativeWindow nfe::RenderWindow::GetNativeHandle() const
{
  return m_NativeHandle;
}

void nfe::RenderWindow::SetResolution( const Resolution& resolution )
{
  m_Resolution = resolution;
}

const Resolution& nfe::RenderWindow::GetResolution() const
{
  return m_Resolution;
}

void nfe::RenderWindow::Initialize( NativeWindow nativeWindow, const Resolution& resolution )
{
  m_NativeHandle = nativeWindow;
  m_Resolution = resolution;
}

nfe::RenderWindow::~RenderWindow()
{

}

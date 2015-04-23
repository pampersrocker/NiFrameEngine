#include "NFEnginePCH.hpp"
#include "NFSettingsDialog.hpp"

#include "NFRenderDevice.hpp"
#include "NFDllEntryPoint.hpp"
#include "NFPrerequisites.hpp"
#include "NFRenderDeviceParameters.hpp"



namespace nfe
{
  //INT_PTR CALLBACK g_DialogProc( _In_ HWND hwndDlg, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam )
  //{
  //  return SettingsDialog::DialogProc(hwndDlg, uMsg, wParam, lParam);
  //}
  SettingsDialog* SettingsDialog::STATIC_DIALOG = nullptr;

  SettingsDialog::SettingsDialog( RenderDevice* renderDevice ) :
    m_RenderDevice( renderDevice )
  {
    assert(STATIC_DIALOG == nullptr);

    STATIC_DIALOG = this;
  }

  SettingsDialog::~SettingsDialog()
  {
    STATIC_DIALOG = nullptr;
  }

  void SettingsDialog::ShowDialog( SelectedRenderDevVals* values )
  {
    const RenderDeviceParams * renderDeviceParams = m_RenderDevice->GetRenderParams();

  }

}
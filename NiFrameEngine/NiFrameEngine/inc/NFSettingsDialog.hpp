#pragma once
#ifndef SettingsDialog_h__
#define SettingsDialog_h__

#include "NFEnginePCH.hpp"
#include "NFRenderDevice.hpp"

namespace nfe
{
  class RenderDevice;

  class SettingsDialog
  {
  public:
    SettingsDialog( RenderDevice* renderDevice );
    ~SettingsDialog();

    void ShowDialog( SelectedRenderDevVals* values );

    

  private:

    RenderDevice* m_RenderDevice;
    static SettingsDialog* STATIC_DIALOG;

    static INT_PTR CALLBACK DialogProc(
      _In_  HWND hwndDlg,
      _In_  UINT uMsg,
      _In_  WPARAM wParam,
      _In_  LPARAM lParam
      );

    static INT_PTR CALLBACK ProcessCommandMessage( WPARAM wParam, HWND hwndDlg );


  };

}

#endif // SettingsDialog_h__

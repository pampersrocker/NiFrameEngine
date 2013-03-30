#include "NiFrameEnginePCH.h"
#include "NiFrameSettingsDialog.h"

#include "NiFrameRenderDevice.h"
#include "DllEntryPoint.h"



namespace NiFrame
{
	//INT_PTR CALLBACK g_DialogProc( _In_ HWND hwndDlg, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam )
	//{
	//	return SettingsDialog::DialogProc(hwndDlg, uMsg, wParam, lParam);
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


		DialogBox(
			DllEntryPoint::GetInstance(), 
			MAKEINTRESOURCE(IDD_OPTIONS_DIALOG), 
			nullptr, 
			(DLGPROC)SettingsDialog::DialogProc );

	}

	INT_PTR CALLBACK SettingsDialog::DialogProc( _In_ HWND hwndDlg, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam )
	{
		switch (uMsg)
		{
		case WM_INITDIALOG:

			return true;
			break;
		case WM_CLOSE:
			EndDialog(hwndDlg, WM_CLOSE);

			return true;
			break;
		case WM_COMMAND:
			return ProcessCommandMessage(wParam, hwndDlg);

			break;
		default:
			break;
		}

		return FALSE;
	}

	INT_PTR CALLBACK SettingsDialog::ProcessCommandMessage( WPARAM wParam, HWND hwndDlg )
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
			return true;
		case IDCANCEL:
			EndDialog(hwndDlg, WM_CLOSE);
			return true;
			break;
		default:
			return true;
			break;
		}
	}

}
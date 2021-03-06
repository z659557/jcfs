// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"


	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif

#include <msapi/EnumWnd.h>
using namespace msdk;

CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif


 	hTrayWnd = msapi::CEnumWnd().Enum(_T("Shell_TrayWnd"));
 	hReBarWnd  = msapi::CEnumWnd(hTrayWnd).Enum(_T("ReBarWindow32"));
// 	hMSTaskSwWClassWnd = msapi::CEnumWnd(hReBarWnd).Enum(_T("MSTaskSwWClass"));


	hMSTaskSwWClassWnd = FindWindowEx(hReBarWnd, NULL, NULL, _T("jc_desk_band"));
	SetParent(this->m_hWnd, hMSTaskSwWClassWnd);

	



	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	return 0;
}


VOID CMainDlg::OnSize(UINT type, CSize size)
{
	SetMsgHandled(FALSE);
	//return;
	//获取原始的大小

	CRect ReBarRect;
	CRect ToolBarRect;

	//::GetWindowRect(hReBarWnd, &ReBarRect);


	//::GetWindowRect(hMSTaskSwWClassWnd, &ToolBarRect);
	//CSimpleWnd ReBarWnd = hReBarWnd;
	CSimpleWnd ToolBarWnd = hMSTaskSwWClassWnd;


	//ReBarWnd.ScreenToClient(ToolBarRect);
	//CRect rcNewToolbar(ToolBarRect.left, ToolBarRect.top, ReBarRect.right, ReBarRect.bottom);

	//移动任务栏
	//::MoveWindow(hMSTaskSwWClassWnd, rcNewToolbar.left, rcNewToolbar.top, rcNewToolbar.Width(), rcNewToolbar.Height(), TRUE);

	//移动自己
	::GetWindowRect(hMSTaskSwWClassWnd, &ToolBarRect);
	//ReBarWnd.ScreenToClient(ToolBarRect);

	//CRect rcNewSelf(ToolBarRect.Width(), ToolBarRect.top, ToolBarRect.Width() + 100, ReBarRect.bottom);
	::MoveWindow(m_hWnd,0, 0, ToolBarRect.Width(), ToolBarRect.Height(),0
);
	
	
	//CSize SelfRect = size;


	//::MoveWindow(hMSTaskSwWClassWnd,ReBarRect.top, ReBarRect.left , ReBarRect.bottom- 100 , ReBarRect.right ,TRUE);

	//设置新的大小
}

//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}


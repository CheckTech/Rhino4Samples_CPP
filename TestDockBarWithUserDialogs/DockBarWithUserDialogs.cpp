// DockBarWithUserDialogs.cpp : implementation file
//

#include "stdafx.h"
#include "DockBarWithUserDialogs.h"
#include "DialogA.h"
#include "DialogB.h"
#include "DialogC.h"
#include "DockBarWithUserDialogsPlugIn.h"

// CDockBarWithUserDialogs

IMPLEMENT_SERIAL(CDockBarWithUserDialogs, CRhinoUiDockBar, 1)

CDockBarWithUserDialogs::CDockBarWithUserDialogs()
: m_CurrentDialog(NULL)
, m_iCurrentDialog(-1)
{

}

CDockBarWithUserDialogs::~CDockBarWithUserDialogs()
{
}


BEGIN_MESSAGE_MAP(CDockBarWithUserDialogs, CRhinoUiDockBar)
END_MESSAGE_MAP()



// CDockBarWithUserDialogs message handlers

void CDockBarWithUserDialogs::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{
}

UUID CDockBarWithUserDialogs::DockBarID() const
{
  // {8FC1D9F5-4EA8-4c10-AA76-072E3E68BEA3}
  UUID uuid =  { 0x8fc1d9f5, 0x4ea8, 0x4c10, { 0xaa, 0x76, 0x7, 0x2e, 0x3e, 0x68, 0xbe, 0xa3 } };
  return uuid;
}

const wchar_t* CDockBarWithUserDialogs::DockBarName( int language_id) const
{
  return L"CDockBarWithUserDialogs";
}

bool CDockBarWithUserDialogs::CreateDockBarControls()
{
  return true;
}

void CDockBarWithUserDialogs::ShowDialog(int iDialog)
{
  AFX_MANAGE_STATE(DockBarWithUserDialogsPlugIn().PlugInModuleState());
  if (iDialog >= 0 && iDialog < 3 && iDialog != m_iCurrentDialog)
  {
    CDialog* pDlg = NULL;
    // Calling CreateDockBarClientDialog will destroy dialog created with previous call and delete the pointer
    switch (iDialog)
    {
      case 0:
        if (CreateDockBarClientDialog(CDialogA::IDD, 0, RUNTIME_CLASS(CDialogA), DockBarWithUserDialogsPlugIn().PlugInModuleState()))
          pDlg = ComputeClientDialog();
        break;
      case 1:
        if (CreateDockBarClientDialog(CDialogB::IDD, 0, RUNTIME_CLASS(CDialogB), DockBarWithUserDialogsPlugIn().PlugInModuleState()))
          pDlg = ComputeClientDialog();
        break;
      case 2:
        if (CreateDockBarClientDialog(CDialogC::IDD, 0, RUNTIME_CLASS(CDialogC), DockBarWithUserDialogsPlugIn().PlugInModuleState()))
          pDlg = ComputeClientDialog();
        break;
    }
    if (pDlg)
    {
      SetDockBarClientWnd(pDlg);
      m_CurrentDialog = pDlg;
      m_iCurrentDialog = iDialog;
      CRect r;
      GetClientRect(r);
      pDlg->MoveWindow(r);
      pDlg->ShowWindow(SW_SHOW);
      pDlg->UpdateWindow();
    }
    else
      m_CurrentDialog = ComputeClientDialog(); // See if there is a child dialog
  }
}

CDialog* CDockBarWithUserDialogs::ComputeClientDialog()
{
  // Need to do this because the pointer saved by CRhinoUiDockBar::CreateDockBarClientDialog is private
  CDialog* pDlg = NULL;
  CWnd* pWndChild=GetWindow(GW_CHILD);
  while (NULL == pDlg && NULL != pWndChild)
  {
    pDlg = dynamic_cast<CDialog*>(pWndChild);
    pWndChild = pWndChild->GetWindow(GW_HWNDNEXT);
  }
  return pDlg;
}

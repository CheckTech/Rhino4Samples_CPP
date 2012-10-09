/////////////////////////////////////////////////////////////////////////////
// DialogB.cpp

#include "stdafx.h"
#include "DockBarWithUserDialogs.h"
#include "DialogB.h"

// CDialogB dialog

IMPLEMENT_DYNCREATE(CDialogB, CDialog)

CDialogB::CDialogB(CWnd* pParent /*=NULL*/)
: CDialog(CDialogB::IDD, pParent)
{
}

CDialogB::~CDialogB()
{
}

void CDialogB::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATIC_B, m_Static);
}

BEGIN_MESSAGE_MAP(CDialogB, CDialog)
  ON_WM_SIZE()
END_MESSAGE_MAP()

// CDialogB message handlers

void CDialogB::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);

  if (IsWindow(m_Static))
  {
    CRect r;
    GetClientRect(r);
    m_Static.MoveWindow(r);
  }
}

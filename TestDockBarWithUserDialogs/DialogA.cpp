/////////////////////////////////////////////////////////////////////////////
// DialogA.cpp

#include "stdafx.h"
#include "DockBarWithUserDialogs.h"
#include "DialogA.h"

// CDialogA dialog

IMPLEMENT_DYNCREATE(CDialogA, CDialog)

CDialogA::CDialogA(CWnd* pParent /*=NULL*/)
: CDialog(CDialogA::IDD, pParent)
{
}

CDialogA::~CDialogA()
{
}

void CDialogA::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATIC_A, m_Static);
}

BEGIN_MESSAGE_MAP(CDialogA, CDialog)
  ON_WM_SIZE()
END_MESSAGE_MAP()

// CDialogA message handlers

void CDialogA::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);

  if (IsWindow(m_Static))
  {
    CRect r;
    GetClientRect(r);
    m_Static.MoveWindow(r);
  }
}

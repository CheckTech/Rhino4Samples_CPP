/////////////////////////////////////////////////////////////////////////////
// DialogC.cpp 

#include "stdafx.h"
#include "DockBarWithUserDialogs.h"
#include "DialogC.h"

// CDialogC dialog

IMPLEMENT_DYNCREATE(CDialogC, CDialog)

CDialogC::CDialogC(CWnd* pParent /*=NULL*/)
: CDialog(CDialogC::IDD, pParent)
{
}

CDialogC::~CDialogC()
{
}

void CDialogC::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_STATIC_C, m_Static);
}

BEGIN_MESSAGE_MAP(CDialogC, CDialog)
  ON_WM_SIZE()
END_MESSAGE_MAP()

// CDialogC message handlers

void CDialogC::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);

  if (IsWindow(m_Static))
  {
    CRect r;
    GetClientRect(r);
    m_Static.MoveWindow(r);
  }
}

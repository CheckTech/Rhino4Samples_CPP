/////////////////////////////////////////////////////////////////////////////
// TestAboutDialog.cpp
//

#include "stdafx.h"
#include "TestAboutDialog.h"

IMPLEMENT_DYNAMIC(CTestAboutDialog, CRhinoDialog)

CTestAboutDialog::CTestAboutDialog(CWnd* pParent /*=NULL*/)
: CRhinoDialog(CTestAboutDialog::IDD, pParent)
{
}

CTestAboutDialog::~CTestAboutDialog()
{
}

void CTestAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestAboutDialog, CRhinoDialog)
END_MESSAGE_MAP()

BOOL CTestAboutDialog::OnInitDialog()
{
  CRhinoDialog::OnInitDialog();

  return TRUE;
}

#include "stdafx.h"
#include "TestRhinoOptionsPage.h"

IMPLEMENT_DYNAMIC(CTestRhinoOptionsPage, CRhinoOptionsDialogPage)

CTestRhinoOptionsPage::CTestRhinoOptionsPage(CWnd* pParent /*=NULL*/)
: CRhinoOptionsDialogPage(CTestRhinoOptionsPage::IDD, pParent)
{
}

CTestRhinoOptionsPage::~CTestRhinoOptionsPage()
{
}

void CTestRhinoOptionsPage::DoDataExchange(CDataExchange* pDX)
{
  CRhinoOptionsDialogPage::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_BUTTON1, m_button);
  DDX_Control(pDX, IDC_SEP1, m_sep1);
}

BEGIN_MESSAGE_MAP(CTestRhinoOptionsPage, CRhinoOptionsDialogPage)
  ON_BN_CLICKED(IDC_BUTTON1, &CTestRhinoOptionsPage::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CTestRhinoOptionsPage::OnInitDialog()
{
  CRhinoOptionsDialogPage::OnInitDialog();

  return TRUE;
}

const wchar_t* CTestRhinoOptionsPage::EnglishPageTitle()
{
  return L"Test Options";
}

const wchar_t* CTestRhinoOptionsPage::LocalPageTitle()
{
  return L"Test Options";
}

void CTestRhinoOptionsPage::RhinoDeleteThisPage()
{
  /*
  DO NOT DELETE THIS PAGE IN PostNcDestroy()!
  When V4 first shipped, where was a lot of confusion when and where to
  delete stacked dialog pages that were created in plug-ins. The reason
  being that if the page had never been created (you never clicked on it),
  then its PostNcDestroy() member was never called. This confusion led to
  may reported crashes. Thus in later releases, Rhino always calls the
  RhinoDeleteThisPage() member. Thus the only place you need to delete
  the page is here.
  */
  delete this;
}

int CTestRhinoOptionsPage::OnApply()
{
  return TRUE;
}

CRhinoCommand::result CTestRhinoOptionsPage::RunScript( CRhinoDoc& doc )
{
  return CRhinoCommand::success;
}

void CTestRhinoOptionsPage::OnBnClickedButton1()
{
  RhinoMessageBox( GetSafeHwnd(), L"Pick me button pressed", LocalPageTitle(), MB_OK );
}

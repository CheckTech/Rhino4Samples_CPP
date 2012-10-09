#include "stdafx.h"
#include "TestRhinoDocPropsPage.h"

IMPLEMENT_DYNAMIC(CTestRhinoDocPropsPage, CRhinoOptionsDialogPage)

CTestRhinoDocPropsPage::CTestRhinoDocPropsPage(CWnd* pParent /*=NULL*/)
: CRhinoOptionsDialogPage(CTestRhinoDocPropsPage::IDD, pParent)
{
}

CTestRhinoDocPropsPage::~CTestRhinoDocPropsPage()
{
}

void CTestRhinoDocPropsPage::DoDataExchange(CDataExchange* pDX)
{
  CRhinoOptionsDialogPage::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_BUTTON1, m_button);
  DDX_Control(pDX, IDC_SEP1, m_sep1);
}

BEGIN_MESSAGE_MAP(CTestRhinoDocPropsPage, CRhinoOptionsDialogPage)
  ON_BN_CLICKED(IDC_BUTTON1, &CTestRhinoDocPropsPage::OnBnClickedButton1)
END_MESSAGE_MAP()

BOOL CTestRhinoDocPropsPage::OnInitDialog()
{
  CRhinoOptionsDialogPage::OnInitDialog();

  return TRUE;
}

const wchar_t* CTestRhinoDocPropsPage::EnglishPageTitle()
{
  return L"Test Properties";
}

const wchar_t* CTestRhinoDocPropsPage::LocalPageTitle()
{
  return L"Test Properties";
}

void CTestRhinoDocPropsPage::RhinoDeleteThisPage()
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

int CTestRhinoDocPropsPage::OnApply()
{
  return TRUE;
}

CRhinoCommand::result CTestRhinoDocPropsPage::RunScript( CRhinoDoc& doc )
{
  return CRhinoCommand::success;
}

void CTestRhinoDocPropsPage::OnBnClickedButton1()
{
  RhinoMessageBox( GetSafeHwnd(), L"Pick me button pressed", LocalPageTitle(), MB_OK );
}


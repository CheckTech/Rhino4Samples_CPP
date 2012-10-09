/////////////////////////////////////////////////////////////////////////////
// MyRhinoDockBarDialog.cpp : MyRhinoDockBarDialog.h implementation file
//


#include "StdAfx.h"
#include "MyRhinoDockBarDialog.h"


IMPLEMENT_SERIAL(CMyRhinoDockBarDialog,CRhinoUiDockBarDialog,1)



////////////////////////////////////////////////////////////////////////////////////
// constructor/destructor
//
CMyRhinoDockBarDialog::CMyRhinoDockBarDialog(CWnd* pParent /*=NULL*/)
	: CRhinoUiDockBarDialog(CMyRhinoDockBarDialog::IDD, pParent)
{
}

CMyRhinoDockBarDialog::~CMyRhinoDockBarDialog()
{
}
//
// end constructor/destructor
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
// required overrides
//
BOOL CMyRhinoDockBarDialog::OnInitDialog() 
{
	CRhinoUiDockBarDialog::OnInitDialog();
	
	//use the CRhinoUiDialogItemResizer inherited from 
	//CRhinoUiDockBarDialog to size our constituent controls
	this->m_Resize.Add(IDC_GROUPBOX, CRhinoUiDialogItemResizer::resize_lockall);
	this->m_Resize.Add(IDC_LISTVIEW, CRhinoUiDialogItemResizer::resize_lockall);
	this->m_Resize.Add(IDC_EDITBOX, CRhinoUiDialogItemResizer::resize_lockbottom | CRhinoUiDialogItemResizer::resize_lockleft | CRhinoUiDialogItemResizer::resize_lockright);
	this->m_Resize.Add(IDC_BTNOK, CRhinoUiDialogItemResizer::resize_lockbottomright);

	return TRUE;
}
//
// end required overrides
////////////////////////////////////////////////////////////////////////////////////
 

////////////////////////////////////////////////////////////////////////////////////
// event handling
//
void CMyRhinoDockBarDialog::DoDataExchange(CDataExchange* pDX)
{
	CRhinoUiDockBarDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyRhinoDockBarDialog,CRhinoUiDockBarDialog)
	ON_BN_CLICKED(IDC_BTNOK, &CMyRhinoDockBarDialog::OnBnClickedBtnok)
END_MESSAGE_MAP()

void CMyRhinoDockBarDialog::OnBnClickedBtnok()
{
	RhinoMessageBox(L"CMyRhinoDockBarDialog::OnBnClickedBtnok()", L"Hello!" ,MB_OK);
}
//
//end event handling
////////////////////////////////////////////////////////////////////////////////////



//
// end MyRhinoDockBarDialog.cpp
////////////////////////////////////////////////////////////////////////////////////


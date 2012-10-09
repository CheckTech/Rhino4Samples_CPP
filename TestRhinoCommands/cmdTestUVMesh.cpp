#include "StdAfx.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN TestUVMesh command
//

class CCommandTestUVMesh : public CRhinoCommand
{
public:
	CCommandTestUVMesh() {m_U=10; m_V=10;}
	~CCommandTestUVMesh() {}
  
	UUID CommandUUID()
	{
    // {E43D0CA2-1568-4fe6-9180-B5119399EA30}
    static const GUID TestUVMeshCommand_UUID = 
    { 0xe43d0ca2, 0x1568, 0x4fe6, { 0x91, 0x80, 0xb5, 0x11, 0x93, 0x99, 0xea, 0x30 } };
		return TestUVMeshCommand_UUID;
	}

  int m_U;
  int m_V;

  const wchar_t* EnglishCommandName() { return L"TestUVMesh"; }

  void LoadProfile(LPCTSTR lpszSection, CRhinoProfileContext& pc);
  void SaveProfile(LPCTSTR lpszSection, CRhinoProfileContext& pc);

	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

static class CCommandTestUVMesh theTestUVMeshCommand;

void CCommandTestUVMesh::LoadProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc )
{
  int i = m_U;
  if ( pc.LoadProfileInt( lpszSection, _T("U"), &i ))
    m_U = i;
  if ( pc.LoadProfileInt( lpszSection, _T("V"), &i ))
    m_V = i;
}

void CCommandTestUVMesh::SaveProfile( LPCTSTR lpszSection, CRhinoProfileContext& pc )
{
  pc.SaveProfileInt( lpszSection, _T("U"), m_U );
  pc.SaveProfileInt( lpszSection, _T("V"), m_V );
}


CRhinoCommand::result CCommandTestUVMesh::RunCommand( const CRhinoCommandContext& context )
{
  bool bDeleteInput = false;
  CRhinoGetObject go;
  go.SetCommandPrompt(L"Select untrimmed surface");
  go.AddCommandOptionInteger(RHCMDOPTNAME(L"U"), &m_U, 0, 2);
  go.AddCommandOptionInteger(RHCMDOPTNAME(L"V"), &m_V, 0, 2);
  go.AddCommandOptionToggle(RHCMDOPTNAME(L"DeleteInput"), RHCMDOPTVALUE(L"No"), RHCMDOPTVALUE(L"Yes"), bDeleteInput, &bDeleteInput);
  go.SetGeometryFilter(CRhinoGetObject::surface_object);
  go.SetGeometryAttributeFilter(CRhinoGetObject::untrimmed_surface);

  CRhinoGet::result rs = CRhinoGet::no_result;
  while (CRhinoGet::cancel != rs && CRhinoGet::nothing != rs && CRhinoGet::object != rs)
    rs = go.GetObjects(1,1);

  if (CRhinoGet::cancel == rs)
    return CRhinoCommand::cancel;
  if (0 == go.ObjectCount())
    return CRhinoCommand::failure;

  const CRhinoObject* pObj = go .Object(0).Object();
  if (0 == pObj)
    return CRhinoCommand::failure;

  const ON_BrepFace* pBrepFace = go.Object(0).Face();
  if (0 == pBrepFace)
    return CRhinoCommand::failure;

  const ON_Surface* pSurf = pBrepFace->SurfaceOf();
  if (0 == pSurf)
    return CRhinoCommand::failure;

  ON_SimpleArray<double>UArray(m_U+1);
  ON_SimpleArray<double>VArray(m_V+1);
  double UDist, VDist;
  UDist = (pSurf->Domain(0).m_t[1]-pSurf->Domain(0).m_t[0])/m_U;
  VDist = (pSurf->Domain(1).m_t[1]-pSurf->Domain(1).m_t[0])/m_V;
  int i;
  for (i=0; i <= m_U; i++)
    UArray.Append(pSurf->Domain(0).m_t[0] + i*UDist);
  for (i=0; i <= m_V; i++)
    VArray.Append(pSurf->Domain(1).m_t[0] + i*VDist);

  //If m_U or m_V are large then there can be a slight difference between
  //pSurf->Domain(0).m_t[0] + (m_U-1)*UDist and pSurf->Domain(0).m_t[1]
  //ON_MeshSurface requires it to be less than or equal to pSurf->Domain(0).m_t[1]
  //05/24/06 TimH Fix for RR21194
  double* d = UArray.Last();
  if (pSurf->Domain(0).m_t[1] < *d)
    *d = pSurf->Domain(0).m_t[1];
  d = VArray.Last();
  if (pSurf->Domain(1).m_t[1] < *d)
    *d = pSurf->Domain(1).m_t[1];

  ON_Mesh* pMeshOut = ON_MeshSurface(*pSurf, m_U+1, UArray.Array(), m_V+1, VArray.Array());

  if (0 == pMeshOut)
    return CRhinoCommand::failure;

  CRhinoMeshObject* pMeshObj = new CRhinoMeshObject(pObj->Attributes());
  if (0 == pMeshObj)
  {
    delete pMeshOut;
    return CRhinoCommand::failure;
  }
  pMeshObj->SetMesh(pMeshOut);

  if (true == bDeleteInput)
    context.m_doc.ReplaceObject(pObj, pMeshObj);
  else
    context.m_doc.AddObject(pMeshObj);

  context.m_doc.Redraw();
  return CRhinoCommand::success;
}

//
// END TestUVMesh command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// cmdTestArchive.cpp : command file
//

#include "StdAfx.h"
#include "TestArchivePlugIn.h"

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN PrintTestArchive command
//

#pragma region PrintTestArchive command

class CCommandPrintTestArchive : public CRhinoCommand
{
public:
	CCommandPrintTestArchive() {}
	~CCommandPrintTestArchive() {}
	UUID CommandUUID()
	{
		// {3EC9B0B2-DA4-46E4-A496-F704F422BAE0}
		static const GUID PrintTestArchiveCommand_UUID =
		{ 0x3EC9B0B2, 0xDA4, 0x46E4, { 0xA4, 0x96, 0xF7, 0x04, 0xF4, 0x22, 0xBA, 0xE0 } };
		return PrintTestArchiveCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"PrintTestArchive"; }
	const wchar_t* LocalCommandName() { return L"PrintTestArchive"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandPrintTestArchive object
static class CCommandPrintTestArchive thePrintTestArchiveCommand;

CRhinoCommand::result CCommandPrintTestArchive::RunCommand( const CRhinoCommandContext& context )
{
  // Print test data
	TestArchivePlugIn().PrintTestData();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END PrintTestArchive command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN GenerateTestData command
//

#pragma region GenerateTestData command

class CCommandGenerateTestData : public CRhinoCommand
{
public:
	CCommandGenerateTestData() {}
	~CCommandGenerateTestData() {}
	UUID CommandUUID()
	{
		// {CDA91D1-1D43-4A54-920F-2A6470D132E0}
		static const GUID GenerateTestDataCommand_UUID =
		{ 0xCDA91D1, 0x1D43, 0x4A54, { 0x92, 0x0F, 0x2A, 0x64, 0x70, 0xD1, 0x32, 0xE0 } };
		return GenerateTestDataCommand_UUID;
	}
	const wchar_t* EnglishCommandName() { return L"GenerateTestData"; }
	const wchar_t* LocalCommandName() { return L"GenerateTestData"; }
	CRhinoCommand::result RunCommand( const CRhinoCommandContext& );
};

// The one and only CCommandGenerateTestData object
static class CCommandGenerateTestData theGenerateTestDataCommand;

CRhinoCommand::result CCommandGenerateTestData::RunCommand( const CRhinoCommandContext& context )
{
  // Create test data
  TestArchivePlugIn().InitTestData();
  // Print test data
  TestArchivePlugIn().PrintTestData();

	return CRhinoCommand::success;
}

#pragma endregion

//
// END GenerateTestData command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

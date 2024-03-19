#include "pch.h"
#include "CPathMgr.h"

#include "CEngine.h"

CPathMgr::CPathMgr()
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	// 실행 경로를 얻어낸다.
	wchar_t szBuffer[256]{};
	GetCurrentDirectory(256, szBuffer);

	wstring strCurrentPath{ szBuffer };
	wstring strBuildPath = GetParentPath(strCurrentPath);

	m_strContentsPath = strBuildPath + L"\\contents";
	m_strSolutionPath = GetParentPath(strBuildPath);
	
	// String Table에서 프로젝트 이름을 얻어온다.
	wchar_t szProjectName[50]{};
	LoadString(CEngine::GetInstance().GetProcessInstance(), IDS_APP_TITLE, szProjectName, 50);

	m_strProjectPath = m_strSolutionPath + L"\\" + szProjectName;
}

void CPathMgr::render()
{
	TextOut(SUBDC, 10, 10, m_strSolutionPath.c_str(), (int)m_strSolutionPath.length());
	TextOut(SUBDC, 10, 30, m_strProjectPath.c_str(), (int)m_strProjectPath.length());
	TextOut(SUBDC, 10, 50, m_strContentsPath.c_str(), (int)m_strContentsPath.length());
}

wstring CPathMgr::GetParentPath(const wstring& _strPath)
{
	std::filesystem::path fsPath{ _strPath };
	return fsPath.parent_path().wstring();
}



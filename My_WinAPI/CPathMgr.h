#pragma once
#include "Singleton.h"
class CPathMgr :
	public Singleton<CPathMgr>
{
	friend Singleton<CPathMgr>;

private:
	wstring	m_strContentsPath;
	wstring m_strSolutionPath;
	wstring m_strProjectPath;

public:
	void init();
	void render();

	const wstring& GetContentsPath() { return m_strContentsPath; }
	const wstring& GetSolutionPath() { return m_strSolutionPath; }
	const wstring& GetProjectPath() { return m_strProjectPath; }

private:
	wstring	GetParentPath(const wstring& _strPath);

private:
	CPathMgr();
	~CPathMgr();
};


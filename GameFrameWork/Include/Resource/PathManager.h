#pragma once
#include "../stdafx.h"
class PathManager
{
public:
	bool Init();
	bool AddPath(const string& KeyName, const wstring& PathName, const string& BaseKeyName = ROOT_PATH);
	const TCHAR* FindPath(const string& KeyName);
	const char* FindPathMultiByte(const string& KeyName);
private:
	unordered_map<string, MyString> PathMap;
	char m_MultiBytePath[MAX_PATH] = {};

public:
	CLASS_IN_SINGLE(PathManager)
};


#include "PathManager.h"

INIT_STATIC_VAR(PathManager)

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

bool PathManager::Init()
{
	TCHAR strPath[MAX_PATH];
	//실행파일 있는곳의 경로를 뽑아낸다.
	GetModuleFileName(NULL, strPath, MAX_PATH);

	//뒤에서부터 돌아서 //이 있으면 그이후 0으로 초기화
	for (int i = lstrlen(strPath); i >= 0; i--)
	{
		if (strPath[i] == '\\' || strPath[i] == '//')
		{
			memset(strPath + (i + 1), 0, sizeof(TCHAR) * (MAX_PATH - (i + 1)));
			break;
		}
	}

	PathMap.insert(make_pair(ROOT_PATH, strPath));

	AddPath(TEXTURE_PATH, TEXT("Textures\\"));
	AddPath(DATA_PATH, TEXT("Data\\"));
	AddPath(SOUND_PATH, TEXT("Sound\\"));

	return true;
}

bool PathManager::AddPath(const string & KeyName, const wstring & PathName, const string & BaseKeyName)
{
	if (FindPath(KeyName) != NULL)
		return false;

	const TCHAR * pPath = FindPath(BaseKeyName);
	MyString FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += PathName;

	PathMap.insert(make_pair(KeyName,FullPath));
	return true;
}

const TCHAR * PathManager::FindPath(const string & KeyName)
{
	unordered_map<string, MyString>::iterator FindIter = PathMap.find(KeyName);

	if (FindIter == PathMap.end())
		return NULL;

	return FindIter->second.c_str();
}

const char * PathManager::FindPathMultiByte(const string & KeyName)
{
	const TCHAR* mPath = FindPath(KeyName);

	if (mPath == NULL)
		return NULL;

	memset(m_MultiBytePath, 0, sizeof(char) * MAX_PATH);

	// 유니코드 문자열을 멀티바이트로 변환한다.
#ifdef UNICODE
	WideCharToMultiByte(CP_ACP, 0, mPath, -1, m_MultiBytePath, lstrlen(mPath) * 2,0, 0);
#else
	memcpy(m_strPath, pPath, sizeof(TCHAR) * lstrlen(pPath));
#endif	// UNICODE

	return m_MultiBytePath;
}

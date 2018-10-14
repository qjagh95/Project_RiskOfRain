#include "Texture.h"
#include "../Core.h"
#include "PathManager.h"

Texture::Texture() :m_memDC(NULL), m_hBitmap(NULL), m_hOldBitmap(NULL)
{
}

Texture::~Texture()
{
	//지우기 전에 DC에 기존에 장착되어 있던 비트맵을 다시 지정해준다
	SelectObject(m_memDC, m_hOldBitmap);

	//비트맵 도구를 지운다
	DeleteObject(m_hBitmap);

	//메모리 도구를 지운다
	DeleteDC(m_memDC);
}

bool Texture::LoadTexture(const string & KeyName, const TCHAR * FileName, const string & BaseKey)
{
	//인자로 들어온 파일경로들을 조합하여 최종 경로를 받아온다
	const TCHAR* pPath = PathManager::Get()->FindPath(BaseKey);
	wstring FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += FileName;

	m_Key = KeyName;
	m_PathKey = BaseKey;
	
	lstrcpy(m_FileName, FileName);
	lstrcpy(m_FullPath, FullPath.c_str());

	//메모리 dc를 생성한다
	m_memDC = CreateCompatibleDC(Core::Get()->GetHDC());

	//비트맵변수에 이미지정보를 저장한다
	m_hBitmap = (HBITMAP)LoadImage(Core::Get()->GetHinstance(), FullPath.c_str(), IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);

	//읽어온 이미지를 DC에 저장한다
	//기존 DC에 저장되있던 이미지는 별도로 지정을 해줘야한다
	m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);

	//이미지 정보를 얻어온다
	GetObject(m_hBitmap, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

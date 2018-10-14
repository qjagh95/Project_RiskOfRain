#pragma once
#include "../RefCount.h"
class Texture : public RefCount
{
public:
	friend class ResourceManager;

	bool LoadTexture(const string& KeyName, const TCHAR* FileName, const string& BaseKey = TEXTURE_PATH);
	UINT GetWidth() const { return (UINT)m_BitmapInfo.bmWidth; }
	UINT GetHeight() const { return (UINT)m_BitmapInfo.bmHeight; }
	HDC GetMemDC() const { return m_memDC; }
	
	const TCHAR* GetFullPath() const { return m_FullPath; }
	string GetKey() const { return m_Key; }

	const TCHAR* GetFileName() const { return m_FileName; }
	string GetPathKey() const { return m_PathKey; }

private:
	HDC m_memDC;		 ///HBITMAP������ DC�� ����
	HBITMAP m_hBitmap;    ///��Ʈ�� �׸��⵵���̴�. ���Ϸκ��� �ȼ��� �о�ͼ� �����Ѵ�
	HBITMAP m_hOldBitmap; ///���� �������ִ� ������ �����Ѵ�.
	BITMAP m_BitmapInfo;
	string m_Key;
	string m_PathKey;
	TCHAR m_FullPath[MAX_PATH];
	TCHAR m_FileName[MAX_PATH];

private:
	Texture();
	~Texture();
};


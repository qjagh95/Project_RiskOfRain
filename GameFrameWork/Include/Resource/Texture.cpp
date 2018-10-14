#include "Texture.h"
#include "../Core.h"
#include "PathManager.h"

Texture::Texture() :m_memDC(NULL), m_hBitmap(NULL), m_hOldBitmap(NULL)
{
}

Texture::~Texture()
{
	//����� ���� DC�� ������ �����Ǿ� �ִ� ��Ʈ���� �ٽ� �������ش�
	SelectObject(m_memDC, m_hOldBitmap);

	//��Ʈ�� ������ �����
	DeleteObject(m_hBitmap);

	//�޸� ������ �����
	DeleteDC(m_memDC);
}

bool Texture::LoadTexture(const string & KeyName, const TCHAR * FileName, const string & BaseKey)
{
	//���ڷ� ���� ���ϰ�ε��� �����Ͽ� ���� ��θ� �޾ƿ´�
	const TCHAR* pPath = PathManager::Get()->FindPath(BaseKey);
	wstring FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += FileName;

	m_Key = KeyName;
	m_PathKey = BaseKey;
	
	lstrcpy(m_FileName, FileName);
	lstrcpy(m_FullPath, FullPath.c_str());

	//�޸� dc�� �����Ѵ�
	m_memDC = CreateCompatibleDC(Core::Get()->GetHDC());

	//��Ʈ�ʺ����� �̹��������� �����Ѵ�
	m_hBitmap = (HBITMAP)LoadImage(Core::Get()->GetHinstance(), FullPath.c_str(), IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);

	//�о�� �̹����� DC�� �����Ѵ�
	//���� DC�� ������ִ� �̹����� ������ ������ ������Ѵ�
	m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);

	//�̹��� ������ ���´�
	GetObject(m_hBitmap, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

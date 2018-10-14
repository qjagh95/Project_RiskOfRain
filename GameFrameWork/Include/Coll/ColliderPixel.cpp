#include "ColliderPixel.h"
#include "../Object/Object.h"
#include "ColliderCircle.h"
#include "ColliderPoint.h"
#include "ColliderRect.h"
#include "../Resource/PathManager.h"

ColliderPixel::ColliderPixel()
{
	SetTag("Pixel");
	m_CollType = CT_PIXEL;
}

ColliderPixel::ColliderPixel(const ColliderPixel & Value)
	:Collider(Value)
{
	m_VirtualInfo = Value.m_VirtualInfo;

	m_VirtualInfo.cPixel = new char[m_VirtualInfo.PixelCount * m_VirtualInfo.PixelSize];
	memcpy(m_VirtualInfo.cPixel, Value.m_VirtualInfo.cPixel, Value.m_VirtualInfo.PixelSize);
}

ColliderPixel::~ColliderPixel()
{
	SAFE_DELETE_ARRAY(m_VirtualInfo.cPixel);
}

bool ColliderPixel::Init()
{
	return true;
}

int ColliderPixel::Update(float DeltaTime)
{
	m_WorldInfo = m_VirtualInfo;

	m_WorldInfo.WorldPos.x = m_Object->GetPos().x - (m_Pivot.x * m_VirtualInfo.Width);
	m_WorldInfo.WorldPos.y = m_Object->GetPos().x - (m_Pivot.y * m_VirtualInfo.Height);

	return 0;
}

bool ColliderPixel::Collsion(Collider * Dest)
{
	switch (Dest->GetCollType())
	{
		case CT_RECT:
			return CollsionRectToPixel(((ColliderRect*)Dest)->GetWorldRect(), m_WorldInfo);
	}

	return false;
}

void ColliderPixel::Render(HDC hDC, float DeltaTime)
{
}

ColliderPixel * ColliderPixel::Clone() const
{
	return new ColliderPixel(*this);
}

void ColliderPixel::Save(FILE * pFile)
{
	Collider::Save(pFile);

	fwrite(&m_VirtualInfo.PixelSize, sizeof(unsigned int), 1, pFile);
	fwrite(&m_VirtualInfo.PixelCount, sizeof(unsigned int), 1, pFile);
	fwrite(&m_VirtualInfo.Width, sizeof(unsigned int), 1, pFile);
	fwrite(&m_VirtualInfo.Height, sizeof(unsigned int), 1, pFile);
	fwrite(&m_VirtualInfo.WorldPos, sizeof(Vector2), 1, pFile);
	fwrite(&m_VirtualInfo.CollsionColor, sizeof(Pixel32), 1, pFile);

	//�ȼ�����������, �ȼ������ŭ, �ȼ�ī��� (3����Ʈ..)
	fwrite(m_VirtualInfo.cPixel, m_VirtualInfo.PixelSize, m_VirtualInfo.PixelCount, pFile);
}

void ColliderPixel::Load(FILE * pFile)
{
	Collider::Load(pFile);

	fread(&m_VirtualInfo.PixelSize, sizeof(unsigned int), 1, pFile);
	fread(&m_VirtualInfo.PixelCount, sizeof(unsigned int), 1, pFile);
	fread(&m_VirtualInfo.Width, sizeof(unsigned int), 1, pFile);
	fread(&m_VirtualInfo.Height, sizeof(unsigned int), 1, pFile);
	fread(&m_VirtualInfo.WorldPos, sizeof(Vector2), 1, pFile);
	fread(&m_VirtualInfo.CollsionColor, sizeof(Pixel32), 1, pFile);

	m_VirtualInfo.cPixel = new char[m_VirtualInfo.PixelSize * m_VirtualInfo.PixelCount];
	//�ȼ�����������, �ȼ������ŭ, �ȼ�ī��� (3����Ʈ..)
	fread(m_VirtualInfo.cPixel, m_VirtualInfo.PixelSize, m_VirtualInfo.PixelCount, pFile);
}

void ColliderPixel::SetPixelCollsionInfo(const char * FileName, const string & PathKey)
{
	FILE* pFile = NULL;

	//��ü��θ� ������ش�
	const char* pPath = PathManager::Get()->FindPathMultiByte(PathKey);
	string FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += FileName;

	fopen_s(&pFile, FullPath.c_str(), "rb");

	if (pFile == NULL)
		return;

	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER ih;

	fread(&bh, sizeof(bh), 1, pFile);
	fread(&ih, sizeof(ih), 1, pFile);

	int Byte = 1;

	switch (ih.biBitCount)
	{
		case 8:
			Byte = 1;
			break;
		case 24:
			Byte = 3;
			break;
		case 32:
			Byte = 4;
			break;
	}

	void* pPixel = new char[Byte * ih.biWidth * ih.biHeight];

	fread(pPixel, Byte, ih.biWidth * ih.biHeight, pFile);

	m_VirtualInfo.cPixel = pPixel;
	m_VirtualInfo.PixelCount = ih.biWidth * ih.biHeight;
	m_VirtualInfo.PixelSize = Byte;
	m_VirtualInfo.Width = ih.biWidth;
	m_VirtualInfo.Height = ih.biHeight;

	//BMP������ Ư���� �ȼ������� �����Ǿ� ������ִ�. �׷��⶧���� �ٽ� ���������ش�
	void* TempPixel = new char[Byte * ih.biWidth];
						//�ݱ������� �� ��������
	for (unsigned int i = 0; i < m_VirtualInfo.Height / 2; i++)
	{
		//���پ� �ѱ�� ����
		int Bottom = (m_VirtualInfo.Height - 1) - i;

		//���� ������ TempPixel�� �����Ѵ�
		memcpy(TempPixel, &((char*)pPixel)[i * m_VirtualInfo.Width * Byte], Byte * m_VirtualInfo.Width);
		//�� �������� ���������� �����Ѵ�
		memcpy(&((char*)pPixel)[i * m_VirtualInfo.Width * Byte], &((char*)pPixel)[Bottom * m_VirtualInfo.Width * Byte], Byte * m_VirtualInfo.Width);
		//TempPixel�� ����Ȱ��� �ǹؿ� �����Ѵ�
		memcpy(&((char*)pPixel)[Bottom * m_VirtualInfo.Width * Byte], TempPixel, Byte * m_VirtualInfo.Width);
	}

	fclose(pFile);
}

void ColliderPixel::SetCollsionPixel(unsigned char r, unsigned char g, unsigned char b)
{
	m_VirtualInfo.CollsionColor.r = r;
	m_VirtualInfo.CollsionColor.g = g;
	m_VirtualInfo.CollsionColor.b = b;
}

void ColliderPixel::SetCollsionPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_VirtualInfo.CollsionColor.r = r;
	m_VirtualInfo.CollsionColor.g = g;
	m_VirtualInfo.CollsionColor.b = b;
	m_VirtualInfo.CollsionColor.a = a;

}

bool ColliderPixel::CheckPixelCollsion(int x, int y)
{
	Pixel32 TempPixel;
	TempPixel.r = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize];
	TempPixel.g = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize + 1];
	TempPixel.b = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize + 2];

	return TempPixel.r == m_VirtualInfo.CollsionColor.r && TempPixel.g == m_VirtualInfo.CollsionColor.g &&TempPixel.b == m_VirtualInfo.CollsionColor.b;
}

bool ColliderPixel::CheckPixelCollsion(const Vector2 & Pos)
{
	Pixel32 TempPixel = {};
	int x = (int)Pos.x;
	int y = (int)Pos.y;

	TempPixel.r = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize];
	TempPixel.g = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize + 1];
	TempPixel.b = ((char*)m_VirtualInfo.cPixel)[(y * m_VirtualInfo.Width + x) * m_VirtualInfo.PixelSize + 2];

	return TempPixel.r == m_VirtualInfo.CollsionColor.r && TempPixel.g == m_VirtualInfo.CollsionColor.g &&TempPixel.b == m_VirtualInfo.CollsionColor.b;
}

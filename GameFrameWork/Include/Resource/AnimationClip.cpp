#include "AnimationClip.h"
#include "Texture.h"
#include "ResourceManager.h"

AnimationClip::AnimationClip()
	:m_Texture(NULL)
{
	m_FrameX = 0;
	m_FrameY = 0;
	m_FrameCountX = 0;
	m_FrameCountY = 0;
	m_FrameMaxX = 0;
	m_FrameMaxY = 0;
	m_StartX = 0;
	m_StartY = 0;
	m_FrameCount = 0;
	m_AnimationTime = 0.0f;
	m_CompleteTime = 0.0f;
	m_isColorKey = false;
	m_ColorKey = 0;
}

AnimationClip::AnimationClip(const AnimationClip& Value)
{
	*this = Value;

	if (m_Texture != NULL)
		m_Texture->AddRefCount();
}

AnimationClip::~AnimationClip()
{
	SAFE_RELEASE(m_Texture);
}

bool AnimationClip::Load(const char * FullPath)
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, FullPath, "rt");

	if (!pFile)
		return false;

	// �̸��� �о�´�.
	char strLine[256] = {};
	fgets(strLine, 256, pFile);

	m_Name = strLine;
	m_Name.pop_back();

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	//�ǵڿ��ִ� \n(�� �ѱ�� ����)�� 0���� �ٲ������.
	int	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_Type = (ANIMATION_TYPE)atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_Option = (ANIMATION_OPTION)atoi(strLine);

	// ũ�⸦ �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_FrameSize.x = (float)atof(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_FrameSize.y = (float)atof(strLine);

	// ������ ī��Ʈ�� �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_FrameCountX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	m_FrameCountY = atoi(strLine);

	m_FrameCount = m_FrameCountX * m_FrameCountY;

	// ��Ʋ���� ��ü x, y�� �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;
	m_FrameMaxX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;
	m_FrameMaxY = atoi(strLine);

	// ��Ʋ���� ���� x, y�� �о�´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;
	m_StartX = atoi(strLine);

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;
	m_StartY = atoi(strLine);

	// �ִϸ��̼� ������ �ð��� ���´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;
	m_CompleteTime = (float)atof(strLine);

	m_AnimationTime = 0.f;

	m_FrameX = m_StartX;
	m_FrameY = m_StartY;

	// �̹��� Ű�� ��θ� ���´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	string strKey = strLine;

	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);
	strLine[Length - 1] = 0;

	TCHAR strFileName[MAX_PATH] = {};

#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, strLine, -1, strFileName, (int)strlen(strLine) * 2);
#else
	strcpy_s(strFileName, strLine);
#endif
	m_Texture = ResourceManager::Get()->LoadTexture(strKey, strFileName);

	// �÷�Ű�� ���´�.
	memset(strLine, 0, 256);
	fgets(strLine, 256, pFile);

	Length = (int)strlen(strLine);

	strLine[Length - 1] = 0;

	(int&)m_isColorKey = atoi(strLine);

	if (m_isColorKey)
	{
		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);

		Length = (int)strlen(strLine);

		strLine[Length - 1] = 0;

		unsigned char r = (unsigned char)atoi(strLine);

		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);

		Length = (int)strlen(strLine);

		strLine[Length - 1] = 0;

		unsigned char g = (unsigned char)atoi(strLine);

		memset(strLine, 0, 256);
		fgets(strLine, 256, pFile);

		Length = (int)strlen(strLine);

		if (strLine[Length - 1] == '\n')
			strLine[Length - 1] = 0;

		unsigned char b = (unsigned char)atoi(strLine);

		m_ColorKey = RGB(r, g, b);
	}
	fclose(pFile);

	return true;
}

AnimationClip * AnimationClip::Clone() const
{
	return new AnimationClip(*this);
}
#include "Animation.h"
#include "AnimationClip.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "../Object/Object.h"
#include "PathManager.h"

Animation::Animation()
	:m_CurClip(NULL), m_DefaultClip(NULL)
{
}

Animation::Animation(const Animation& Value)
{
	*this = Value;

	m_ClipMap.clear();
	m_CurClip = NULL;
	m_DefaultClip = NULL;
	m_isEnd = Value.m_isEnd;
	m_AniStart = Value.m_AniStart;

	unordered_map<string, AnimationClip*>::const_iterator StartIter = Value.m_ClipMap.begin();
	unordered_map<string, AnimationClip*>::const_iterator EndIter = Value.m_ClipMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		AnimationClip* newClip = StartIter->second->Clone();
		m_ClipMap.insert(make_pair(StartIter->first, newClip));
	}

	SetDefaultClip(m_DefaultClipName);
	SetCurClip(m_CurClipName);
}
   
Animation::~Animation()
{
	Safe_Delete_Map(m_ClipMap);
}

bool Animation::Init()
{
	m_isEnd = false;
	m_AniStart = false;

	return true;
}

void Animation::Update(float DeltaTime)
{
	m_CurClip->m_AnimationTime += DeltaTime;
	float CompleatTime = m_CurClip->m_CompleteTime / m_CurClip->m_FrameCount;

	m_isEnd = false;

	if (m_CurClip->m_Option == AO_LOOP || m_CurClip->m_Option == AO_ONCE_DESTROY || m_CurClip->m_Option == AO_ONCE_RETURN)
	{
		while (m_CurClip->m_AnimationTime >= CompleatTime)
		{
			m_CurClip->m_AnimationTime -= CompleatTime;
			m_CurClip->m_FrameX++;

			//다돌았으면 시작위치로 바꿔주고 y++
			if (m_CurClip->m_FrameX >= m_CurClip->m_StartX + m_CurClip->m_FrameCountX)
			{
				m_CurClip->m_FrameX = m_CurClip->m_StartX;
				m_CurClip->m_FrameY++;

				//y위치 다돌았으면 y위치 바꾼다.
				if (m_CurClip->m_FrameY >= m_CurClip->m_StartY + m_CurClip->m_FrameCountY)
				{
					m_CurClip->m_FrameY = m_CurClip->m_StartY;
					m_isEnd = true;

					//디폴트는 Loop값
					switch (m_CurClip->m_Option)
					{
						case AO_ONCE_RETURN:
							ChangeClip(m_DefaultClipName);
							break;
						case AO_ONCE_DESTROY:
							m_Object->SetisActiv(false);
							break;
					}//switch
				}//if(y위치)
			}//if(x위치)
		}//while
	}
	else if (m_CurClip->m_Option == AO_REVERS_LOOP || m_CurClip->m_Option == AO_REVERS_BOUNCE_LOOP || m_CurClip->m_Option == AO_REVERS_ONCE_DESTROY)
	{
		while (m_CurClip->m_AnimationTime >= CompleatTime)
		{
			m_CurClip->m_AnimationTime -= CompleatTime;
			m_CurClip->m_FrameX--;

			//다돌았으면 시작위치로 바꿔주고 y++
			if (m_CurClip->m_FrameX == 0)
			{
				m_CurClip->m_FrameX = m_CurClip->m_StartX;
				m_CurClip->m_FrameY++;

				//y위치 다돌았으면 y위치 바꾼다.
				if (m_CurClip->m_FrameY >= m_CurClip->m_StartY + m_CurClip->m_FrameCountY)
				{
					m_CurClip->m_FrameY = m_CurClip->m_StartY;
					m_isEnd = true;

					switch (m_CurClip->m_Option)
					{
						case AO_REVERS_ONCE_DESTROY:
							m_Object->SetisActiv(false);
							break;
					}//switch
				}//if(y위치)
			}//if(x위치)
		}//while
	}
}

Animation * Animation::Clone() const
{
	return new Animation(*this);
}

bool Animation::CreateAnimationClip(const string & ClipName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float FrameWidth, float FrameHeight, int FrameCountX, int FrameCountY, int FrameMaxX, int FrameMaxY, int StartX, int StartY, float CompleatTime, const string & TexKey, const TCHAR * FileName, bool bColorKey, DWORD dColorKey, const string & PathKey)
{
	AnimationClip* newClip = FindClip(ClipName);

	if (newClip != NULL)
		return false;

	newClip = new AnimationClip();

	newClip->m_Name = ClipName;
	newClip->m_Type = eType;
	newClip->m_Option = eOption;
	newClip->m_FrameSize.x = FrameWidth;
	newClip->m_FrameSize.y = FrameHeight;
	newClip->m_FrameCountX = FrameCountX;
	newClip->m_FrameCountY = FrameCountY;
	newClip->m_StartX = StartX;
	newClip->m_StartY = StartY;
	newClip->m_FrameX = StartX;
	newClip->m_FrameY = StartY;
	newClip->m_CompleteTime = CompleatTime;
	newClip->m_AnimationTime = 0.0f;
	newClip->m_FrameCount = FrameCountX * FrameCountY;
	newClip->m_Texture = ResourceManager::Get()->LoadTexture(TexKey, FileName, PathKey);
	newClip->m_isColorKey = bColorKey;
	newClip->m_ColorKey = dColorKey;
		
	m_ClipMap.insert(make_pair(ClipName, newClip));

	if (m_ClipMap.size() == 1)
	{
		SetDefaultClip(ClipName);
		SetCurClip(ClipName);
	}
	return true;
}

void Animation::SetDefaultClip(const string & ClipName)
{
	m_DefaultClipName = ClipName;
	m_DefaultClip = FindClip(ClipName);
}

void Animation::SetCurClip(const string & ClipName)
{
	m_CurClipName = ClipName;
	m_CurClip = FindClip(ClipName);

	m_CurClip->m_FrameX = m_CurClip->m_StartX;
	m_CurClip->m_FrameY = m_CurClip->m_StartY;
	m_CurClip->m_AnimationTime = 0.0f;

	m_Object->SetTexture(m_CurClip->m_Texture);
}

void Animation::ChangeClip(const string & ClipName)
{
	if (m_CurClipName == ClipName)
		return;

	SetCurClip(ClipName);
}

bool Animation::LoadAnimation(const char * FileName, const string & PathKey)
{
	AnimationClip* newClip = new AnimationClip();

	const char* tPath = PathManager::Get()->FindPathMultiByte(PathKey);
	string FullPath;
	if (tPath != NULL)
		FullPath = tPath;

	FullPath += FileName;

	//파일에서 읽어온다
	if (newClip->Load(FullPath.c_str()) == false)
	{
		SAFE_DELETE(newClip);
		return false;
	}

	if (FindClip(newClip->m_Name) != NULL)
	{
		SAFE_DELETE(newClip);
		return false;
	}

	m_ClipMap.insert(make_pair(newClip->m_Name, newClip));

	if (m_ClipMap.size() == 1)
	{
		SetDefaultClip(newClip->m_Name);
		SetCurClip(newClip->m_Name);
	}

	return true;
}

AnimationClip * Animation::FindClip(const string & KeyName)
{
	unordered_map<string, AnimationClip*>::iterator FindIter = m_ClipMap.find(KeyName);

	if (FindIter == m_ClipMap.end())
		return NULL;

	return FindIter->second;
}

int Animation::GetFrameX() const
{
	return m_CurClip->m_FrameX;
}

int Animation::GetFrameY() const
{
	return  m_CurClip->m_FrameY;
}

Vector2 Animation::GetFrameSize() const
{
	return m_CurClip->m_FrameSize;
}

ANIMATION_OPTION Animation::GetOption() const
{
	return m_CurClip->m_Option;
}

float Animation::GetCompleatTime() const
{
	return m_CurClip->GetCompleatTime();
}

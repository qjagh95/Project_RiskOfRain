#pragma once
//클립을 모아서 관리해준다.
#include "../stdafx.h"

class Object;
class AnimationClip;
class Animation
{
public:
	bool Init();
	void Update(float DeltaTime);
	Animation* Clone() const;

	bool CreateAnimationClip(const string& ClipName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float FrameWidth, float FrameHeight,
							 int FrameCountX , int FrameCountY, int FrameMaxX, int FrameMaxY, int StartX, int StartY,  float CompleatTime, const string& TexKey, const TCHAR* FileName,
							 bool bColorKey = true, DWORD dColorKey = RGB(255,0,255),
							 const string& PathKey = TEXTURE_PATH);

	bool LoadAnimation(const char* FileName, const string& PathKey = DATA_PATH);
	void SetDefaultClip(const string& ClipName);
	void SetCurClip(const string& ClipName);
	void ChangeClip(const string& ClipName);

	int GetFrameX() const;
	int GetFrameY() const;
	Vector2 GetFrameSize() const;
	void SetObject(Object* Value) { m_Object = Value; }
	bool GetIsEnd() const { return m_isEnd; }
	void SetAniStart(bool Value) { m_AniStart = Value; }
	bool GetAniStart() const { return m_AniStart; }

private:
	Object* m_Object;
	unordered_map<string, AnimationClip*> m_ClipMap;

	string m_CurClipName;
	string m_DefaultClipName;
	AnimationClip* m_CurClip;
	AnimationClip* m_DefaultClip;

	bool m_isEnd;
	bool m_AniStart;

//------------------------private함수--------------------------------
private:
	AnimationClip* FindClip(const string& KeyName);

//-------------------------------------------------------------------
public:
	friend class Object;

private:
	Animation();
	Animation(const Animation& Value);
	~Animation();
};


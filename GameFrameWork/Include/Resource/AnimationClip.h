#pragma once
//하나의 모션정보를 저장하기위하여 만들었다
#include "../stdafx.h"
class Texture;
class AnimationClip
{
public:
	bool Load(const char* FullPath);
	AnimationClip* Clone() const;

	DWORD GetColorKey() const { return m_ColorKey; }
	bool GetIsColorKey() const { return m_isColorKey; }

private:
	string	m_Name; ///클립 이름(행동이름)

	ANIMATION_TYPE	m_Type; ///통이미지인가?, 아니면 하나하나 파일이 분리되있나?
	ANIMATION_OPTION m_Option; ///루프, 한번하고 사라짐(버프), 한번하고 돌아감
	Texture* m_Texture;
	Vector2	m_FrameSize; ///사이즈 (FrameWidth,FrameHeight)

	///현재 보여지고있는 애니메이션 프레임 인덱스x
	int	m_FrameX; 
	///현재 보여지고있는 애니메이션 프레임 인덱스x
	int	m_FrameY;
	///애니메이션 표시할 줄의 이미지갯수x
	int	m_FrameCountX;
	///애니메이션 표시할 줄의 이미지갯수y
	int	m_FrameCountY;
	///이미지 전체를 일정한 크기로 자른 갯수 x
	int	m_FrameMaxX; 
	///이미지 전체를 일정한 크기로 자른 갯수 y
	int	m_FrameMaxY;  
	///시작할 애니메이션 위치
	int	m_StartX;     
	///시작할 에니메이션 위치
	int	m_StartY;     
	///한줄의 애니메이션 총 갯수 (FrameX * FrameY)
	int m_FrameCount; 
	
	///시간값을 + 시켜줄 변수
	float m_AnimationTime;
	///애니메이션 완료 시간
	float m_CompleteTime;

	bool m_isColorKey;
	DWORD m_ColorKey;

public:
	friend class Animation;

	~AnimationClip();

private:
	AnimationClip();
	AnimationClip(const AnimationClip& Value);
};


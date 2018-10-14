#pragma once
//�ϳ��� ��������� �����ϱ����Ͽ� �������
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
	string	m_Name; ///Ŭ�� �̸�(�ൿ�̸�)

	ANIMATION_TYPE	m_Type; ///���̹����ΰ�?, �ƴϸ� �ϳ��ϳ� ������ �и����ֳ�?
	ANIMATION_OPTION m_Option; ///����, �ѹ��ϰ� �����(����), �ѹ��ϰ� ���ư�
	Texture* m_Texture;
	Vector2	m_FrameSize; ///������ (FrameWidth,FrameHeight)

	///���� ���������ִ� �ִϸ��̼� ������ �ε���x
	int	m_FrameX; 
	///���� ���������ִ� �ִϸ��̼� ������ �ε���x
	int	m_FrameY;
	///�ִϸ��̼� ǥ���� ���� �̹�������x
	int	m_FrameCountX;
	///�ִϸ��̼� ǥ���� ���� �̹�������y
	int	m_FrameCountY;
	///�̹��� ��ü�� ������ ũ��� �ڸ� ���� x
	int	m_FrameMaxX; 
	///�̹��� ��ü�� ������ ũ��� �ڸ� ���� y
	int	m_FrameMaxY;  
	///������ �ִϸ��̼� ��ġ
	int	m_StartX;     
	///������ ���ϸ��̼� ��ġ
	int	m_StartY;     
	///������ �ִϸ��̼� �� ���� (FrameX * FrameY)
	int m_FrameCount; 
	
	///�ð����� + ������ ����
	float m_AnimationTime;
	///�ִϸ��̼� �Ϸ� �ð�
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


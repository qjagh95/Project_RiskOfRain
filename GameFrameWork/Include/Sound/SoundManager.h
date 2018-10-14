#pragma once
#include "../stdafx.h"
#include "fmod.hpp"

using namespace FMOD;

#ifdef _WIN64 
#pragma comment(lib,"fmod64_vc")
#else
#pragma comment(lib,"fmod_vc")
#endif

struct SoundInfo
{
	Sound* pSound;
	bool isLoop;
	int ChannelNumber;
};

class SoundManager
{
public:
	bool Init();
	void Update();

	bool LoadSound(const string& KeyName, bool isLoop, const TCHAR* FileName, const string& PathKey = SOUND_PATH);
	void Play(const string& KeyName, bool BgmMode = false);
	void Stop(const string& KeyName);

private:
	SoundInfo* FindSound(const string& KeyName);

private:
	System* m_System;
	Channel* m_Channel[10];
	bool m_isChannel[9]; ///bgm은 무조건 0번에서 재생되기 때문에 9

	unordered_map<string, SoundInfo*> m_SoundMap;

public:
	CLASS_IN_SINGLE(SoundManager);
};


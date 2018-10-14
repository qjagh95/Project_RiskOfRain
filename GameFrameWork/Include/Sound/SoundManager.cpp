#include "SoundManager.h"
#include "../Resource/PathManager.h"

INIT_STATIC_VAR(SoundManager)

SoundManager::SoundManager()
{
	memset(m_Channel, 0, sizeof(Channel*) * 10);
	memset(m_isChannel, 0, sizeof(bool) * 9);
}

SoundManager::~SoundManager()
{
	unordered_map<string, SoundInfo*>::iterator StartIter = m_SoundMap.begin();
	unordered_map<string, SoundInfo*>::iterator EndIter = m_SoundMap.end();

	for (; StartIter != EndIter ;StartIter++)
	{
		StartIter->second->pSound->release();
		SAFE_DELETE(StartIter->second);
	}

	m_System->close();
	m_System->release();
}

bool SoundManager::Init()
{
	System_Create(&m_System);
	m_System->init(10, FMOD_INIT_NORMAL, NULL);

	return true;
}

void SoundManager::Update()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_isChannel[i - 1] == true)
		{
			bool isPlay = false;
			m_Channel[i]->isPlaying(&isPlay);

			if (isPlay == false)
			{
				m_Channel[i] = NULL;
				m_isChannel[i - 1] = false;
			}
		}
	}
}

bool SoundManager::LoadSound(const string & KeyName, bool isLoop, const TCHAR * FileName, const string & PathKey)
{
	SoundInfo* newInfo = FindSound(KeyName);

	if (newInfo != NULL)
		return false;

	const char* pPath = PathManager::Get()->FindPathMultiByte(PathKey);
	string FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	char cFileName[MAX_PATH] = {};

#ifdef _WIN64
	WideCharToMultiByte(CP_ACP, 0, FileName, -1, cFileName, lstrlen(FileName), 0, 0);
#else
	strcpy_s(cFileName, FileName);
#endif

	FullPath += cFileName;

	newInfo = new SoundInfo();
	newInfo->isLoop = isLoop;

	FMOD_MODE Mode = FMOD_LOOP_NORMAL;

	if (isLoop == false)
		Mode = FMOD_DEFAULT;
	
	m_System->createSound(FullPath.c_str(), Mode, NULL, &newInfo->pSound);
	
	m_SoundMap.insert(make_pair(KeyName, newInfo));

	return true;
}

void SoundManager::Play(const string & KeyName, bool BgmMode)
{
	SoundInfo* newInfo = FindSound(KeyName);

	if (newInfo == NULL)
		return;

	if (BgmMode == true)
	{
		m_System->playSound(newInfo->pSound, NULL, false, &m_Channel[0]);
	}
	else
	{
		int ChannelCount = 1;

		for (int i = 0; i < 9; i++)
		{
			if (m_isChannel[i] == false)
			{
				ChannelCount = i + 1;
				m_isChannel[i] = true;
				break;
			}
		}

		if (ChannelCount == -1)
			ChannelCount = 1;

		m_System->playSound(newInfo->pSound, NULL, false, &m_Channel[ChannelCount]);
		newInfo->ChannelNumber = ChannelCount;
	}
}

void SoundManager::Stop(const string & KeyName)
{
	SoundInfo* newInfo = FindSound(KeyName);

	if (newInfo == NULL)
		return;

	m_Channel[newInfo->ChannelNumber]->stop();
	m_isChannel[newInfo->ChannelNumber - 1] = false;
	m_Channel[newInfo->ChannelNumber] = NULL;
}

void SoundManager::GetisPlay(const string & KeyName, bool* ReturnPlaying)
{
	SoundInfo* newInfo = FindSound(KeyName);

	m_Channel[newInfo->ChannelNumber]->isPlaying(ReturnPlaying);
}

SoundInfo * SoundManager::FindSound(const string & KeyName)
{
	unordered_map<string, SoundInfo*>::iterator FindIter = m_SoundMap.find(KeyName);

	if (FindIter == m_SoundMap.end())
		return NULL;

	return FindIter->second;
}

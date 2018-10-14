#include "ResourceManager.h"
#include "Texture.h"

INIT_STATIC_VAR(ResourceManager)

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	Safe_Release_Map(TextureMap);
}

bool ResourceManager::Init()
{
	Texture * newTexture = LoadTexture("BackBuffer", L"BackBuffer.bmp");

	SAFE_RELEASE(newTexture);

	return true;
}

Texture * ResourceManager::LoadTexture(const string & KeyName, const TCHAR * FileName, const string & BaseKey)
{
	Texture* newTexture = FindTexture(KeyName);
	
	if (newTexture != NULL)
		return newTexture;

	newTexture = new Texture();

	if (newTexture->LoadTexture(KeyName, FileName, BaseKey) == false)
	{
		SAFE_RELEASE(newTexture);
		return NULL;
	}

	newTexture->AddRefCount();
	TextureMap.insert(make_pair(KeyName, newTexture));

	return newTexture;
}

Texture * ResourceManager::FindTexture(const string & KeyName)
{
	unordered_map<string, Texture*>::iterator FindIter = TextureMap.find(KeyName);

	if (FindIter == TextureMap.end())
		return NULL;

	FindIter->second->AddRefCount();

	return FindIter->second;
}

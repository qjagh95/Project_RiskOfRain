#pragma once
#include "../stdafx.h"
class Texture;
class ResourceManager
{
public:
	bool Init();
	Texture* LoadTexture(const string& KeyName, const TCHAR* FileName, const string& BaseKey = TEXTURE_PATH);
	Texture* FindTexture(const string& KeyName);

private:
	unordered_map<string, Texture*> TextureMap;

public:
	CLASS_IN_SINGLE(ResourceManager)
};


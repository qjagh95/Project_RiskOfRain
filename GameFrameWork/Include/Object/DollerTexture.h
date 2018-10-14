#pragma once
#include "Object.h"
class Texture;
class DollerTexture : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	DollerTexture* Clone() override;

	void SetDifferntTexture(Texture* pTexture);
	void SetDifferntTexture(const string& KeyName, const TCHAR* FileName);

protected:
	DollerTexture();
	DollerTexture(const DollerTexture& Value);
	~DollerTexture();

};


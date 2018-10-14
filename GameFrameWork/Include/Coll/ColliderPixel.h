#pragma once
#include "Collider.h"
class ColliderPixel : public Collider
{
public:
	bool Init() override;
	int Update(float DeltaTime) override;
	bool Collsion(Collider* Dest) override;
	void Render(HDC hDC, float DeltaTime) override;
	ColliderPixel* Clone() const override;
	void Save(FILE* pFile) override;
	void Load(FILE* pFile) override;

	void SetPixelCollsionInfo(const char* FileName, const string& PathKey = TEXTURE_PATH);
	void SetCollsionPixel(unsigned char r, unsigned char g, unsigned char b);
	void SetCollsionPixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	Pixel32 GetPixelCollsion() const { return m_WorldInfo.CollsionColor; }
	PixelInfo GetInfo() const { return m_WorldInfo; }

	bool CheckPixelCollsion(int x, int y);
	bool CheckPixelCollsion(const Vector2& Pos);

protected:
	ColliderPixel();
	ColliderPixel(const ColliderPixel& Value);
	~ColliderPixel();

private:
	PixelInfo m_VirtualInfo;
	PixelInfo m_WorldInfo;

public:
	friend class Object;
	friend class CollsionManager;
};


#include "Object.h"
class DollerUI : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	DollerUI* Clone() override;

protected:
	DollerUI();
	DollerUI(const DollerUI& Value);
	~DollerUI();
};

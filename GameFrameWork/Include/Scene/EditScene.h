#pragma once
#include "SceneComponent.h"

class TileInfo;
class Texture;
class Tile;
class Layer;
class Button;
class EditScene : public SceneComponent
{

public:
	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC hDC, float DeltaTime) override;

	void ButtonInit(Layer* UiLayer);
	void MonsterButtonInit(Layer* UiLayer);
	void OptionButtonInit(Layer* UiLayer);

	void CameraMove(float DeltaTime);
	void TileMode(float DeltaTime);
	void MonsterMode(float DeltaTime);
	void SaveLoad();

	void ChangeState(EDITOR_STATE eType);

	void SaveStageFile(const TCHAR* FileName);
	void LoadStageFile(const TCHAR* FileName);
	void SaveMonsterList(const TCHAR* FileName);
	void LoadMonFile(const TCHAR* FileName);

	void ATile1Callback(float DeltaTime);
	void ATile2Callback(float DeltaTime);
	void ATile3Callback(float DeltaTime);
	void ATile4Callback(float DeltaTime);
	void ATile5Callback(float DeltaTime);
	void ATileInnderCallback(float DeltaTime);

	void BTile1Callback(float DeltaTime);
	void BTile2Callback(float DeltaTime);
	void BTile3Callback(float DeltaTime);
	void BTile4Callback(float DeltaTime);
	void BTile5Callback(float DeltaTime);
	void BTile6Callback(float DeltaTime);
	void BTile7Callback(float DeltaTime);
	void BTile8Callback(float DeltaTime);
	void BTileInnderCallback(float DeltaTime);

	void CTile1Callback(float DeltaTime);
	void CTile2Callback(float DeltaTime);
	void CTile3Callback(float DeltaTime);
	void CTile4Callback(float DeltaTime);
	void CTile5Callback(float DeltaTime);

	void DTile1Callback(float DeltaTime);
	void DTile2Callback(float DeltaTime);
	void DTile3Callback(float DeltaTime);
	void DTile4Callback(float DeltaTime);
	void DTile5Callback(float DeltaTime);
	void DTile6Callback(float DeltaTime);
	void DTile7Callback(float DeltaTime);
	void DTile8Callback(float DeltaTime);
	void DTile9Callback(float DeltaTime);
	void DTile10Callback(float DeltaTime);

	void ETile1Callback(float DeltaTime);
	void ETile2Callback(float DeltaTime);
	void ETile3Callback(float DeltaTime);
	void ETile4Callback(float DeltaTime);
	void ETile5Callback(float DeltaTime);
	void ETile6Callback(float DeltaTime);
	void ETile7Callback(float DeltaTime);
	void ETile8Callback(float DeltaTime);
	void ETile9Callback(float DeltaTime);
	void ETile10Callback(float DeltaTime);
	void ETile11Callback(float DeltaTime);

	void FTile1Callback(float DeltaTime);
	void FTile2Callback(float DeltaTime);
	void FTile3Callback(float DeltaTime);
	void FTile4Callback(float DeltaTime);
	void FTile5Callback(float DeltaTime);
	void FTile6Callback(float DeltaTime);
	void FTile7Callback(float DeltaTime);
	void FTile8Callback(float DeltaTime);
	void FTile9Callback(float DeltaTime);
	void FTile10Callback(float DeltaTime);
	void FTile11Callback(float DeltaTime);
	void FTile12Callback(float DeltaTime);
	void FTile13Callback(float DeltaTime);
	void FTile14Callback(float DeltaTime);

	void GTile1Callback(float DeltaTime);
	void GTile2Callback(float DeltaTime);
	void GTile3Callback(float DeltaTime);
	void GTile4Callback(float DeltaTime);
	void GTile5Callback(float DeltaTime);
	void GTile6Callback(float DeltaTime);
	void GTile7Callback(float DeltaTime);
	void GTile8Callback(float DeltaTime);
	void GTile9Callback(float DeltaTime);

	void HTile1Callback(float DeltaTime);
	void HTile2Callback(float DeltaTime);
	void HTile3Callback(float DeltaTime);
	void HTile4Callback(float DeltaTime);
	void HTile5Callback(float DeltaTime);
	void HTile6Callback(float DeltaTime);
	void HTile7Callback(float DeltaTime);

	void ItemBoxCallback(float DeltaTime);
	void RopeCallback(float DeltaTime);
	void PumpCallback(float DeltaTime);

	void TelePotCallback(float DeltaTime);

	void Monster1Callback(float DeltaTime);
	void Monster2Callback(float DeltaTime);
	void Monster3Callback(float DeltaTime);
	void Monster4Callback(float DeltaTime);
	void Monster5Callback(float DeltaTime);
	void Monster6Callback(float DeltaTime);
	void Monster7Callback(float DeltaTime);
	void Monster8Callback(float DeltaTime);
	void Monster9Callback(float DeltaTime);
	void Monster10Callback(float DeltaTime);

private:
	TileInfo* TileMap;
	Tile* SelectTile;
	Texture* SelectTileTexture;
	TILE_TYPE CurType;
	Button* TileButton;

	list<Button*> TileButtonList; ///보이기 안보이기를 하기위함.
	list<Button*> MonsterButtonList;

	list<ObjectBaseSave> monsterList;
	
	EDITOR_STATE eState;

	MONSTER_TYPE monsterType;

	bool isItemOptionMode;
	bool isRopeOptionMode;
	bool isPumpOptionMode;
	bool isTelePotOptionMode;

	bool isTileShow;
	bool isMonsterButtonShow;

private:
	EditScene();
	~EditScene();

public:
	friend class Scene;
	friend class TileInfo;
};


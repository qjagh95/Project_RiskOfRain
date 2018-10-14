#include "EditScene.h"
#include "../Camera.h"
#include "../Object/TileInfo.h"
#include "../Object/Tile.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Layer.h"
#include "../Resource/PathManager.h"
#include "../Input.h"
#include "../Button.h"
#include "../Object/TileBg.h"
#include "../stdafx.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Input.h"

void EditScene::ATile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile1", TEXT("Tile/ATempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ATile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile2", TEXT("Tile/ATempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ATile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile3", TEXT("Tile/ATempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ATile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile4", TEXT("Tile/ATempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ATile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile5", TEXT("Tile/ATempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ATileInnderCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ATempTile6", TEXT("Tile/ATempTileInnder.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile1", TEXT("Tile/BTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile2", TEXT("Tile/BTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile3", TEXT("Tile/BTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile4", TEXT("Tile/BTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile5", TEXT("Tile/BTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile6", TEXT("Tile/BTempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile7", TEXT("Tile/BTempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTile8Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTile8", TEXT("Tile/BTempTile8.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::BTileInnderCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("BTempTileInnder", TEXT("Tile/BTempTileInnder.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::CTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("CTempTile1", TEXT("Tile/CTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::CTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("CTempTile2", TEXT("Tile/CTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::CTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("CTempTile3", TEXT("Tile/CTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::CTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("CTempTile4", TEXT("Tile/CTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::CTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("CTempTile5", TEXT("Tile/CTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile1", TEXT("Tile/DTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile2", TEXT("Tile/DTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile3", TEXT("Tile/DTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile4", TEXT("Tile/DTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile5", TEXT("Tile/DTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile6", TEXT("Tile/DTempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile7", TEXT("Tile/DTempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile8Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile8", TEXT("Tile/DTempTile8.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile9Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile9", TEXT("Tile/DTempTile9.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::DTile10Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("DTempTile10", TEXT("Tile/DTempTile10.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile1", TEXT("Tile/ETempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile2", TEXT("Tile/ETempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile3", TEXT("Tile/ETempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile4", TEXT("Tile/ETempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile5", TEXT("Tile/ETempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile6", TEXT("Tile/ETempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile7", TEXT("Tile/ETempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile8Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	isTelePotOptionMode = false;
	
	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile8", TEXT("Tile/ETempTile8.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile9Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile9", TEXT("Tile/ETempTile9.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile10Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile10", TEXT("Tile/ETempTile10.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ETile11Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ETempTile11", TEXT("Tile/ETempTile11.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile1", TEXT("Tile/FTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile2", TEXT("Tile/FTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile3", TEXT("Tile/FTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile4", TEXT("Tile/FTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile5", TEXT("Tile/FTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile6", TEXT("Tile/FTempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile7", TEXT("Tile/FTempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile8Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile8", TEXT("Tile/FTempTile8.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile9Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile9", TEXT("Tile/FTempTile9.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile10Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile10", TEXT("Tile/FTempTile10.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile11Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile11", TEXT("Tile/FTempTile11.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile12Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile12", TEXT("Tile/FTempTile12.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile13Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile13", TEXT("Tile/FTempTile13.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::FTile14Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("FTempTile14", TEXT("Tile/FTempTile14.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile1", TEXT("Tile/GTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile2", TEXT("Tile/GTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile3", TEXT("Tile/GTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile4", TEXT("Tile/GTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile5", TEXT("Tile/GTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile6", TEXT("Tile/GTempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isTelePotOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile7", TEXT("Tile/GTempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile8Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile8", TEXT("Tile/GTempTile8.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::GTile9Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("GTempTile9", TEXT("Tile/GTempTile9.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile1Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile1", TEXT("Tile/HTempTile1.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile2Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile2", TEXT("Tile/HTempTile2.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile3Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile3", TEXT("Tile/HTempTile3.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile4Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile4", TEXT("Tile/HTempTile4.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile5Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile5", TEXT("Tile/HTempTile5.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile6Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile6", TEXT("Tile/HTempTile6.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::HTile7Callback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("HTempTile7", TEXT("Tile/HTempTile7.bmp"));
	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::ItemBoxCallback(float DeltaTime)
{
	isItemOptionMode = true;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("ItemBox", TEXT("Tile/ItemBoxButton.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::RopeCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = true;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("Rope", TEXT("Tile/RopeButton.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::PumpCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isTelePotOptionMode = false;
	isPumpOptionMode = true;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("Pump", TEXT("Tile/JumpButton.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}
void EditScene::TelePotCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = true;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("TelePoter", TEXT("Tile/TelepotButton.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(50.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster1Callback(float DeltaTime)
{
	monsterType = MT_MONSTERONE;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster1", TEXT("EditMonster/IssacEnemy1_One.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(67.0f, 47.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster2Callback(float DeltaTime)
{
	monsterType = MT_MONSTERTWO;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster2", TEXT("EditMonster/AncientWisp_One.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(150.0f, 305.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster3Callback(float DeltaTime)
{
	monsterType = MT_MONSTERTHREE;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster3", TEXT("EditMonster/Jelly_One.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(39.0f, 72.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster4Callback(float DeltaTime)
{
	monsterType = MT_MONSTERFOUR;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster4", TEXT("EditMonster/Lemurian_One.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(45.0f, 45.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster5Callback(float DeltaTime)
{
	monsterType = MT_MONSTERFIVE;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster5", TEXT("EditMonster/Wisp_Right_Stun.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(27.0f, 50.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster6Callback(float DeltaTime)
{
	monsterType = MT_MONSTERSIX;

	SelectTileTexture = ResourceManager::Get()->LoadTexture("EditMonster6", TEXT("EditMonster/RockGolem_Right_Hold.bmp"));

	Input::Get()->SetMouseTexture(SelectTileTexture);
	Input::Get()->SetMouseTextureSize(Vector2(60.0f, 90.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

void EditScene::Monster7Callback(float DeltaTime)
{
	monsterType = MT_MONSTERSEVEN;
}

void EditScene::Monster8Callback(float DeltaTime)
{
	monsterType = MT_MONSTEREIGHT;
}

void EditScene::Monster9Callback(float DeltaTime)
{
	monsterType = MT_MONSTERNINE;
}

void EditScene::Monster10Callback(float DeltaTime)
{
	monsterType = MT_MONSTERTEN;
}

void EditScene::NoMoveButtonCallback(float DeltaTime)
{
	isItemOptionMode = false;
	isRopeOptionMode = false;
	isPumpOptionMode = false;
	isTelePotOptionMode = false;

	CurType = TT_NOMOVE;

	Input::Get()->SetMouseTexture(ResourceManager::Get()->LoadTexture("NoMoveTile", TEXT("Tile/OptionNoMove.bmp")));
	Input::Get()->SetMouseTextureSize(Vector2(60.0f, 90.0f));
	Input::Get()->SetMouseTexturePivot(0.5f, 0.5f);
}

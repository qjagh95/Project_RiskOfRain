#include "EditScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Layer.h"

#include "../Camera.h"
#include "../Input.h"
#include "../Button.h"

#include "../Resource/ResourceManager.h"

#include "../Object/TileInfo.h"
#include "../Object/Object.h"
#include "../Object/TileBg.h"
#include "../Object/Tile.h"

#include "../Object/EditMonster.h"
#include "../Object/EditMonster1.h"
#include "../Object/EditMonster2.h"
#include "../Object/EditMonster3.h"
#include "../Object/EditMonster4.h"
#include "../Object/EditMonster5.h"
#include "../Object/EditMonster6.h"

#include "../Resource/PathManager.h"
#include "../Resource/Texture.h"

#include "../Sound/SoundManager.h"

EditScene::EditScene()
	:TileMap(NULL), SelectTileTexture(NULL), SelectTile(NULL), TileButton(NULL)
	, CurType(TT_NOMAL), isItemOptionMode(false), isRopeOptionMode(false), isPumpOptionMode(false), isTileShow(true)
	,isTelePotOptionMode(false), eState(EDITOR_STATE::ES_TILE), isMonsterButtonShow(true)
	,monsterType(MONSTER_TYPE::MT_NOMAL)
{
}

EditScene::~EditScene()
{
	SAFE_RELEASE(TileMap);
	SAFE_RELEASE(SelectTileTexture);
	SAFE_RELEASE(SelectTile);
	SAFE_RELEASE(TileButton);

	Safe_Release_VecList(MonsterButtonList);
	Safe_Release_VecList(TileButtonList);
}

bool EditScene::Init()
{
	Vector2 WinSize = Core::Get()->GetWinSizeVector2();
	Camera::Get()->SetWorldSize(1800.0f, 1000.0f);

	Input::Get()->PushKey("Save", VK_F2);
	Input::Get()->PushKey("Load", VK_F3);
	Input::Get()->PushKey("TileOnOff", VK_F4);
	Input::Get()->PushKey("OptionChange", VK_F7);
	Input::Get()->PushKey("Clear", VK_RETURN);

	SoundManager::Get()->LoadSound("EditBGM", true, TEXT("RolCoTa.mp3"));

	SoundManager::Get()->Play("EditBGM", true);

	Layer* DefaultLayer = m_Scene->FindLayer("Default");
	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* UILayer = m_Scene->FindLayer("UI");

	TileBg* newBg = Object::CreateObject<TileBg>("Bg", BackLayer);

	TileMap = Object::CreateObject<TileInfo>("TileMap", DefaultLayer);
	TileMap->CreateGrid(124, 60, Vector2(6200.0f, 3000.0f));
	Camera::Get()->SetWorldSize(Vector2(6200.0f, 3000.0f));

	ButtonInit(UILayer);
	OptionButtonInit(UILayer);
	MonsterButtonInit(UILayer);

	SAFE_RELEASE(DefaultLayer);
	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(newBg);

	return true;
}

int EditScene::Input(float DeltaTime)
{
	return 0;
}

int EditScene::Update(float DeltaTime)
{
	if (isTileShow == true)
	{
		list<Button*>::iterator StartIter = TileButtonList.begin();
		list<Button*>::iterator EndIter = TileButtonList.end();

		for (; StartIter != EndIter; StartIter++)
			(*StartIter)->SetisShow(true);

	}
	else if (isTileShow == false)
	{
		list<Button*>::iterator StartIter = TileButtonList.begin();
		list<Button*>::iterator EndIter = TileButtonList.end();

		for (; StartIter != EndIter; StartIter++)
			(*StartIter)->SetisShow(false);
	}

	if (isMonsterButtonShow == true)
	{
		list<Button*>::iterator StartIter = MonsterButtonList.begin();
		list<Button*>::iterator EndIter = MonsterButtonList.end();

		for (; StartIter != EndIter; StartIter++)
			(*StartIter)->SetisShow(true);

	}
	else if (isMonsterButtonShow == false)
	{
		list<Button*>::iterator StartIter = MonsterButtonList.begin();
		list<Button*>::iterator EndIter = MonsterButtonList.end();

		for (; StartIter != EndIter; StartIter++)
			(*StartIter)->SetisShow(false);
	}

	if (KEYDOWN("OptionChange"))
	{
		static int a = (int)eState;

		if ((EDITOR_STATE)a >= ES_MAX - 1)
		{
			a = 0;
			Input::Get()->SetMouseDefaultTexture();
			ChangeState(EDITOR_STATE::ES_TILE);
		}
		else
		{
			a++;
			Input::Get()->SetMouseDefaultTexture();
			ChangeState((EDITOR_STATE)a);
		}
	}

	CameraMove(DeltaTime);

	return 0;
}

int EditScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void EditScene::Collision(float DeltaTime)
{
}

void EditScene::Render(HDC hDC, float DeltaTime)
{
	//Collsion������ �ް� �����ؾ� �ϱ⶧���� ��¿�� ���� Render���� ȣ��
	switch (eState)
	{
		case ES_TILE:
			TileMode(DeltaTime);
			break;
		case ES_MONSTER:
			MonsterMode(DeltaTime);
			break;
	}

	SaveLoad();
}

void EditScene::TileMode(float DeltaTime)
{
	isMonsterButtonShow = false;
	monsterType = MT_NOMAL;

	if (KEYDOWN("Clear"))
	{
		TileMap->ClearTileMap();
	}

	if (KEYDOWN("TileOnOff"))
	{
		if (isTileShow == true)
			isTileShow = false;
		else
			isTileShow = true;
	}

	if (KEYPRESS("LBotton"))
	{
		Vector2 mousePos = Input::Get()->GetMouseWorldPos();
		SelectTile = TileMap->GetTile(mousePos);

		if (SelectTile == NULL)
			return;

		if (isItemOptionMode == true)
		{
			if (SelectTile->GetTileType() == TT_NOMAL)
				return;

			SelectTile->SetTileType(CurType);
			SelectTile->SetTileOption(TO_ITEM);
		}
		else if (isRopeOptionMode == true)
		{
			if (SelectTile->GetTileType() == TT_NOMAL)
				return;

			SelectTile->SetTileType(CurType);
			SelectTile->SetTileOption(TO_ROPE);
		}
		else if (isPumpOptionMode == true)
		{
			if (SelectTile->GetTileType() == TT_NOMAL)
				return;

			SelectTile->SetTileType(CurType);
			SelectTile->SetTileOption(TO_PUMP);
		}
		else if (isTelePotOptionMode == true)
		{
			if (SelectTile->GetTileType() == TT_NOMAL)
				return;

			SelectTile->SetTileType(CurType);
			SelectTile->SetTileOption(TO_TELEPOT);
		}
		else
		{
			//ù��°�� �����ðž�
			if ((*TileButtonList.begin())->GetisShow() == true)
			{
				Vector2 CameraPos = Camera::Get()->GetPos();
				Vector2 CameraEnd;

				CameraEnd.x = CameraPos.x + Core::Get()->GetWinSizeVector2().x;
				CameraEnd.y = CameraPos.y + Core::Get()->GetWinSizeVector2().y / 2.0f - 34.0f;

				int a = TileMap->GetTileIndex(CameraPos);
				int b = TileMap->GetTileIndex(CameraEnd);

				if (SelectTile->GetIndex() < a || SelectTile->GetIndex() < b)
					return;
			}

			SelectTile->SetTexture(SelectTileTexture);
			SelectTile->SetTileType(CurType);
		}
		SAFE_RELEASE(SelectTile);
	}

	if (KEYPRESS("RBotton"))
	{
		//�ϳ��� True�� true
		bool Check = false;

		Check |= isRopeOptionMode;
		Check |= isItemOptionMode;
		Check |= isPumpOptionMode;
		Check |= isTelePotOptionMode;

		Vector2 mousePos = Input::Get()->GetMouseWorldPos();
		SelectTile = TileMap->GetTile(mousePos);

		if (SelectTile == NULL)
			return;

		if (Check == true)
		{
			SelectTile->SetTileOption(TO_NONE);
		}
		else
		{
			SelectTile->SetTexture("");
			SelectTile->SetTileOption(TO_NONE);
			SelectTile->SetTileType(TT_NOMAL);
		}

		SAFE_RELEASE(SelectTile);
	}
}

void EditScene::MonsterMode(float DeltaTime)
{
	isTileShow = false;

	if (KEYDOWN("Clear"))
	{
		list<ObjectBaseSave>::iterator StartIter = monsterList.begin();
		list<ObjectBaseSave>::iterator EndIter = monsterList.end();
		
		for (;StartIter != EndIter; StartIter++)
			(*StartIter).m_Object->SetisActiv(false);
	}

	if (KEYDOWN("TileOnOff"))
	{
		if (isMonsterButtonShow == true)
			isMonsterButtonShow = false;
		else
			isMonsterButtonShow = true;
	}

	if (KEYDOWN("LBotton"))
	{
		Vector2 mPos = Input::Get()->GetMouseWorldPos();

		if ((*MonsterButtonList.begin())->GetisShow() == true)
		{
			Vector2 CameraPos = Camera::Get()->GetPos();
			Vector2 EmptyPos = CameraPos + Vector2(500.0f, 50.0f);

			if ((mPos.x > CameraPos.x && mPos.x < EmptyPos.x) && (mPos.y > CameraPos.y && mPos.y < EmptyPos.y))
				return;
		}

		bool isSelect = EditMonster::GetIsSelect();

		if (isSelect == true)
			return;

		ObjectBaseSave Saver;

		switch (monsterType)
		{
			case MT_MONSTERONE:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster1", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
				SAFE_RELEASE(TempLayer);
			}
				break;
			case MT_MONSTERTWO:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster2* newMonster = (EditMonster2*)Object::CreateObject<EditMonster2>("EditMonster2", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(TempLayer);
				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERTHREE:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster3* newMonster = (EditMonster3*)Object::CreateObject<EditMonster3>("EditMonster3", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
				SAFE_RELEASE(TempLayer);
			}
				break;
			case MT_MONSTERFOUR:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster4* newMonster = (EditMonster4*)Object::CreateObject<EditMonster4>("EditMonster4", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
				SAFE_RELEASE(TempLayer);
			}
				break;
			case MT_MONSTERFIVE:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster5* newMonster = (EditMonster5*)Object::CreateObject<EditMonster5>("EditMonster5", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
				SAFE_RELEASE(TempLayer);
			}
				break;
			case MT_MONSTERSIX:
			{
				Layer* TempLayer = m_Scene->FindLayer("Default");

				EditMonster6* newMonster = (EditMonster6*)Object::CreateObject<EditMonster6>("EditMonster6", TempLayer);
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(TempLayer);
				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERSEVEN:
			{
			}
				break;
			case MT_MONSTEREIGHT:
			{
			}
				break;
			case MT_MONSTERNINE:
			{
			}
				break;
			case MT_MONSTERTEN:
			{
			}
				break;
		} //switch
		Saver.m_mType = monsterType;
		monsterList.push_back(Saver);
	}//if(moouseDown)

	if (KEYDOWN("RBotton"))
	{
		//����Ʈ���� �������.
		list<ObjectBaseSave>::iterator StartIter = monsterList.begin();
		list<ObjectBaseSave>::iterator EndIter = monsterList.end();

		for (; StartIter != EndIter; )
		{
			if ((*StartIter).m_Object->GetisActiv() == false)
				StartIter = monsterList.erase(StartIter);
			else
				StartIter++;
		}
	}
}


void EditScene::CameraMove(float DeltaTime)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		Camera::Get()->Move(Vector2(-800.0f * DeltaTime, 0.0f));
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		Camera::Get()->Move(Vector2(800.0f * DeltaTime, 0.0f));
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, -800.0f * DeltaTime));
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, 800.0f * DeltaTime));

	if (GetAsyncKeyState('A') & 0x8000)
		Camera::Get()->Move(Vector2(-500.0f * DeltaTime, 0.0f));
	else if (GetAsyncKeyState('D') & 0x8000)
		Camera::Get()->Move(Vector2(500.0f * DeltaTime, 0.0f));
	if (GetAsyncKeyState('W') & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, -500.0f * DeltaTime));
	else if (GetAsyncKeyState('S') & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, 500.0f * DeltaTime));
}

void EditScene::ChangeState(EDITOR_STATE eType)
{
	eState = eType;

	if (eState == ES_TILE)
	{
		isTileShow = true;
		isMonsterButtonShow = false;
	}
	else if (eState == ES_MONSTER)
	{
		isTileShow = false;
		isMonsterButtonShow = true;
	}
}

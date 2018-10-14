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

#include "../Resource/PathManager.h"
#include "../Resource/Texture.h"

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
	//F1 - Grid On Off
	//F2 - Save
	//F3 - Load
	//F4 - TileOnOff
	//F5 - 일시정지
	//F6 - DebugMode
	//F7 - MonsterMode
	Vector2 WinSize = Core::Get()->GetWinSizeVector2();
	Camera::Get()->SetWorldSize(1800.0f, 1000.0f);

	Input::Get()->PushKey("Save", VK_F2);
	Input::Get()->PushKey("Load", VK_F3);
	Input::Get()->PushKey("TileOnOff", VK_F4);
	Input::Get()->PushKey("OptionChange", VK_F7);
	Input::Get()->PushKey("Clear", VK_RETURN);

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
	//Collsion정보를 받고 실행해야 하기때문에 어쩔수 없이 Render에서 호출
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
			//첫번째만 가져올거야
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
		//하나라도 True면 true
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
		{
			(*StartIter).m_Object->SetisActiv(false);
		}
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
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster1", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERTWO:
			{
				EditMonster2* newMonster = (EditMonster2*)Object::CreateObject<EditMonster2>("EditMonster2", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERTHREE:
			{
				EditMonster3* newMonster = (EditMonster3*)Object::CreateObject<EditMonster3>("EditMonster3", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERFOUR:
			{
				EditMonster4* newMonster = (EditMonster4*)Object::CreateObject<EditMonster4>("EditMonster4", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERFIVE:
			{
				EditMonster5* newMonster = (EditMonster5*)Object::CreateObject<EditMonster5>("EditMonster5", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERSIX:
			{
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster6", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERSEVEN:
			{
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster7", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTEREIGHT:
			{
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster8", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERNINE:
			{
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster9", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
			case MT_MONSTERTEN:
			{
				EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster10", m_Scene->FindLayer("Default"));
				newMonster->SetPos(mPos);
				Saver.m_Object = newMonster;

				SAFE_RELEASE(newMonster);
			}
				break;
		} //switch
		Saver.m_mType = monsterType;
		monsterList.push_back(Saver);
	}//if(moouseDown)

	if (KEYDOWN("RBotton"))
	{
		//리스트에서 빼줘야함.
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
		Camera::Get()->Move(Vector2(-500.0f * DeltaTime, 0.0f));
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		Camera::Get()->Move(Vector2(500.0f * DeltaTime, 0.0f));
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, -500.0f * DeltaTime));
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		Camera::Get()->Move(Vector2(0.0f, 500.0f * DeltaTime));

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

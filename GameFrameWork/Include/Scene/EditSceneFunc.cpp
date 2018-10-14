#include "EditScene.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Layer.h"

#include "../Camera.h"
#include "../Input.h"
#include "../Button.h"

#include "../Resource/Texture.h"
#include "../Resource/PathManager.h"

#include "../Object/TileInfo.h"
#include "../Object/TileBg.h"
#include "../Object/Tile.h"

#include "../Object/EditMonster1.h"
#include "../Object/EditMonster2.h"
#include "../Object/EditMonster3.h"
#include "../Object/EditMonster4.h"
#include "../Object/EditMonster5.h"
#include "../Object/EditMonster6.h"


#include "../Object/Monster.h"

void EditScene::SaveMonsterList(const TCHAR * FileName)
{
	const char* pPath = PathManager::Get()->FindPathMultiByte(DATA_PATH);
	string MPath;
#ifdef _UNICODE
	MPath = CW2A(FileName);
#endif // _UNICODE
	
	MPath += ".stgmon";

	FILE* pFile = NULL;

	fopen_s(&pFile, MPath.c_str(), "wb");
	{
		TrueAssert(pFile == NULL);

		size_t Count = monsterList.size();
		fwrite(&Count, sizeof(Count), 1, pFile);
		
		list<ObjectBaseSave>::iterator StartIter = monsterList.begin();
		list<ObjectBaseSave>::iterator EndIter = monsterList.end();

		for (;StartIter != EndIter ; StartIter++)
		{
			ObjectSave Saver;

			Saver.Pos = StartIter->m_Object->GetPos();
			Saver.m_mType = StartIter->m_mType;

			fwrite(&Saver, sizeof(ObjectSave), 1, pFile);
		}
	}
	fclose(pFile);
}

void EditScene::SaveStageFile(const TCHAR * FileName)
{
	string MPath;
#ifdef _UNICODE
	MPath = CW2A(FileName);
#endif // _UNICODE

	MPath += ".stg";
	TileMap->SaveFromFullPath(MPath.c_str());
}

void EditScene::LoadStageFile(const TCHAR * FileName)
{
	string MPath;
#ifdef _UNICODE
	MPath = CW2A(FileName);
#endif // _UNICODE

	//레이어를 미리 받는다
	Layer* newLayer = TileMap->GetLayer();

	//기존정보를 날린다
	TileMap->SetisActiv(false);
	SAFE_RELEASE(TileMap);

	TileMap = Object::CreateObject<TileInfo>("EditorObject", newLayer);
	SAFE_RELEASE(newLayer);

	Layer* TempLayer = m_Scene->FindLayer("Default");
	TileMap->LoadFromFullPath(MPath.c_str(), TempLayer);
	SAFE_RELEASE(TempLayer);
}

void EditScene::LoadMonFile(const TCHAR* FileName)
{
	monsterList.clear();

	string MPath;
#ifdef _UNICODE
	MPath = CW2A(FileName);
#endif // _UNICODE

	FILE* pFile = NULL;
	fopen_s(&pFile, MPath.c_str(), "rb");
	{
		TrueAssert(pFile == NULL);

		size_t Count;
		fread(&Count, sizeof(Count), 1, pFile);
		ObjectBaseSave Save;

		for (size_t i = 0 ; i < Count; i++)
		{
			ObjectSave Saver;
			fread(&Saver, sizeof(ObjectSave), 1, pFile);

			switch (Saver.m_mType)
			{
				case MT_MONSTERONE:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster1* newMonster = (EditMonster1*)Object::CreateObject<EditMonster1>("EditMonster1", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
					SAFE_RELEASE(TempLayer);
				}
				break;
				case MT_MONSTERTWO:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster2* newMonster = (EditMonster2*)Object::CreateObject<EditMonster2>("EditMonster2", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
					SAFE_RELEASE(TempLayer);
				}
				break;
				case MT_MONSTERTHREE:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster3* newMonster = (EditMonster3*)Object::CreateObject<EditMonster3>("EditMonster3", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
				}
				break;
				case MT_MONSTERFOUR:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster4* newMonster = (EditMonster4*)Object::CreateObject<EditMonster4>("EditMonster4", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
					SAFE_RELEASE(TempLayer);
				}
				break;
				case MT_MONSTERFIVE:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster5* newMonster = (EditMonster5*)Object::CreateObject<EditMonster5>("EditMonster5", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
					SAFE_RELEASE(TempLayer);
				}
				break;
				case MT_MONSTERSIX:
				{
					Layer* TempLayer = m_Scene->FindLayer("Default");

					EditMonster6* newMonster = (EditMonster6*)Object::CreateObject<EditMonster6>("EditMonster6", TempLayer);
					newMonster->SetPos(Saver.Pos);

					Save.m_Object = newMonster;

					SAFE_RELEASE(newMonster);
					SAFE_RELEASE(TempLayer);
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
			Save.m_mType = Saver.m_mType;

			monsterList.push_back(Save);
		}
	}
	fclose(pFile);
}

void EditScene::SaveLoad()
{
	if (KEYDOWN("Save"))
	{
		ShowCursor(TRUE);

		//일반적으로 저장할때 뜨는 파일UI 구조체
		OPENFILENAME OFN;
		TCHAR FileName[MAX_PATH] = {};
		const TCHAR* pDir = PathManager::Get()->FindPath(ROOT_PATH);

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = Core::Get()->GetHwnd();
		OFN.lpstrFilter = TEXT("All File(*.*)\0*.*\0Stage File\0*.stg\0");
		OFN.lpstrFile = FileName;
		OFN.lpstrDefExt = TEXT("");
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrInitialDir = pDir;
		if (GetSaveFileName(&OFN) != 0)
		{
			SaveStageFile(FileName);
			SaveMonsterList(FileName);
		}
		ShowCursor(FALSE);
	}

	if (KEYDOWN("Load"))
	{
		ShowCursor(TRUE);

		//일반적으로 저장할때 뜨는 파일UI 구조체
		OPENFILENAME OFN;
		TCHAR FileName[MAX_PATH] = {};
		const TCHAR* pDir = PathManager::Get()->FindPath(ROOT_PATH);

		memset(&OFN, 0, sizeof(OPENFILENAME));
		OFN.lStructSize = sizeof(OPENFILENAME);
		OFN.hwndOwner = Core::Get()->GetHwnd();
		OFN.lpstrFilter = TEXT("All File(*.*)\0*.*\0Stage File\0*.stg\0");
		OFN.lpstrFile = FileName;
		OFN.lpstrDefExt = TEXT("");
		OFN.nMaxFile = MAX_PATH;
		OFN.lpstrInitialDir = pDir;
		if (GetOpenFileName(&OFN) != 0)
		{
			wstring Arr;
			Arr = FileName;
			size_t Cut = Arr.find_last_of(L".", Arr.size());

			if (lstrlen(Arr.c_str()) - Cut == 4)
			{
				Arr = Arr.replace(Cut, Arr.size(), L".stgmon");
				LoadStageFile(FileName);
				LoadMonFile(Arr.c_str());
			}
			else
			{
				Arr = Arr.replace(Cut, Arr.size(), L".stg");
				LoadStageFile(Arr.c_str());
				LoadMonFile(FileName);
			}

		}

		ShowCursor(FALSE);
	}
}

void EditScene::ButtonInit(Layer* UiLayer)
{
	TileButton = Object::CreateObject<Button>("ATileButton1", UiLayer);
	TileButton->SetPos(0.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATile1Callback, this);
	TileButton->SetTexture("ATempTile1", TEXT("Tile/ATempTile1.bmp"));

	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ATileButton2", UiLayer);
	TileButton->SetPos(50.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATile2Callback, this);
	TileButton->SetTexture("ATempTile2", TEXT("Tile/ATempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ATileButton3", UiLayer);
	TileButton->SetPos(100.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATile3Callback, this);
	TileButton->SetTexture("ATempTile3", TEXT("Tile/ATempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ATileButton4", UiLayer);
	TileButton->SetPos(150.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATile4Callback, this);
	TileButton->SetTexture("ATempTile4", TEXT("Tile/ATempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ATileButton5", UiLayer);
	TileButton->SetPos(200.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATile5Callback, this);
	TileButton->SetTexture("ATempTile5", TEXT("Tile/ATempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("BTileButton1", UiLayer);
	TileButton->SetPos(250.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile1Callback, this);
	TileButton->SetTexture("BTempTile1", TEXT("Tile/BTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton2", UiLayer);
	TileButton->SetPos(300.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile2Callback, this);
	TileButton->SetTexture("BTempTile1", TEXT("Tile/BTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton3", UiLayer);
	TileButton->SetPos(350.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile3Callback, this);
	TileButton->SetTexture("BTempTile3", TEXT("Tile/BTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton4", UiLayer);
	TileButton->SetPos(400.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile4Callback, this);
	TileButton->SetTexture("BTempTile4", TEXT("Tile/BTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton5", UiLayer);
	TileButton->SetPos(450.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile5Callback, this);
	TileButton->SetTexture("BTempTile5", TEXT("Tile/BTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton6", UiLayer);
	TileButton->SetPos(500.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile6Callback, this);
	TileButton->SetTexture("BTempTile6", TEXT("Tile/BTempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton7", UiLayer);
	TileButton->SetPos(550.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile7Callback, this);
	TileButton->SetTexture("BTempTile7", TEXT("Tile/BTempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButton8", UiLayer);
	TileButton->SetPos(600.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTile8Callback, this);
	TileButton->SetTexture("BTempTile8", TEXT("Tile/BTempTile8.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	//////////////////////////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("CTileButton1", UiLayer);
	TileButton->SetPos(0.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::CTile1Callback, this);
	TileButton->SetTexture("CTempTile1", TEXT("Tile/CTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("CTileButton2", UiLayer);
	TileButton->SetPos(50.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::CTile2Callback, this);
	TileButton->SetTexture("CTempTile2", TEXT("Tile/CTempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("CTileButton3", UiLayer);
	TileButton->SetPos(100.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::CTile3Callback, this);
	TileButton->SetTexture("CTempTile3", TEXT("Tile/CTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("CTileButton4", UiLayer);
	TileButton->SetPos(150.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::CTile4Callback, this);
	TileButton->SetTexture("CTempTile4", TEXT("Tile/CTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("CTileButton5", UiLayer);
	TileButton->SetPos(200.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::CTile5Callback, this);
	TileButton->SetTexture("CTempTile5", TEXT("Tile/CTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton1", UiLayer);
	TileButton->SetPos(250.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile1Callback, this);
	TileButton->SetTexture("DTempTile1", TEXT("Tile/DTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton2", UiLayer);
	TileButton->SetPos(300.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile2Callback, this);
	TileButton->SetTexture("DTempTile2", TEXT("Tile/DTempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton3", UiLayer);
	TileButton->SetPos(350.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile3Callback, this);
	TileButton->SetTexture("DTempTile3", TEXT("Tile/DTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton4", UiLayer);
	TileButton->SetPos(400.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile4Callback, this);
	TileButton->SetTexture("DTempTile4", TEXT("Tile/DTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton5", UiLayer);
	TileButton->SetPos(450.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile5Callback, this);
	TileButton->SetTexture("DTempTile5", TEXT("Tile/DTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton6", UiLayer);
	TileButton->SetPos(500.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile6Callback, this);
	TileButton->SetTexture("DTempTile6", TEXT("Tile/DTempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton7", UiLayer);
	TileButton->SetPos(550.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile7Callback, this);
	TileButton->SetTexture("DTempTile7", TEXT("Tile/DTempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton8", UiLayer);
	TileButton->SetPos(600.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile8Callback, this);
	TileButton->SetTexture("DTempTile8", TEXT("Tile/DTempTile8.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton9", UiLayer);
	TileButton->SetPos(650.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile9Callback, this);
	TileButton->SetTexture("DTempTile9", TEXT("Tile/DTempTile9.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("DTileButton10", UiLayer);
	TileButton->SetPos(700.0f, 50.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::DTile10Callback, this);
	TileButton->SetTexture("DTempTile10", TEXT("Tile/DTempTile10.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	///////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("ETileButton1", UiLayer);
	TileButton->SetPos(0.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile1Callback, this);
	TileButton->SetTexture("ETempTile1", TEXT("Tile/ETempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton2", UiLayer);
	TileButton->SetPos(50.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile2Callback, this);
	TileButton->SetTexture("ETempTile2", TEXT("Tile/ETempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton3", UiLayer);
	TileButton->SetPos(100.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile3Callback, this);
	TileButton->SetTexture("ETempTile3", TEXT("Tile/ETempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton4", UiLayer);
	TileButton->SetPos(150.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile4Callback, this);
	TileButton->SetTexture("ETempTile4", TEXT("Tile/ETempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton5", UiLayer);
	TileButton->SetPos(200.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile5Callback, this);
	TileButton->SetTexture("ETempTile5", TEXT("Tile/ETempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton6", UiLayer);
	TileButton->SetPos(250.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile6Callback, this);
	TileButton->SetTexture("ETempTile6", TEXT("Tile/ETempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton7", UiLayer);
	TileButton->SetPos(300.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile7Callback, this);
	TileButton->SetTexture("ETempTile7", TEXT("Tile/ETempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton8", UiLayer);
	TileButton->SetPos(350.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile8Callback, this);
	TileButton->SetTexture("ETempTile8", TEXT("Tile/ETempTile8.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton9", UiLayer);
	TileButton->SetPos(400.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile9Callback, this);
	TileButton->SetTexture("ETempTile9", TEXT("Tile/ETempTile9.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton10", UiLayer);
	TileButton->SetPos(450.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile10Callback, this);
	TileButton->SetTexture("ETempTile10", TEXT("Tile/ETempTile10.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ETileButton11", UiLayer);
	TileButton->SetPos(500.0f, 100.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ETile11Callback, this);
	TileButton->SetTexture("ETempTile11", TEXT("Tile/ETempTile11.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	////////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("FTileButton1", UiLayer);
	TileButton->SetPos(0.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile1Callback, this);
	TileButton->SetTexture("FTempTile1", TEXT("Tile/FTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton2", UiLayer);
	TileButton->SetPos(50.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile2Callback, this);
	TileButton->SetTexture("FTempTile2", TEXT("Tile/FTempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton3", UiLayer);
	TileButton->SetPos(100.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile3Callback, this);
	TileButton->SetTexture("FTempTile3", TEXT("Tile/FTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton4", UiLayer);
	TileButton->SetPos(150.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile4Callback, this);
	TileButton->SetTexture("FTempTile4", TEXT("Tile/FTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton5", UiLayer);
	TileButton->SetPos(200.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile5Callback, this);
	TileButton->SetTexture("FTempTile5", TEXT("Tile/FTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton6", UiLayer);
	TileButton->SetPos(250.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile6Callback, this);
	TileButton->SetTexture("FTempTile6", TEXT("Tile/FTempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton7", UiLayer);
	TileButton->SetPos(300.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile7Callback, this);
	TileButton->SetTexture("FTempTile7", TEXT("Tile/FTempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton8", UiLayer);
	TileButton->SetPos(350.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile8Callback, this);
	TileButton->SetTexture("FTempTile8", TEXT("Tile/FTempTile8.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton9", UiLayer);
	TileButton->SetPos(400.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile9Callback, this);
	TileButton->SetTexture("FTempTile9", TEXT("Tile/FTempTile9.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton10", UiLayer);
	TileButton->SetPos(450.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile10Callback, this);
	TileButton->SetTexture("FTempTile10", TEXT("Tile/FTempTile10.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton11", UiLayer);
	TileButton->SetPos(500.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile11Callback, this);
	TileButton->SetTexture("FTempTile11", TEXT("Tile/FTempTile11.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton12", UiLayer);
	TileButton->SetPos(550.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile12Callback, this);
	TileButton->SetTexture("FTempTile12", TEXT("Tile/FTempTile12.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton13", UiLayer);
	TileButton->SetPos(600.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile13Callback, this);
	TileButton->SetTexture("FTempTile13", TEXT("Tile/FTempTile13.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("FTileButton14", UiLayer);
	TileButton->SetPos(650.0f, 150.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::FTile14Callback, this);
	TileButton->SetTexture("FTempTile14", TEXT("Tile/FTempTile14.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	////////////////////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("GTileButton1", UiLayer);
	TileButton->SetPos(0.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile1Callback, this);
	TileButton->SetTexture("GTempTile1", TEXT("Tile/GTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton2", UiLayer);
	TileButton->SetPos(50.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile2Callback, this);
	TileButton->SetTexture("GTempTile2", TEXT("Tile/GTempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton3", UiLayer);
	TileButton->SetPos(100.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile3Callback, this);
	TileButton->SetTexture("GTempTile3", TEXT("Tile/GTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton4", UiLayer);
	TileButton->SetPos(150.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile4Callback, this);
	TileButton->SetTexture("GTempTile4", TEXT("Tile/GTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton5", UiLayer);
	TileButton->SetPos(200.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile5Callback, this);
	TileButton->SetTexture("GTempTile5", TEXT("Tile/GTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton6", UiLayer);
	TileButton->SetPos(250.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile6Callback, this);
	TileButton->SetTexture("GTempTile6", TEXT("Tile/GTempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton7", UiLayer);
	TileButton->SetPos(300.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile7Callback, this);
	TileButton->SetTexture("GTempTile7", TEXT("Tile/GTempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton8", UiLayer);
	TileButton->SetPos(350.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile8Callback, this);
	TileButton->SetTexture("GTempTile8", TEXT("Tile/GTempTile8.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("GTileButton9", UiLayer);
	TileButton->SetPos(400.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::GTile9Callback, this);
	TileButton->SetTexture("GTempTile9", TEXT("Tile/GTempTile9.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	//////////////////////////////////////////////////////////////////////////////////////////

	TileButton = Object::CreateObject<Button>("HTileButton1", UiLayer);
	TileButton->SetPos(450.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile1Callback, this);
	TileButton->SetTexture("HTempTile1", TEXT("Tile/HTempTile1.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton2", UiLayer);
	TileButton->SetPos(500.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile2Callback, this);
	TileButton->SetTexture("HTempTile2", TEXT("Tile/HTempTile2.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton3", UiLayer);
	TileButton->SetPos(550.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile3Callback, this);
	TileButton->SetTexture("HTempTile3", TEXT("Tile/HTempTile3.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton4", UiLayer);
	TileButton->SetPos(600.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile4Callback, this);
	TileButton->SetTexture("HTempTile4", TEXT("Tile/HTempTile4.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton5", UiLayer);
	TileButton->SetPos(650.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile5Callback, this);
	TileButton->SetTexture("HTempTile5", TEXT("Tile/HTempTile5.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton6", UiLayer);
	TileButton->SetPos(700.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile6Callback, this);
	TileButton->SetTexture("HTempTile6", TEXT("Tile/HTempTile6.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("HTileButton7", UiLayer);
	TileButton->SetPos(750.0f, 200.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::HTile7Callback, this);
	TileButton->SetTexture("HTempTile7", TEXT("Tile/HTempTile7.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	//////////////////////////////////////////////////////////////////////////////////////////////
}

void EditScene::MonsterButtonInit(Layer * UiLayer)
{
	TileButton = Object::CreateObject<Button>("Monster1Button", UiLayer);
	TileButton->SetPos(0.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster1Callback, this);
	TileButton->SetTexture("Monster1", TEXT("Tile/M1.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster2Button", UiLayer);
	TileButton->SetPos(50.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster2Callback, this);
	TileButton->SetTexture("Monster2", TEXT("Tile/M2.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster3Button", UiLayer);
	TileButton->SetPos(100.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster3Callback, this);
	TileButton->SetTexture("Monster3", TEXT("Tile/M3.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster4Button", UiLayer);
	TileButton->SetPos(150.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster4Callback, this);
	TileButton->SetTexture("Monster4", TEXT("Tile/M4.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster5Button", UiLayer);
	TileButton->SetPos(200.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster5Callback, this);
	TileButton->SetTexture("Monster5", TEXT("Tile/M5.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster6Button", UiLayer);
	TileButton->SetPos(250.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster6Callback, this);
	TileButton->SetTexture("Monster6", TEXT("Tile/M6.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster7Button", UiLayer);
	TileButton->SetPos(300.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster7Callback, this);
	TileButton->SetTexture("Monster7", TEXT("Tile/M7.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster8Button", UiLayer);
	TileButton->SetPos(350.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster8Callback, this);
	TileButton->SetTexture("Monster8", TEXT("Tile/M8.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster9Button", UiLayer);
	TileButton->SetPos(400.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster9Callback, this);
	TileButton->SetTexture("Monster9", TEXT("Tile/M9.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("Monster10Button", UiLayer);
	TileButton->SetPos(450.0f, 0.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::Monster10Callback, this);
	TileButton->SetTexture("Monster10", TEXT("Tile/M10.bmp"));
	TileButton->AddRefCount();
	MonsterButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);
}

void EditScene::OptionButtonInit(Layer* UiLayer)
{
	TileButton = Object::CreateObject<Button>("ItemBoxButton", UiLayer);
	TileButton->SetPos(0.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ItemBoxCallback, this);
	TileButton->SetTexture("ItemBox", TEXT("Tile/ItemBoxButton.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("PumpButton", UiLayer);
	TileButton->SetPos(50.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::PumpCallback, this);
	TileButton->SetTexture("Pump", TEXT("Tile/JumpButton.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);
	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("RopeButton", UiLayer);
	TileButton->SetPos(100.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::RopeCallback, this);
	TileButton->SetTexture("Rope", TEXT("Tile/RopeButton.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("TelepotButton", UiLayer);
	TileButton->SetPos(150.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::TelePotCallback, this);
	TileButton->SetTexture("Telepot", TEXT("Tile/TelepotButton.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("ATileButtonIndder", UiLayer);
	TileButton->SetPos(200.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::ATileInnderCallback, this);
	TileButton->SetTexture("ATileButtonIndder", TEXT("Tile/ATempTileInnder.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("BTileButtonInnder", UiLayer);
	TileButton->SetPos(250.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::BTileInnderCallback, this);
	TileButton->SetTexture("BTempTileInnder", TEXT("Tile/BTempTileInnder.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);

	TileButton = Object::CreateObject<Button>("NoMoveTile", UiLayer);
	TileButton->SetPos(300.0f, 250.0f);
	TileButton->SetSize(50.0f, 50.0f);
	TileButton->SetIsOffset(false);
	TileButton->SetCallBack<EditScene>(&EditScene::NoMoveButtonCallback, this);
	TileButton->SetTexture("NoMoveTile", TEXT("Tile/OptionNoMove.bmp"));
	TileButton->AddRefCount();
	TileButtonList.push_back(TileButton);

	SAFE_RELEASE(TileButton);
}

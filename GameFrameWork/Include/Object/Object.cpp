#include "Object.h"
#include "../Scene/Scene.h"
#include "../Scene/Layer.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Texture.h"
#include "../Resource/Animation.h"
#include "../Resource/AnimationClip.h"
#include "../Resource/PathManager.h"

#include "../Coll/Collider.h"
#include "../Coll/ColliderCircle.h"
#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderPoint.h"
#include "../Coll/ColliderPixel.h"

#include "../Coll/CollsionManager.h"

#include "../Camera.h"

unordered_map<string, Object*> Object::m_Prototype;
unordered_multimap<string, Object*> Object::m_SceneObject;
list<Object*> Object::m_FindList;

Object::Object()
	:m_Texture(NULL), m_Scene(NULL), m_Layer(NULL), m_Animation(NULL),
	m_Angle(0.0f), MoveSpeed(0.0f), m_ColorKey(0), Force(0.0f), ForceOrigin(0.0f), GravityTime(0.0f),
	isColorKey(false),isGravity(false), isCameraMode(true)
{
}

Object::Object(const Object & Value)
{
	*this = Value;

	m_RefCount = 1;

	if (m_Texture != NULL)
		m_Texture->AddRefCount();

	//복사될 객체안에있는 충돌체리스트를 받는다.
	list<Collider*>::const_iterator StartIter = Value.m_ColliderList.begin();
	list<Collider*>::const_iterator EndIter = Value.m_ColliderList.end();

	//기존것을 날린다
	m_ColliderList.clear();
	
	for (; StartIter != EndIter; StartIter++)
	{
		//Collider가 가지고있는 오브젝트가 이 this ObjectClass로 바뀐다.
		Collider* newCollider = (*StartIter)->Clone();
		newCollider->SetObject(this);

		m_ColliderList.push_back(newCollider);
	}
	
	if (m_Animation != NULL)
	{
		m_Animation = m_Animation->Clone();
		m_Animation->SetObject(this);
	}
}

Object::~Object()
{
	SAFE_RELEASE(m_Texture);
	SAFE_DELETE(m_Animation);		
	Safe_Release_VecList(m_ColliderList);
}

bool Object::Init()
{
	return true;
}

int Object::Input(float DeltaTime)
{
	return 0;
}

int Object::Update(float DeltaTime)
{
	if (m_Animation != NULL)
		m_Animation->Update(DeltaTime);

	if (isGravity == false)
		return 0;

	GravityTime += DeltaTime;

	m_Pos.y -= Force * DeltaTime;
	m_TempMove.y -= Force * DeltaTime;

	Force -= GRAVITY * GravityTime * GravityTime;

	return 0;
}

int Object::LateUpdate(float DeltaTime)
{
	//충돌은 모든 업데이트가 끝난뒤 돈다.
	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
		(*StartIter)->Update(DeltaTime);

	return 0;
}

void Object::Collision(float DeltaTime)
{
	
}

void Object::Render(HDC hDC, float DeltaTime)
{
	if (m_Texture != NULL)
	{
		Vector2 LeftTop = m_Pos - (m_Size * m_Pivot);

		if(isCameraMode == true)
			LeftTop -= Camera::Get()->GetPos();

		//여기서 이미지좌표를 옮긴다 (애니메이션)
		int FrameX = 0;
		int FrameY = 0;
		Vector2 tSize = m_Size;

		if (m_Animation != NULL)
		{
			FrameX = m_Animation->GetFrameX() * (int)(m_Animation->GetFrameSize().x);
			FrameY = m_Animation->GetFrameY() * (int)(m_Animation->GetFrameSize().y);
			tSize = m_Animation->GetFrameSize();
			m_ColorKey = m_Animation->m_CurClip->GetColorKey();
			isColorKey = m_Animation->m_CurClip->GetIsColorKey();
		}

		FrameX += (int)m_Offset.x;
		FrameY += (int)m_Offset.y;

		if (isColorKey == false)
			BitBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)tSize.x, (int)tSize.y, m_Texture->GetMemDC(), FrameX, FrameY, SRCCOPY);
		else 
			TransparentBlt(hDC, (int)LeftTop.x, (int)LeftTop.y, (int)tSize.x, (int)tSize.y, m_Texture->GetMemDC(), FrameX, FrameY, (int)tSize.x, (int)tSize.y, (UINT)m_ColorKey);
	}

	m_TempMove = Vector2(0.0f, 0.0f);

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	//모든 랜더가 끝나면 충돌체 랜더 시작
	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
		(*StartIter)->Render(hDC, DeltaTime);
}

void Object::SaveFile(const char * FileName, const string & BaseKey)
{
	const char* pPath = PathManager::Get()->FindPathMultiByte(BaseKey);

	string FullPath;

	if (pPath != NULL)
		FullPath = pPath;
	
	FullPath += FileName;

	SaveFromFullPath(FullPath.c_str());
}

void Object::SaveFromFullPath(const char * FileName)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, FileName, "wb");
	
	if (pFile == NULL)
		return;

	Save(pFile);

	fclose(pFile);
}

void Object::Save(FILE * pFile)
{
	int TagLenth = (int)m_Tag.length();
	fwrite(&TagLenth, sizeof(int), 1, pFile);
	fwrite(m_Tag.c_str(), sizeof(char), TagLenth, pFile);

	fwrite(&m_ObjectType, sizeof(OBJECT_TYPE), 1, pFile);
	fwrite(&m_Pos, sizeof(Vector2), 1, pFile);
	fwrite(&m_Size, sizeof(Vector2), 1, pFile);
	fwrite(&m_Pivot, sizeof(Vector2), 1, pFile);
	fwrite(&m_Offset, sizeof(Vector2), 1, pFile);
	fwrite(&m_Angle, sizeof(float), 1, pFile);
	fwrite(&MoveSpeed, sizeof(float), 1, pFile);
	fwrite(&m_ColorKey, sizeof(DWORD), 1, pFile);
	fwrite(&isColorKey, sizeof(bool), 1, pFile);
	fwrite(&isGravity, sizeof(bool), 1, pFile);
	fwrite(&Force, sizeof(float), 1, pFile);
	fwrite(&ForceOrigin, sizeof(float), 1, pFile);
	fwrite(&GravityTime, sizeof(float), 1, pFile);

	bool isTexture = false;

	if (m_Texture != NULL)
		isTexture = true;

	fwrite(&isTexture, sizeof(bool), 1, pFile);

	if (m_Texture == false)
		return;

	string TexKeyName = m_Texture->GetKey();
	const TCHAR* pFileName = m_Texture->GetFileName();
	string PathKey = m_Texture->GetPathKey();

	int iLenth = (int)TexKeyName.length();
	fwrite(&iLenth, sizeof(int), 1, pFile);
	fwrite(TexKeyName.c_str(), sizeof(char), iLenth, pFile);

	iLenth = lstrlen(pFileName);
	fwrite(&iLenth, sizeof(int), 1, pFile);
	fwrite(pFileName, sizeof(TCHAR), iLenth, pFile);

	iLenth = (int)PathKey.length();
	fwrite(&iLenth, sizeof(int), 1, pFile);
	fwrite(PathKey.c_str(), sizeof(char), iLenth, pFile);

	size_t CollSize = m_ColliderList.size();

	fwrite(&CollSize, sizeof(size_t), 1, pFile);

	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		COLLIDER_TYPE CollType = (*StartIter)->GetCollType();
		fwrite(&CollType, sizeof(COLLIDER_TYPE), 1, pFile);
		(*StartIter)->Save(pFile);
	}

	bool isAnimation = false;

	if (m_Animation != NULL)
		isAnimation = true;

	fwrite(&isAnimation, sizeof(bool), 1, pFile);
}

void Object::LoadFile(const char * FileName, Layer* pLayer ,const string & BaseKey)
{
	const char* pPath = PathManager::Get()->FindPathMultiByte(BaseKey);

	string FullPath;

	if (pPath != NULL)
		FullPath = pPath;

	FullPath += FileName;

	LoadFromFullPath(FullPath.c_str(), pLayer);
}

void Object::LoadFromFullPath(const char * FileName, Layer* pLayer)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, FileName, "rb");

	if (pFile == NULL)
		return;

	Load(pFile, pLayer);

	fclose(pFile);
}

void Object::Load(FILE * pFile, Layer* pLayer)
{
	int TagLenth = 0;
	char TagName[256] = {};

	fread(&TagLenth, sizeof(int), 1, pFile);
	fread(TagName, sizeof(char), TagLenth, pFile);
	m_Tag = TagName;

	fread(&m_ObjectType, sizeof(OBJECT_TYPE), 1, pFile);
	fread(&m_Pos, sizeof(Vector2), 1, pFile);
	fread(&m_Size, sizeof(Vector2), 1, pFile);
	fread(&m_Pivot, sizeof(Vector2), 1, pFile);
	fread(&m_Offset, sizeof(Vector2), 1, pFile);
	fread(&m_Angle, sizeof(float), 1, pFile);
	fread(&MoveSpeed, sizeof(float), 1, pFile);
	fread(&m_ColorKey, sizeof(DWORD), 1, pFile);
	fread(&isColorKey, sizeof(bool), 1, pFile);
	fread(&isGravity, sizeof(bool), 1, pFile);
	fread(&Force, sizeof(float), 1, pFile);
	fread(&ForceOrigin, sizeof(float), 1, pFile);
	fread(&GravityTime, sizeof(float), 1, pFile);

	bool isTexture = false;

	if (m_Texture != NULL)
		isTexture = true;

	fread(&isTexture, sizeof(bool), 1, pFile);

	if (isTexture == false)
		return;

	int iLenth = 0;
	char KeyName[256] = {};
	char PathKey[256] = {};
	TCHAR FileName[MAX_PATH] = {};

	fread(&iLenth, sizeof(int), 1, pFile);
	fread(KeyName, sizeof(char), iLenth, pFile);

	fread(&iLenth, sizeof(int), 1, pFile);
	fread(FileName, sizeof(TCHAR), iLenth, pFile);

	fread(&iLenth, sizeof(int), 1, pFile);
	fread(PathKey, sizeof(char), iLenth, pFile);

	m_Texture = ResourceManager::Get()->LoadTexture(KeyName, FileName, PathKey);

	size_t CollSize = m_ColliderList.size();

	fread(&CollSize, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < CollSize; i++)
	{
		COLLIDER_TYPE CollType;

		fread(&CollType, sizeof(COLLIDER_TYPE), 1, pFile);

		Collider* newColl = NULL;

		switch (CollType)
		{
			case CT_RECT:
				newColl = AddCollider<ColliderRect>("CollRect");
				break;
			case CT_CIRCLE:
				newColl = AddCollider<ColliderCircle>("CollCircle");
				break;
			case CT_POINT:
				newColl = AddCollider<ColliderPoint>("CollPoint");
				break;
			case CT_PIXEL:
				newColl = AddCollider<ColliderPixel>("CollPixel");
				break;
		}

		newColl->Load(pFile);
		SAFE_RELEASE(newColl);
	}

	bool isAnimation = false;
	fread(&isAnimation, sizeof(bool), 1, pFile);
}

Scene * Object::GetScene() const
{
	if (m_Scene != NULL) 
		m_Scene->AddRefCount();

	return m_Scene;
}

Layer * Object::GetLayer() const
{
	if (m_Layer != NULL)
		m_Layer->AddRefCount();

	return m_Layer;
}

bool Object::SetTexture(const string & KeyName, const TCHAR * FileName, const string & BaseKey)
{
	SAFE_RELEASE(m_Texture);
	m_Texture = ResourceManager::Get()->LoadTexture(KeyName, FileName, BaseKey);

	return true;
}

bool Object::SetTexture(const string & KeyName)
{
	SAFE_RELEASE(m_Texture);
	m_Texture = ResourceManager::Get()->FindTexture(KeyName);

	return true;
}

bool Object::SetTexture(Texture * Value)
{
	m_Texture = Value;

	if (m_Texture != NULL)
		m_Texture->AddRefCount();

	return true;
}

Object * Object::FindPrototype(const string & TagName)
{
	unordered_map<string, Object*>::iterator FineIter = m_Prototype.find(TagName);
	if (FineIter == m_Prototype.end())
		return NULL;

	FineIter->second->AddRefCount();

	return FineIter->second;
}

Object * Object::FindSceneObject(const string & TagName)
{
	unordered_multimap<string, Object*>::iterator FindIter = m_SceneObject.find(TagName);

	if (FindIter == m_SceneObject.end())
		return NULL;

	FindIter->second->AddRefCount();

	return FindIter->second;
}

const list<Object*>* Object::FindSceneObjects(const string & TagName)
{
	EraseFindList();

	//태그네임이 같은것들을 골라낸다. (equal_range 함수)
	//결국 리스트형태와 비슷해진다.
	//pair<unordered_multimap<string, Object*>::iterator, unordered_multimap<string, Object*>::iterator> newPair = m_SceneObject.equal_range(TagName);
	
	//auto : 선언과 동시에 무조건 초기화를 해야한다.
	//지정하는 값 타입으로 변수타입이 설정된다.
	//중간에 다른값을 넣으면 컴퓨터가 화낸다.

	auto newPair = m_SceneObject.equal_range(TagName);

	unordered_multimap<string, Object*>::iterator StartIter = newPair.first;
	unordered_multimap<string, Object*>::iterator EndIter = newPair.second;

	//멀티맵은 키의중복이 허용되야만 찾기가 가능하기때문.
	//탐색속도가 빠른 맵을이용해서 탐색하고
	//중간삽입삭제가 가장빠른 리스트를 이용하여 삽입삭제한다.
	//최적의 방법!

	while (StartIter != EndIter)
	{
		StartIter->second->AddRefCount();
		//돌면서 탐색리스트에 넣어준다.
		m_FindList.push_back(StartIter->second);
		StartIter++;
	}

	return &m_FindList;
}

void Object::EraseFindList()
{
	Safe_Release_VecList(m_FindList);
}

bool Object::AddAnimationClip(const string & ClipName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float FrameWidth, float FrameHeight, int FrameCountX, int FrameCountY, int FrameMaxX, int FrameMaxY, int StartX, int StartY, float CompleatTime, const string & TexKey, const TCHAR * FileName, bool bColorKey, DWORD dColorKey, const string & PathKey)
{
	if (m_Animation == NULL)
	{
		m_Animation = new Animation();
		m_Animation->SetObject(this);
	}
	return m_Animation->CreateAnimationClip(ClipName, eType, eOption, FrameWidth, FrameHeight, FrameCountX, FrameCountY, FrameMaxX, FrameMaxY, StartX, StartY, CompleatTime, TexKey, FileName, bColorKey, dColorKey ,PathKey);
}

bool Object::LoadAnimation(const char* FileName, const string & ClipName)
{
	if (m_Animation == NULL)
	{
		m_Animation = new Animation();
		m_Animation->SetObject(this);
	}

	return m_Animation->LoadAnimation(FileName, ClipName);
}

void Object::ChangeClip(const string & ClipName)
{
	if (m_Animation->m_CurClipName == ClipName)
		return;

	m_Animation->ChangeClip(ClipName);
}

string Object::GetClipName() const
{
	return m_Animation->GetClipName();
}

void Object::EraseSceneObject(const string & TagName, Object * pObject)
{	
	auto newPair = m_SceneObject.equal_range(TagName);

	unordered_multimap<string, Object*>::iterator StartIter = newPair.first;
	unordered_multimap<string, Object*>::iterator EndIter = newPair.second;

	while (StartIter != EndIter)
	{
		if (StartIter->second == pObject)
		{
			SAFE_RELEASE(pObject);
			m_SceneObject.erase(StartIter);
			break;
		}
		StartIter++;
	}
}

void Object::Move(float x, float y)
{
	m_TempMove.x += x;
	m_TempMove.y += y;

	m_Pos.x += x;
	m_Pos.y += y;
}

void Object::Move(float x, float y, float DeltaTime)
{
	m_TempMove.x += x * DeltaTime;
	m_TempMove.y += y * DeltaTime;

	m_Pos.x += x * DeltaTime;
	m_Pos.y += y * DeltaTime;
}

void Object::Move(const Vector2 & Dir)
{
	m_TempMove += Dir;
	m_Pos += Dir;
}

void Object::Move(const Vector2 & Dir, float DeltaTime)
{
	m_TempMove += Dir * DeltaTime;
	m_Pos += Dir * DeltaTime;
}

void Object::MoveByAngle(float DeltaTime)
{
	m_TempMove.x += MoveSpeed * DeltaTime * cosf(Math::DgreeToRadian(m_Angle));
	m_TempMove.y += MoveSpeed * DeltaTime * sinf(Math::DgreeToRadian(m_Angle));

	m_Pos.x += MoveSpeed * DeltaTime * cosf(Math::DgreeToRadian(m_Angle));
	m_Pos.y += MoveSpeed * DeltaTime * sinf(Math::DgreeToRadian(m_Angle));
}  

Object * Object::CreateCloneObject(const string & TagName, Layer * pLayer)
{
	Object* FindProto = FindPrototype(TagName);

	if (FindProto == NULL)
		return NULL;

	//복제하여 생성한다. 
	Object* newObject = FindProto->Clone();

	SAFE_RELEASE(FindProto);

	if (pLayer != NULL)
		pLayer->AddObject(newObject);

	newObject->AddRefCount();
	m_SceneObject.insert(make_pair(TagName, newObject));

	return newObject;
}

void Object::ErasePrototype(Scene * pScene)
{
	unordered_map<string, Object*>::iterator StartIter = m_Prototype.begin();
	unordered_map<string, Object*>::iterator EndIter = m_Prototype.end();

	for (; StartIter != EndIter; )
	{
		if (StartIter->second->m_Scene == pScene)
		{
			SAFE_RELEASE(StartIter->second);
			StartIter = m_Prototype.erase(StartIter);
			EndIter = m_Prototype.end();
		}
		else
			StartIter++;
	}
}

void Object::EraseSceneObject(Scene * pScene)
{ 
	unordered_multimap<string, Object*>::iterator StartIter = m_SceneObject.begin();
	unordered_multimap<string, Object*>::iterator EndIter = m_SceneObject.end();

	for (; StartIter != EndIter; )
	{
		if (StartIter->second->m_Scene == pScene)
		{
			SAFE_RELEASE(StartIter->second);
			StartIter = m_SceneObject.erase(StartIter);
			EndIter = m_SceneObject.end();
		}
		else
			StartIter++;
	}
}
void Object::SetColliderCallBack(const string & TagName, void(*pFunc)(Collider *, Collider *, float), COLLSION_STATE eState)
{
	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->SetCallBack(pFunc, eState);
			break;
		}
	}
}
Collider * Object::GetCollider(const string & TagName)
{
	list<Collider*>::iterator StartIter = m_ColliderList.begin();
	list<Collider*>::iterator EndIter = m_ColliderList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->AddRefCount();
			return (*StartIter);
		}
	}
	return NULL;
}
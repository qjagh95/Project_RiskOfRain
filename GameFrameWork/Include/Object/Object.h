#pragma once
#include "../RefCount.h"
class Scene;
class Layer;
class Texture;
class Collider;
class Animation;
class Object : public RefCount
{
public:
	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void CollsionAfterUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

	void SaveFile(const char* FileName, const string& BaseKey = DATA_PATH);
	void SaveFromFullPath(const char* FileName);
	virtual void Save(FILE* pFile);
	void LoadFile(const char* FileName, Layer* pLayer , const string& BaseKey = DATA_PATH);
	void LoadFromFullPath(const char* FileName, Layer* pLayer);
	virtual void Load(FILE* pFile, Layer* pLayer);

	//������Ÿ�� �����ý���
	//�Ѿ˰������ �ϳ��� ���Ͽ��� �о� �����س��� �ʿ� ����ִ´�
	//�ʾ��� �����͸� ��� ���縦 �Ͽ� �����Ѵ�
	//�׷��� Clone�� �������.

	//������ �ʿ� �ϳ��� ������Ʈ�� �±��̸��� ���� insert�ѵ�
	//�ʿ��� Object�� Find�� �� Object�� ��������ڸ� �̿��Ͽ� (return new Object(*this))
	//�ش� ���̾ AddObject���ִ� ���̴�.
	virtual Object* Clone() = 0;

	void SetScene(Scene* Value) { m_Scene = Value; }
	Scene* GetScene() const;
	void SetLayer(Layer* Value) { m_Layer = Value; }
	Layer* GetLayer() const;

	float GetAngle() const { return m_Angle; }
	void SetAngle(float Value) { m_Angle = Value; }
	void SetMoveSpeed(float Value) { MoveSpeed = Value; }
	float GetMoveSpeed() const { return MoveSpeed; }

	bool SetTexture(const string& KeyName, const TCHAR * FileName, const string& BaseKey = TEXTURE_PATH);
	bool SetTexture(const string& KeyName);
	bool SetTexture(Texture* Value);

	void Move(float x, float y);
	void Move(float x, float y, float DeltaTime);
	void Move(const Vector2& Dir);
	void Move(const Vector2& Dir, float DeltaTime);
	void Move(float xDir);
	void MoveByAngle(float DeltaTime);
	void Rotation(float RotationSpeed, float DeltaTime) { m_Angle += RotationSpeed * DeltaTime; }

	static Object* CreateCloneObject(const string& TagName, Layer* pLayer);

	//Ư�������� �Ѿ�� ��� ������Ÿ�� ������Ʈ�� �����
	static void ErasePrototype(Scene* pScene);
	static void EraseSceneObject(Scene* pScene);
	static void EraseSceneObject(const string& TagName, Object* pObject);
	static void EraseFindList();

	bool AddAnimationClip(const string& ClipName, ANIMATION_TYPE eType, ANIMATION_OPTION eOption, float FrameWidth, float FrameHeight,
		int FrameCountX, int FrameCountY, int FrameMaxX, int FrameMaxY, int StartX, int StartY,
		float CompleatTime, const string& TexKey, const TCHAR* FileName,
		bool bColorKey = true, DWORD dColorKey = RGB(255, 0, 255),
		const string& PathKey = TEXTURE_PATH);
	bool LoadAnimation(const char* FileName, const string& ClipName);
	void ChangeClip(const string& ClipName);
	string GetClipName() const;
	void SetDefaultAnimation(const string& ClipName);

	void DestroyColorKey() { isColorKey = false; }

	//����Ʈ�� �����ͷ� �����ϴ� ������
	//�׳� list<Object*>�� ���Ͻ� �޴� ����Ʈ��
	//���簡 �Ͼ��. �����ϴ� �۾��� �����⶧����
	//����Ʈ�� �ּҸ� ��ȯ�Ѵ�.
	static const list<Object*>* FindSceneObjects(const string& TagName);

	//Object�� �������ִ� �浹ü ����Ʈ�� �ּҸ� ��ȯ�ϱ�����(������Ʈ�� �������ִ� �浹ü ����� �������)
	const list<Collider*>* GetColliderList() const { return &m_ColliderList; }

	template<typename T>
	static T* CreatePrototype(const string& TagName, Scene* CurScene)
	{
		T* FindProto = (T*)FindPrototype(TagName);

		if (FindProto != NULL)
			return NULL;

		FindProto = new T();
		FindProto->SetTag(TagName);
		FindProto->SetScene(CurScene);

		if (FindProto->Init() == false)
		{
			SAFE_RELEASE(FindProto);
			return NULL;
		}

		FindProto->AddRefCount();
		m_Prototype.insert(make_pair(TagName, FindProto));

		return FindProto;
	}

	template<typename T>
	static T* CreateObject(const string& TagName, Layer* pLayer = NULL)
	{
		T* newObject = new T();
		newObject->SetTag(TagName);

		if (pLayer != NULL)
			pLayer->AddObject(newObject);

		if (newObject->Init() == false)
		{
			if (pLayer != NULL)
				pLayer->EraseObject(newObject);

			SAFE_RELEASE(newObject);
			return NULL;
		}

		newObject->AddRefCount();
		m_SceneObject.insert(make_pair(TagName, newObject));
		return newObject;
	}

	template<typename T>
	T* AddCollider(const string& TagName)
	{
		T* newCollider = new T();

		newCollider->SetTag(TagName);
		newCollider->SetObject(this);

		if (newCollider->Init() == false)
		{
			SAFE_RELEASE(newCollider);
			return NULL;
		}

		newCollider->AddRefCount();
		m_ColliderList.push_back(newCollider);

		return newCollider;
	}
	template<typename T>
	void SetColliderCallBack(const string& TagName, T* pObject, void(*pFunc)(Collider*, Collider*, float), COLLSION_STATE eState)
	{
		list<Collider*>::iterator StartIter = m_ColliderList.begin();
		list<Collider*>::iterator EndIter = m_ColliderList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if ((*StartIter)->GetTag() == TagName)
			{
				(*StartIter)->SetCallBack(pObject, pFunc, eState);
				break;
			}
		}
	}
	void SetColliderCallBack(const string& TagName, void(*pFunc)(Collider*, Collider*, float), COLLSION_STATE eState);

	void SetMoveUpPos(float y) { m_Pos.y += y; }
	void SetPos(float x, float y) { m_Pos.x = x, m_Pos.y = y; }
	void SetPos(const Vector2& Value) { m_Pos.x = Value.x, m_Pos.y = Value.y; }
	void SetSize(float x, float y) { m_Size.x = x, m_Size.y = y; }
	void SetSize(const Vector2& Value) { m_Size.x = Value.x, m_Size.y = Value.y; }
	void SetPivot(float x, float y) { m_Pivot.x = x, m_Pivot.y = y; }
	void SetPivot(const Vector2& Value) { m_Pivot.x = Value.x, m_Pivot.y = Value.y; }
	void SetColorKey(char r, char g, char b) { m_ColorKey = RGB(r, g, b), isColorKey = true; }
	void SetColorKey(DWORD Value) { m_ColorKey = Value, isColorKey = true; }

	void SetGravity(bool Value) { isGravity = Value; }
	bool GetIsGravity() const { return isGravity; }
	void SetForce(float Value) { Force = Value, ForceOrigin = Value; }
	float GetForce() const { return Force; }
	float GetFirceOrigin() const { return ForceOrigin; }

	bool GetIsCameraMode() const { return isCameraMode; }
	void SetIsCameraMode(bool Value) { isCameraMode = Value; }

	void ClearGravityTime() { GravityTime = 0.0f; }

	Vector2 GetPos() const { return m_Pos; }
	Vector2 GetSize() const { return m_Size; }
	Vector2 GetPivot() const { return m_Pivot; }

	OBJECT_TYPE GetObjectType() const { return m_ObjectType; }
	Collider* GetCollider(const string& TagName);

protected:
	Object();
	Object(const Object& Value);
	virtual ~Object() = 0;

	Scene* m_Scene;
	Layer* m_Layer;

	Vector2 m_Pos;
	Vector2 m_Size;
	Vector2 m_Pivot;
	Vector2 m_TempMove;

	Vector2 LeftTop;
	Vector2 RightBottom;

	DWORD m_ColorKey;

	bool isColorKey;
	float m_Angle;
	float MoveSpeed;
	bool isCameraMode;

	Texture* m_Texture;
	Animation* m_Animation;

	bool isGravity;
	float Force;
	float ForceOrigin;
	float GravityTime;

	OBJECT_TYPE m_ObjectType;

	Vector2 m_Offset; ///��ư�̹����� ǥ���ϱ�����.
	list<Collider*> m_ColliderList; ///�浹ü ����Ʈ

protected:
	static Object* FindPrototype(const string& TagName);
	static Object* FindSceneObject(const string& TagName);

	//��� Clone.. Find�� �ϸ� ��������ڸ� ȣ�����ִ¿뵵
	static unordered_map<string, Object*> m_Prototype;			///Ű���ߺ��� ��������ʴ´�.
																
	//���� �ϳ� �� ������ ������
	//�ߺ����� ����ϱ����Ͽ�
	//CreateObj, CreateCloneObj�� �Ҷ�
	//���ÿ� insert�� �Ѵ�.
	static unordered_multimap<string, Object*> m_SceneObject;	///Ű���ߺ��� ����Ѵ�.
	static list<Object*> m_FindList;							///Ž������Ʈ(���Ի����� �����Ƿ� ����Ʈ�� �޴´�)
};


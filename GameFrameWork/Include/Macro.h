#pragma once
#include <assert.h>

#define	SAFE_DELETE(p)	if(p != NULL)	{ delete p; p = NULL; }
#define SAFE_RELEASE(p) if(p != NULL) {p->Release(); p = NULL;}
#define	SAFE_DELETE_ARRAY(p)	if(p != NULL)	{ delete[] p; p = NULL; }

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)
#endif

#define TrueAssert(p) assert(!p)
#define PI 3.141592f
#define GRAVITY 0.98f

#define	CLASS_IN_SINGLE(Type)	\
	private:\
		static Type*	instance;\
	public:\
		static Type* Get()\
		{\
			if (!instance)\
				instance = new Type;\
			return instance;\
		}\
		static void Delete()\
		{\
			SAFE_DELETE(instance);\
		}\
	private:\
		Type();\
		~Type();

#define	INIT_STATIC_VAR(Type)	Type* Type::instance = NULL;
#define	GET_INSTANCE(Type)	Type::Get()
#define	DELETE_INSTANCE(Type)	Type::Delete()

#define KEYPRESS(key) Input::Get()->KeyPress(key)
#define KEYDOWN(key) Input::Get()->KeyDown(key)
#define KEYUP(key) Input::Get()->KeyUp(key)

#ifdef UNICODE
typedef wstring	MyString;
#else
typedef string	MyString;
#endif // UNICODE


#define ROOT_PATH "Root_Path"
#define TEXTURE_PATH "Texture_Path"
#define DATA_PATH "Data_Path"
#define SOUND_PATH "Sound_Path"


#define GETMOUSESCREEMPOS Input::Get()->GetMouseScreenPos()
#define GETMOUSEWORLDPOS Input::Get()->GetMouseWorldPos()
#define GETMOUSEGAP Input::Get()->GetMouseGap()



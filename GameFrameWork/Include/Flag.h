#pragma once

//ColliderType
enum COLLIDER_TYPE
{
	CT_RECT,
	CT_CIRCLE,
	CT_POINT,
	CT_PIXEL,
};

enum COLLSION_STATE
{
	CS_COLFIRST,
	CS_COLDOING,
	CS_COLEND,
	CS_COLMAX,
};

struct Pixel8
{
	unsigned char cPixel;
};


struct Pixel24
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};


struct Pixel32
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct PixelInfo
{
	void* cPixel;
	unsigned int PixelSize;
	unsigned int PixelCount;
	unsigned int Width;
	unsigned int Height;
	Vector2 WorldPos;
	Pixel32 CollsionColor;
};

enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME,
	AT_END,
};

enum ANIMATION_OPTION
{
	AO_LOOP,
	AO_ONCE_RETURN,
	AO_ONCE_DESTROY,
	AO_ONCE_STOP,
	AO_REVERS_LOOP,
};

enum OBJECT_TYPE
{
	OT_PLAYER,
	OT_MONSTER,
	OT_BULLET,
	OT_EFFECT,
	OT_UI,
	OT_BACKGROUND,
	OT_ITEM,
	OT_ROPE,
	OT_PUMP,
	OT_TELEPOT,
	OT_SHIELD,
	OT_BAR,
	OT_EDITOBJECT,
	OT_MAX,
};

enum BUTTON_STATE
{
	BS_NOMAL,
	BS_OVER,
	BS_CLICK,
};

enum BAR_DIR
{
	BD_LEFT,
	BD_RIGHT,
	BD_UP,
	BD_DOWN,
	BD_END,
};

enum TILE_TYPE
{
	TT_NOMAL,
	TT_NOMOVE,
};

enum TILE_OPTION
{
	TO_NONE,
	TO_ITEM,
	TO_ROPE,
	TO_PUMP,
	TO_TELEPOT,
};

enum MONSTER_TYPE
{
	MT_NOMAL,
	MT_MONSTERONE,
	MT_MONSTERTWO,
	MT_MONSTERTHREE,
	MT_MONSTERFOUR,
	MT_MONSTERFIVE,
	MT_MONSTERSIX,
	MT_MONSTERSEVEN,
	MT_MONSTEREIGHT,
	MT_MONSTERNINE,
	MT_MONSTERTEN,
	MT_BOSSONE,
	MT_BOSSTWO,
};

enum MONSTER_STATE
{
	MS_IDLE,
	MS_TRACE,
	MS_ATTACK
};

enum PLAYER_STATE
{
	PS_IDLE,
	PS_MOVE,
	PS_JUMPING,
	PS_ROPE,
	PS_SKILL1,
	PS_SKILL2,
	PS_SKILL3,
	PS_SKILL4,
	PS_MAX,
};

enum EDITOR_STATE
{
	ES_TILE,
	ES_MONSTER,
	ES_MAX,
};

enum ITEMBOX_OPEN
{
	//이넘으로 아이템종류 죄다 박아넣자..
	IO_ITEM, 
	IO_MISSILE,
};

class Object;
struct ObjectBaseSave
{
	Object* m_Object;
	MONSTER_TYPE m_mType;
	char StageFileName;
};

struct ObjectSave
{
	Vector2 Pos;
	MONSTER_TYPE m_mType;
};

enum SKILL_TYPE
{
	ST_SKILLONE,
	ST_SKILLTWO,
	ST_SKILLTHREE,
	ST_SKILLFOUR,
};
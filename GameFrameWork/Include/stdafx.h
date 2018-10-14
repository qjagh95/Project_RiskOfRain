#pragma once

#include <iostream>
#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>
#include <time.h>
#include <map>
#include <functional>
#include <math.h>
#include <conio.h>
#include <atlstr.h>
#include <random>
#include <thread>

using namespace std;

#include "Macro.h"
#include "Vector2.h"
#include "Rect.h"
#include "Math.h"
#include "Circle.h"
#include "Core.h"
#include "Flag.h"

#include "Keyboard.h"

#pragma comment(lib, "msimg32.lib")

#include <crtdbg.h>

#define KEYPress(Key) Keyboard::Get()->KeyPress(Key)
#define KEYDown(Key) Keyboard::Get()->KeyDown(Key)
#define KEYUp(Key) Keyboard::Get()->KeyUp(Key)


template<typename T>
void Safe_Delete_VecList(T& _Val)
{
	T::iterator	iterStart = _Val.begin();
	T::iterator	iterEnd = _Val.end();

	for (; iterStart != iterEnd; iterStart++)
		SAFE_DELETE(*iterStart);

	_Val.clear();
}

template <typename T>
void Safe_Release_VecList(T& _Val)
{
	T::iterator	iterStart = _Val.begin();
	T::iterator	iterEnd = _Val.end();

	for (; iterStart != iterEnd; ++iterStart)
		SAFE_RELEASE((*iterStart));

	_Val.clear();
}

template<typename T>
void Safe_Delete_Map(T& _Val)
{
	T::iterator	iterStart = _Val.begin();
	T::iterator	iterEnd = _Val.end();

	for (; iterStart != iterEnd; iterStart++)
		SAFE_DELETE(iterStart->second);

	_Val.clear();
}


template<typename T>
void Safe_Release_Map(T& _Val)
{
	T::iterator	iterStart = _Val.begin();
	T::iterator	iterEnd = _Val.end();

	for (; iterStart != iterEnd; iterStart++)
		SAFE_RELEASE(iterStart->second);

	_Val.clear();
}

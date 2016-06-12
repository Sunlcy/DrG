#pragma once
#include <Windows.h>

//standard color of element identifiers
enum class ElementColor : COLORREF
{
	BLACK = RGB(0, 0, 0),
	RED = RGB(255, 0, 0),
	GREEN = RGB(0, 255, 0),
	BLUE = RGB(0, 0, 255)
};
#pragma once
#include "framework.h"
#include "RES_MANAGER.h"
#include "RENDERER.h"
#include "S_MODEL.h"
#include "PALLETE.h"

class EDITOR
{
public:
	RES_MANAGER resManager;
	RENDERER renderer;
	S_MODEL sModel;
	PALLETE pallete;
	EDITOR()
	{

	}
	void init(HWND win, HINSTANCE hInstance);	
};


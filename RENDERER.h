#pragma once
#include "framework.h"
#include "RES_MANAGER.h"
#include "R_MODEL.h"



class RENDERER
{
public:
	RES_MANAGER* resManager;
	R_MODEL rModel;	
	void init(RES_MANAGER* res);
	void render();
};


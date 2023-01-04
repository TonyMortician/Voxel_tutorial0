#pragma once
#define STB_IMAGE_IMPLEMENTATION   
#include "framework.h"
#include "Shader.h"
#include "RES_MANAGER.h"

class PALLETE
{
public:
	RES_MANAGER* resManager;	
	GLuint palleteText;
	
	void init(RES_MANAGER* res);
	void loadPalleteText();
};


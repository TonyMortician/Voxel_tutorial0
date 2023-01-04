#pragma once
#include "framework.h"
#include "Shader.h"
#include "RES_MANAGER.h"
#include "camera01.h"



class R_MODEL
{
public:
	RES_MANAGER* resManager;		
	camera01 cam2;
	Shader modelShader;
	GLuint vao;
	glm::mat4 model;
	glm::mat4 perspective;

	void init(RES_MANAGER* res);	
	void renderModel();		
};


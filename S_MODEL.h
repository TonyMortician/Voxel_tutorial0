#pragma once
#include "framework.h"
#include "RES_MANAGER.h"

class S_MODEL
{
public:
	glm::vec3 tSize;
	glm::vec3 mSize;
	GLuint texture;
	RES_MANAGER* resManager{ nullptr };

	void init(RES_MANAGER *res);
	void createModel();
};


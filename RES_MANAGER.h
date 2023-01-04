#pragma once
#include "framework.h"



struct mainWinData
{
	HWND hWnd;
	HINSTANCE hInstance;
};

class RES_MANAGER
{
public:
	GLuint modelTexture{ 0 };
	GLuint palleteTexture{ 0 };
	GLuint pNum{ 0 };
	glm::vec3 modelTSize;
	glm::vec3 modelMSize;
	mainWinData mainWin;
	float pSize{ 5.0f };
	bool isSet{ 0 };
	void init(HWND hwnd, HINSTANCE hInstance);	
};


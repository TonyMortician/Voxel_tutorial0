#pragma once
#include "framework.h"
#include "RES_MANAGER.h"
#include "Shader.h"

class R_EDIT
{
public:
	RES_MANAGER* resManager;
	Shader editShader;
	Shader brushShader;
	Shader editTop;
	Shader editFront;
	Shader editLeft;
	Shader editRight;
	Shader editBack;
	GLuint vao;
	void init(RES_MANAGER* res);
	
	void renderGrid();
	void renderCursor();
	
	void setPointsNum();
	void setBrushPoints();
	GLuint pointsNum{ 0 };
	GLuint brushPointsNum{ 0 };

	void renderGridTop();
	void renderGridFront();
	void renderGridLeft();
	void renderGridRight();
	void renderGridBack();

	void renderGridTopAll();
	Shader topAll;
};


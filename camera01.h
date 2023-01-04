// camera created by me on febrary of 2022 
// version 0.01
#pragma once

#include "framework.h"

class camera01
{
public:
	glm::vec4 Front;
	glm::vec4 Up;
	glm::vec4 Right; 
	glm::vec3 pos;
	glm::mat4 vmat;
	glm::mat4 dirMat;
	float pitch;
	float yaw;
	camera01();
	void PitchUp();
	void PitchDown();
	void TurnRight();
	void TurnLeft();
	void move(GLuint dir);
	void setView(GLuint dir);

};


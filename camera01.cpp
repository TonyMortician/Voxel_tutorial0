#include "camera01.h"


camera01::camera01()
{
	pitch = 0.087266462599716f;
	yaw = 0.087266462599716f;
	Front = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	dirMat = glm::mat4(1);
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::PitchUp()
{
	dirMat = glm::mat4(1);
	dirMat = glm::rotate(dirMat, pitch, glm::vec3(Right.x, Right.y, Right.z));
	Up = dirMat * Up;
	Front = dirMat * Front;
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::PitchDown()
{
	dirMat = glm::mat4(1);
	dirMat = glm::rotate(dirMat, -pitch, glm::vec3(Right.x, Right.y, Right.z));
	Up = dirMat * Up;
	Front = dirMat * Front;
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::TurnRight()
{
	dirMat = glm::mat4(1);
	dirMat = glm::rotate(dirMat, -yaw, glm::vec3(Up.x, Up.y, Up.z));
	Right = dirMat * Right;
	Front = dirMat * Front;
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::TurnLeft()
{
	dirMat = glm::mat4(1);
	dirMat = glm::rotate(dirMat, yaw, glm::vec3(Up.x, Up.y, Up.z));
	Right = dirMat * Right;
	Front = dirMat * Front;
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::move(GLuint dir)
{
	switch (dir)
	{
	case 0:
		pos += glm::vec3(Front.x*0.25f, Front.y * 0.25f, Front.z * 0.25f);
		break;
	case 1: // back
		pos -= glm::vec3(Front.x * 0.25f, Front.y * 0.25f, Front.z * 0.25f);
		break;
	case 2: // left
		pos -= glm::vec3(Right.x * 0.25f, Right.y * 0.25f, Right.z * 0.25f);
		break;
	case 3: // right
		pos += glm::vec3(Right.x * 0.25f, Right.y * 0.25f, Right.z * 0.25f);
		break;
	case 4: // up
		pos += glm::vec3(Up.x * 0.25f, Up.y * 0.25f, Up.z * 0.25f);
		break;
	case 5: // down
		pos -= glm::vec3(Up.x * 0.25f, Up.y * 0.25f, Up.z * 0.25f);
		break;
	}
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

void camera01::setView(GLuint dir)
{
	switch (dir)
	{
	case 1:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		pos = glm::vec3(-5.0f, 0.0f, -10.0f);
		Right = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
		break;
	case 2:
		Up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		Front = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
		pos = glm::vec3(0.0f, 0.0f, 0.0f);
		Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);		
		break;
	case 3:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		pos = glm::vec3(5.0f, 0.0f, -10.0f);
		Right = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		break;
	case 4:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, -5.0f, -10.0f);
		Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 5:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, 5.0f, -10.0f);
		Right = glm::vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		break;
	
	
	case 10:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, -2.0f, -10.0f);
		Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 11:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, -1.0f, -10.0f);
		Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 12:
		Up = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Front = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		pos = glm::vec3(0.0f, -3.0f, -10.0f);
		Right = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		break;
	}
	dirMat = glm::mat4(1);
	vmat = glm::lookAt(pos, pos + glm::vec3(Front.x, Front.y, Front.z), glm::vec3(Up.x, Up.y, Up.z));
}

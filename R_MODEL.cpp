#include "R_MODEL.h"


void R_MODEL::init(RES_MANAGER* res)
{
	resManager = res;	
	modelShader.Load_shader("simpleModel");
	glGenVertexArrays(1, &vao);
	
	model = glm::mat4(1);
	perspective = glm::perspective(glm::radians(45.0f), float(1440) / float(900), 1.0f, 100.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
}

void R_MODEL::renderModel()
{
	glUseProgram(modelShader.ID);
	glBindImageTexture(0, resManager->modelTexture, 0, GL_TRUE, 0, GL_READ_ONLY, GL_R32UI);	
	glBindImageTexture(1, resManager->palleteTexture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8);
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "mvm"), 1, GL_FALSE, glm::value_ptr(perspective * cam2.vmat * model));
	glUniform3fv(glGetUniformLocation(modelShader.ID, "tSize"), 1, glm::value_ptr(resManager->modelTSize));
	glUniform3fv(glGetUniformLocation(modelShader.ID, "mSize"), 1, glm::value_ptr(resManager->modelMSize));	
	glUniform1f(glGetUniformLocation(modelShader.ID, "pSize"), resManager->pSize);
	glBindVertexArray(vao);	
	glDrawArrays(GL_POINTS, 0, resManager->pNum);	
	glUseProgram(0);
}

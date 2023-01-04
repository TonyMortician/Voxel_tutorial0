#pragma once
#include "framework.h"


struct u_form
{
	char type;
	std::string name;
	unsigned int location;
};



class Shader
{
public:
	std::string name;
	std::string fileName;
	unsigned int ID;
	std::vector<u_form> uniforms;

	std::vector<int> shaders;
	std::ofstream  logger;
	unsigned int Load_shader(std::string filename);
	void check();
	void deleteShader();
	void reloadShader();
	unsigned int compile_subroutine(std::string filename, unsigned int routine_type);
};


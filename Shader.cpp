#include "Shader.h"

unsigned int Shader::Load_shader(std::string filename)
{
	fileName = filename;
	std::ifstream header;
	int u_num(0), f_num(0);	
	shaders.clear();
	logger.open(std::string(std::string("ShaderLogs\\")+filename + std::string("\\") + filename).c_str(), std::ios::out);
	header.open(std::string(std::string("Shaders\\") + filename + std::string("\\") + filename).c_str(), std::ios_base::in);
	if (header.is_open())
	{
		header >> name >> u_num >> f_num;
		std::vector<std::string> filenames;
		std::string temp_name;
		unsigned int routine_type;
		std::vector<unsigned int> subrotines;
		while (f_num--)
		{
			header >> temp_name >> routine_type;
			temp_name = std::string("Shaders\\" + filename + "\\") + temp_name;
			subrotines.push_back(compile_subroutine(temp_name, routine_type));
		}
		ID = glCreateProgram();
		for (unsigned int r : subrotines)
		{
			glAttachShader(ID, r);
		}
		glLinkProgram(ID);
		int res(0);
		glGetProgramiv(ID, GL_LINK_STATUS, &res);
		if (!res)
		{
			char report[1024];
			glGetProgramInfoLog(ID, 1024, NULL, report);
			logger << "[ERROR]::" << "[LINKING FAILED]::" << "[" << filename.c_str() << "]" << ":::" << report << " <<<<" << std::endl;
			return 1;
		}
		else
		{
			logger << "<SUCCESS>::<SHADER COMPILED>::" << "[" << filename.c_str() << "]" << std::endl;
		}
		u_form temp_uform;
		while (u_num--)
		{
			header >> temp_uform.name >> temp_uform.type;
			uniforms.push_back(temp_uform);
		}
		logger << "Uniforms num: " << uniforms.size() << std::endl;
	}
	else
	{
		logger << "Failed to open file." << std::endl;	
		return 1;
	}
	logger.close();
	return 0;
}

void Shader::check()
{
	
}

unsigned int Shader::compile_subroutine(std::string f_name, unsigned int routine_type)
{
	std::stringstream code;
	std::string code_source;
	unsigned int routine(0);
	std::ifstream source;	
	source.open(f_name.c_str(), std::ios_base::in);
	if (source.is_open())
	{
		code << source.rdbuf();
		source.close();
		routine = glCreateShader(routine_type);
		code_source = code.str();
		const char* c_string = code_source.c_str();
		glShaderSource(routine, 1, &c_string, NULL);
		glCompileShader(routine);
		int res(0);
		glGetShaderiv(routine, GL_COMPILE_STATUS, &res);
		char report[1024];
		if (res)
		{
			logger << "<SUCCESS>::<ROUTINE COMPILED>::" << "[" << f_name.c_str() << "]" << std::endl;
			shaders.push_back(routine);
			return routine;
		}
		else
		{
			glGetShaderInfoLog(routine, 1024, NULL, report);
			logger << "[ERROR]::" << "[" << f_name.c_str() << "]" << "::" << " " << report << " <<<<" << std::endl;			
		}
	}
	else
	{
		logger << "[ERROR]:: " << "SUBROUTINE NOT FOUND!\n";		
	}
}

void Shader::deleteShader()
{
	for (int x : shaders)
	{
		glDeleteShader(x);
	}
	glDeleteProgram(ID);
}

void Shader::reloadShader()
{
	deleteShader();
	Load_shader(fileName);
}
#include "S_MODEL.h"

void S_MODEL::init(RES_MANAGER *res)
{
	resManager = res;
}

void S_MODEL::createModel()
{
	std::ifstream source;
	source.open(std::wstring(L"MODELS\\model.data").c_str(), std::ios_base::in);

	GLuint size;
	GLuint* data;

	if (source.is_open())
	{
		source >> tSize.x >> tSize.y >> tSize.z;
		source >> mSize.x >> mSize.y >> mSize.z;

		size = tSize.x * tSize.y * tSize.z;
		data = new GLuint[size];

		for (int i = 0; i < size; i++)
		{
			source >> data[i];
		}
		source.close();

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_3D, texture);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage3D(GL_TEXTURE_3D, 0, GL_R32UI, tSize.x, tSize.y, tSize.z, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, data);
		glBindTexture(GL_TEXTURE_3D, 0);

		delete[] data;		
	}
}


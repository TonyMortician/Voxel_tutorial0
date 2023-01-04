#include "PALLETE.h"

void PALLETE::init(RES_MANAGER* res)
{
	resManager = res;
	loadPalleteText();
}

void PALLETE::loadPalleteText()
{
	int width, height, nrChannels;
	unsigned char* data = stbi_load("pallete.png", &width, &height, &nrChannels, 0);
	glGenTextures(1, &palleteText);
	glBindTexture(GL_TEXTURE_2D, palleteText);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

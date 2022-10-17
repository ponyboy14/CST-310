#include "Texture.h"
#include "stb_image.h"
//#include <cassert.h>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	
	//loads the image data
	unsigned char* imageData = stbi_load(fileName.c_str(),&width, &height, &numComponents, 4);
	
	
	if(imageData == NULL)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
	
	
	//generates texture space
	glGenTextures(1, &m_texture);
	
	//Binds a 2D texture to the space
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	//Controls texture wrapping 
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	
	
	//Determines how it handles extrapulating pixels 
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
	
	//glTexImage2D();
	
	
	//Frees the image data
	stbi_image_free(imageData);
}


Texture::~Texture()
{

	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{		

	//assert(unit >= 0 && unit <= 31);	
	
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
			
		
		
		
}		
		
		


#include "Texture.h"
#include <iostream>
#include "stb_image.h"//texture load and creation

using namespace std;

Texture::Texture()//default constructor--> generate and bind a defualt GL_TEXTURE_2D
{
	//set memebr data
	this->target = GL_TEXTURE_2D;
	//generate texture

	glGenTextures(1, &this->texture);//generate 1 texture stored in an unsigned int (this->texture)
	glBindTexture(this->target, this->texture);//bind this->texture to be a GL_TEXTURE_2D
}

Texture::Texture(GLenum textureTarget)//constructor
{
	//set member data
	this->target = textureTarget;//set the texture target (GL_TEXTURE_2D)
	
	//generate texture

	glGenTextures(1, &this->texture);//generate 1 texture stored in an unsigned int (this->texture)
	glBindTexture(this->target, this->texture);//bind this->texture to be this->target texture (for example a GL_TEXTURE_2D)
	   
}

void Texture::bind()
{
	glBindTexture(this->target, this->texture);//bind this->texture to be this->target texture (for example a GL_TEXTURE_2D)

}

void Texture::texWrapping(GLenum texCoordinate, GLint wrapMode)//set the texture wrapping parameter, where texture target is related to target of texture (GL_TEXTURE2D), textCoordinate indicates the texture coordinate we want to warp (s or t texture coordinate), warpMode is the wtrapping mode we want to applicate (GL_REPEAT)
{
	glTexParameteri(this->target, texCoordinate, wrapMode);
		
}

void Texture::texFiltering(GLenum glFilterOperation, GLint textFilter)//set texture filtering parameter, where glFilterOperation indicates magnifying or minifying operation (GL_MIN_FILTER), textFilter is texture filtering (GL_NEAREST o GL_LINEAR)
{
	glTexParameteri(this->target, glFilterOperation, textFilter);
	
}

void Texture::load(const char* filenamePath, GLint mipmapLevel)//load and create texture
{
	this->filename = filenamePath;

	int width, height, nrChannels;
	
	unsigned char* data = stbi_load(filenamePath, &width, &height, &nrChannels, 0);//load texture using stb_image.h library

	if (data)//if texture has been loaded
	{
		GLenum format;
		if (nrChannels == 1)
		{
			format = GL_RED;
		}

		if (nrChannels == 3)
		{
			format = GL_RGB;
		}

		if (nrChannels == 4)
		{
			format = GL_RGBA;
		}
		//create Texture. NOW TEXTURE OBJECT HAS THE TEXTURE IMAGE ATTACHED TO IT!
		//bind();//bind texture
		glTexImage2D(this->target, mipmapLevel, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); // check out page 63 of the book
		glGenerateMipmap(this->target); //generate Mipmaps
		cout << "TEXTURE AND MIPMAPS LOADED!\n" << endl;
	}
	else//if texture has not been loaded
	{
		cout << "ERROR::FAILED_TO_LOAD_TEXTURE\n" << endl;
	}


	//free the memory once the texture is generated
	stbi_image_free(data);


}




unsigned int Texture::getTexture()//return this texture object
{
	return this->texture;
}

GLenum Texture::getTexTarget()//return texture target (GL_TEXTURE_2D)
{
	return this->target;
}

//CUBEMAP SKYBOX TEXTURE

void Texture::getSkyboxVertices(float* f)//return skybox vertices to create a cubemap skybox
{
	float skyboxVertex[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	for (int i = 0; i < 108; i++)
	{
		f[i] = skyboxVertex[i];
	}
	

	
}

void Texture::cubeMapLoader(vector<std::string> faces, GLint mipmapLevel)//load CubeMap that we use as a skebox
{
	int width, height, nrComponents;

	for (int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
		
		if (data)
		{
			

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mipmapLevel, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			cout << "\nCubemap Loaded!" << endl;
		}
		else
		{
			cout << "Cubemap texture failed to load at path: " << faces[i] << endl;
		}

		stbi_image_free(data);
	}

	
}

Texture::~Texture()//destructor
{
	cout << "Texture ";
	if (this->target != GL_TEXTURE_CUBE_MAP)
	{
		for (int i = 0; this->filename[i] != '\0'; i++)
		{
			cout << this->filename[i];
		}
	}
	
	cout << " deleted!\n" << endl;
}









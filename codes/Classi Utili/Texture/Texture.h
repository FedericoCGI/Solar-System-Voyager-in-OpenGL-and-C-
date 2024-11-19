#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Texture
{
	private:
		unsigned int texture;
		const char* filename;
		GLenum target;//texture target (1D, 2D, 3D)
		 

	public:
		
		Texture(GLenum);
		Texture();
		void texWrapping(GLenum, GLint);
		void texFiltering(GLenum, GLint);
		void load(const char *, GLint);
		void bind();
		unsigned int getTexture();
		GLenum getTexTarget();
		//cubemap skybox texture
		void getSkyboxVertices(float *);
		void cubeMapLoader(std::vector<std::string>, GLint);
		~Texture();

};



#endif // !TEXTURE_H


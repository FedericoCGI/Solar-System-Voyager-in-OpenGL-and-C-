#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Shader
{
	private:
		int shader;
		GLenum sType;
		

	public:
		
		Shader(const char*, GLenum);
		int getShader();
		~Shader();
};



#endif

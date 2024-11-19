#ifndef SHADERLINKER_H
#define SHADERLINKER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <string.h>
#include "Shader.h"

class ShaderLinker
{
	private:
		unsigned int shaderProgram;

	public:
		ShaderLinker(int , int);
		unsigned int getShaderProgram();
		void uniformGetLocAndSendMatToShader(const char*, glm::mat4&);
		void uniformGetLocAndSetText(const char*, float);
		~ShaderLinker();
};




#endif


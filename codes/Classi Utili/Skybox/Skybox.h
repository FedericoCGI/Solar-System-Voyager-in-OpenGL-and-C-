#ifndef SKYBOX_H
#define SKYBOX_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Texture/stb_image.h"
#include "Texture/Texture.h"
#include "Shader/Shader.h"
#include "Shader/ShaderLinker.h"

class Skybox
{
	private:
		Texture* cubeMap;
		std::vector<std::string> faces;
		float skyboxVertices[108];
		unsigned int skyboxVBO;

	public:
		unsigned int skyboxVAO;
		Skybox(Texture*, std::vector<std::string>);
		void setSkybox();
		void drawSB(ShaderLinker*);
		~Skybox();

};

#endif


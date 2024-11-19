#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Mesh/Mesh.h>
#include <Texture/stb_image.h>
#include <Texture/Texture.h>
#include <Shader/Shader.h>
#include <Shader/ShaderLinker.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>




class Model
{
	private:
		
		//functions
		void loadModel(std::string const &path);
		void processNode(aiNode*, const aiScene*);
		Mesh processMesh(aiMesh*, const aiScene*);
		vector<Textures> loadMaterialTexture(aiMaterial*, aiTextureType, std::string);

	public:
		//model data
		vector<Textures> texture_loaded;
		vector<Mesh> meshes;
		std::string directory;
		bool gammaCorrection;
		string  path;
		

		//functions
		Model(string const &path, bool gamma= false);
		void Draw(ShaderLinker*);
		~Model();

};



#endif


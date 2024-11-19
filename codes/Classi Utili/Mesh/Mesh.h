#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <Shader/Shader.h>
#include <Shader/ShaderLinker.h>

#include <My Algebra/MyAlgebra.h>

#include <string>
#include <iostream>
#include <vector>



using namespace glm;
using namespace std;

//structure settings

//Vertex structure is used to index aech of the vertex attribute
struct Vertex 
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
	vec3 Bitangent;

};

//Texture structure is used to organize texture data
struct Textures
{
	unsigned int id;
	string type;
	string path;
};

//define Mesh class

class Mesh
{
	private:
		//render data
		unsigned int VBO, EBO;

		//functions
		void setupMesh();

	public:
		//mesh data
		vector<Vertex> vertices;
		vector <unsigned int> indices;
		vector<Textures> textures;
		unsigned int VAO;

		//functions
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Textures> textures);
		void draw(ShaderLinker* shaderProgram);
		~Mesh();


};

#endif

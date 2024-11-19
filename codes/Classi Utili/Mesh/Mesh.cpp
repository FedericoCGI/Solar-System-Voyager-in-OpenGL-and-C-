#include "Mesh.h"

using namespace std;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Textures> textures)//constructor
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::setupMesh()//set the mesh up, setting the appropriate buffers, specify the vertex shader and vertex attribute pointers
{

	//0. create a Vertex Array Object (VAO) first
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(this->VAO);//bind VAO to be a vertex array buffer

	//1. create a Vertex Buffer Object (VBO)
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO);//bind VBO to be a GL_ARRAY_BUFFER
	//2. copy vertices in the vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//3. create an Element Buffer Object (EBO)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);//bind EBO to be a GL_ELEMEN_ARRAY_BUFFER
	//4. copy indices in the elements buffer object
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//5. set the vertex attribute pointer

	//vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);//location-size of vertex attribute for vertex postion- tipe of data for vertex position- not normalize data- stride- offset
	glEnableVertexAttribArray(0); //vertex position are at location 0

	//vertex normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));//for stride and offset we use the fact that structures has a  sequencial memory in C++
	glEnableVertexAttribArray(1); //normals are at location 1

	// vertex texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));//offsetof(structure, member) returns the byte offset of that variable from the start of the struct
	glEnableVertexAttribArray(2); //texture coordinates are at location 2

	//vrtex tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(3);// tangent are at location 3

	//vertex bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
	glEnableVertexAttribArray(4); //bitangent are at location 4

	glBindVertexArray(0);//unbind VAO in order to not modify it with another VAO calls

}


//RENDERING
void Mesh::draw(ShaderLinker* shaderProgram)//rendering 
{
	//texture management
	unsigned int diffuseNr = 1;//diffusive texture
	unsigned int specularNr = 1; //specular texture
	unsigned int normaNr = 1;//normal texture
	unsigned int heightNr = 1; // height texture

	//get uniform texture location, set the texture and bind it
	for (int i = 0; i < textures.size(); i++)
	{
		//in order to use multiple texture, we have to bind all needed texture to the corresponding texture unit

		glActiveTexture(GL_TEXTURE0 + i);//activate proper texture unit 
		string name = textures[i].type;

		//set texture name
		if (name == "texture_diffuse")
		{
			name = name + to_string(diffuseNr++);
			
		}

		if (name == "texture_specular")
		{
			name = name + to_string(specularNr++);
			
		}

		if (name == "texture_normal")
		{
			name = name + to_string(normaNr++);
			
		}

		if (name == "texture_height")
		{
			name = name + to_string(heightNr++);
			
		}

		//get the uniform texture and set texture for shaders
		shaderProgram->uniformGetLocAndSetText((name).c_str(), i); //(thanks to gluniform1f function defined in ShaderLinker::unifromGetLocAndSetText) we make sure each uniform sampler corresponds to the proper texture unit
		//we added material to the resulting uniform because we usually store textures in a material structure
		glBindTexture(GL_TEXTURE_2D, textures[i].id);//bind the texture

		//with this procedure we can attach multiple texture to a single model 
	}

	//draw this mesh
	glBindVertexArray(this->VAO);//bind the VAO related to this mesh object
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//indices.size() unsigned int indices to draw
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}




/*const char* Mesh::string_toChar(string s)//turn a string into a const char*
{
	const char* c;
	c = s.c_str();
	return c;
}*/


Mesh::~Mesh()//destructor
{
	std::cout << "\nMesh deleted!" << std::endl;
}
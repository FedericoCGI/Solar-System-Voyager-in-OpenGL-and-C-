#include "Skybox.h"
#include <iostream>

using namespace std;

Skybox::Skybox(Texture* cm, vector<string> f)//constructor
{
	this->cubeMap = cm;
	this->faces = f;

	setSkybox();
}

void Skybox::setSkybox()//set skybox 
{
	//set Skybox Vertices
	float skyboxVertices[108]; //6x6x3=108 vertices
	this->cubeMap->getSkyboxVertices(skyboxVertices);

	//SKYBOX VERTEX ATTRIBUTE

	//0. create first a Vertex Array Object (VAO)
	glGenVertexArrays(1, &this->skyboxVAO);
	glBindVertexArray(this->skyboxVAO);//bind skyboxVAO to be a Vertex Array

	//1. create a Vertex Buffer Object (VBO)
	glGenBuffers(1, &this->skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->skyboxVBO);//bind skyVBO to be GL_ARRAY_BUFFER

	//2. copy skyboxVertices into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	//set vertex attribute pointer--> skybox vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//skybox vertex position are at location 0

	//Skybox Configuration

	//load cubemap
	this->cubeMap->cubeMapLoader(this->faces, 0);

	//cubemap texture wrap and filter settings
	cubeMap->texWrapping(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	cubeMap->texWrapping(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	cubeMap->texWrapping(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	cubeMap->texFiltering(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	cubeMap->texFiltering(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Skybox::drawSB(ShaderLinker* skyboxProgram)//draw skybox as scene background
{
	glDepthFunc(GL_LEQUAL);
	glUseProgram(skyboxProgram->getShaderProgram());
	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);//draw 36 vertices
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

Skybox::~Skybox()//destructor
{
	cout << "\nSkybox destroyed!" << endl;
}
//this class handles shaders linking 

#include "ShaderLinker.h"
#include <iostream>
#include <string>
#include <string.h>


using namespace std;

ShaderLinker::ShaderLinker(int vertexShader, int fragmentShader)//constructor
{
	this->shaderProgram = glCreateProgram();//create a shader program

	//attach vertex shader and fragment shader to the shader program
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	

	//link shader program to them
	glLinkProgram(this->shaderProgram);

	//checking for linking errors
	int success;
	char infoLog[512];

	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);//linking was successfull
	if (!success) //linking was not successfull
	{
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::LINKING_FAILED!\n" << endl;
	}
	else
	{
		cout << "SHADERS LINKING SUCCESSFULL!\n" << endl;
	}

	
		

}

unsigned int ShaderLinker::getShaderProgram()//return shader program
{
	return this->shaderProgram;
}

void ShaderLinker::uniformGetLocAndSendMatToShader(const char* unvar, glm::mat4& m)//get matrix uniform location and send data matrix to the shaders
{
	//query for uniform variable unvar location
	unsigned int location = glGetUniformLocation(this->shaderProgram, unvar);

	//set matrix and send matrix data to the shaders
	glad_glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m));
}

void ShaderLinker::uniformGetLocAndSetText(const char* unvar, float f)//get texture uniform location and set the texture for shaders
{
	//query for uniform variable unvar location
	unsigned int location = glGetUniformLocation(this->shaderProgram, unvar);
	//set texture for the shaders
	glUniform1f(location, f);
}



ShaderLinker::~ShaderLinker()//destructor
{
	cout << "Shader Linker removed!\n" << endl;
}



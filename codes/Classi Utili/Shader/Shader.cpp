//create a  shader reading a file glsl, and create a VERTEX_SHADER or a FRAGMENT_SHADER depending on the shaderType given

#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Shader::Shader(const char* shaderPath, GLenum shaderType)//constructor
{
    this->sType = shaderType;

    // 1. retrieve the vertex source code from filePath
    std::string shaderCode;
    std::ifstream ShaderFile;
    

    // ensure ifstream objects can throw exceptions:
    ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    

    try
    {
        // open files
        ShaderFile.open(shaderPath);

        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();

        // close file handlers
        ShaderFile.close();

        // convert stream into string
        shaderCode = ShaderStream.str();

        

    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* shaderSource = shaderCode.c_str();



    //build and compile vertex shader program
    this->shader = glCreateShader(shaderType);//create a  shader with defined type (or Vertex or Fragment)
    glShaderSource(this->shader, 1, &shaderSource, NULL);//build a vertex shader program
    glCompileShader(shader);//compile vertex shader program

    //checking compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);//check if compilation was successfull
    if (!success)//if compilation was not successfull
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::";
        if (this->sType == GL_VERTEX_SHADER)
        {
            cout << "VERTEX";
        }

        if (this->sType == GL_FRAGMENT_SHADER)
        {
            cout << "FRAGMENT";
        }

        cout <<"::COMPILATION_FAILDE!\n" << endl;
    }
    else
    {
        if (this->sType == GL_VERTEX_SHADER)
        {
            cout << "VERTEX";
        }

        if (this->sType == GL_FRAGMENT_SHADER)
        {
            cout << "FRAGMENT";
        }
        
        cout << " SHADER COMPILATION SUCCESSFULL\n" << endl;
    }

    // if geometry shader is given, compile geometry shader
    
    

    


}

int Shader::getShader()//return this shader
{
    return this->shader;
}




Shader::~Shader()//destructor
{
    if (this->sType == GL_VERTEX_SHADER)
    {
        cout << "GL_VERTEX";
    }

    if (this->sType == GL_FRAGMENT_SHADER)
    {
        cout << "GL_FRAGMENT";
    }
    
    cout << "_SHADER deleted!\n" << endl;
}

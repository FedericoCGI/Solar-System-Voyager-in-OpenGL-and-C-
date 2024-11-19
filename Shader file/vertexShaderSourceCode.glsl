//GLSL is a shader language
#version 330 core //declaration of the version used: as we are using OpenGl version 3.3 we write version 330. We add core because we are working with OpenGl CORE PROFILE
layout (location=0) in vec3 aPos; //declaration of vertex attribute in the vertex shader. Since each vertex of our triangle has a 3D coordinates, we create e vec3 variable named aPos
layout (location=1) in vec3 aNormal;
layout (location=2) in vec2 aTextCoords;



out vec2 TexCoords;

//declare transformations matrix as uniform
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 planetModel;

void main()
{
	gl_Position=projection * view *  model * planetModel * vec4(aPos,1.0f); //gl_position is a vec4 variable. The 4th parameter of vec4 constructor is aPos.w, where this component is used for perspective division
	
	TexCoords=aTextCoords;
}


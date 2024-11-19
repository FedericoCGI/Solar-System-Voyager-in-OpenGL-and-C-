//GLSL is a shader language
#version 330 core //declaration of the version used: as we are using OpenGl version 3.3 we write version 330. We add core because we are working with OpenGl CORE PROFILE
layout (location=0) in vec3 aPos; //declaration of vertex attribute in the vertex shader. Since each vertex of our triangle has a 3D coordinates, we create e vec3 variable named aPos

void main()
{
	gl_Position=vec4(aPos.x, aPos.y, aPos.z, 1.0); //gl_position is a vec4 variable. The 4th parameter of vec4 constructor is aPos.w, where this component is used for perspective division
}


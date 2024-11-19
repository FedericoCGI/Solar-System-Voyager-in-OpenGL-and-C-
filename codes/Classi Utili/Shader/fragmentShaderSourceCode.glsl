#version 330 core //declare version OPENGL we are using (330) and profile we are working (CORE_PROFILE)
out vec4 FragColor;//fragment shader requires one output variable, a vec4 variable named FragColor

uniform vec4 myColor;//we set this variable in the OpenGl code
void main()
{
	//FragColor=vec4(1.0f,1.0f,0.0f,1.0f); // we pass an RGBA color as vec4 constructor prameters. in GLSL an RGBA color is defined by a set of 4 value between 0.0 and 1.0, where the first 3 value correspond to R,G,B channel, while the last one to ALPHA CHANNEL
	//ALPHA CHANNEL set at 1.0 means that the color choosen is completely opaque

	FragColor=myColor;
}
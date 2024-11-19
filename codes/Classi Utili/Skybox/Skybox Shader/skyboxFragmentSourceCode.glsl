#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;//skybox cubemap texture

void main()
{    
    FragColor = texture(skybox, TexCoords);
}
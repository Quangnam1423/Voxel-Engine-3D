#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform float time;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform MVP
{
	mat4 model;
	mat4 view;
	mat4 projection;
};
uniform vec4 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = texCoords;
}
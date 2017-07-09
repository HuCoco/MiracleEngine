#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform AffineMatrixs
{
	mat4 model;
	mat4 inverseModel;
	mat4 view;
	mat4 projection;
};


void main()
{
    vec4 worldPos = model * vec4(position, 1.0f);
    FragPos = worldPos.xyz; 
    gl_Position = projection * view * worldPos;
    TexCoords = texCoords;
    Normal = mat3(inverseModel) * normal;
  
}
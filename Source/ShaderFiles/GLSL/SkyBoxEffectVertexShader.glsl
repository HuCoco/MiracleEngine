#version 330 core
layout (location = 0) in vec3 position;
out vec3 TexCoords;

uniform SkyBoxMatrixs
{
	mat4 model;
	mat4 view;
	mat4 projection;
};

void main()
{
    vec4 pos = projection * view * model * vec4(position.x,-position.y,position.z, 1.0);  
    gl_Position = pos.xyww;
    TexCoords = vec3(position.x ,position.y , position.z);
}
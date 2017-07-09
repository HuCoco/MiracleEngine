#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 btangent;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;
uniform sampler2D TexNormal;

uniform AffineMatrixs
{
	mat4 model;
	mat4 inverseModel;
	mat4 view;
	mat4 projection;
};

vec3 CalcNormal()
{
	vec3 WorldTangent = normalize((inverseModel * vec4(tangent,0.0)).xyz);
	vec3 WorldNormal = normalize((inverseModel * vec4(normal,0.0)).xyz);
	WorldTangent = normalize(WorldTangent - dot(WorldTangent, WorldNormal) * WorldNormal);
	vec3 WorldBTangent = cross(WorldTangent, WorldNormal);
	//vec3 WorldBTangent = normalize((projection * view * model * vec4(btangent,0.0)).xyz);
	vec3 NormalMap = texture(TexNormal, TexCoords).rgb;
	NormalMap = normalize(NormalMap * 2.0 - 1.0); 
	mat3 TBN = mat3(WorldTangent,WorldBTangent,WorldNormal);
	return normalize(TBN * NormalMap);
}

void main()
{
    vec4 worldPos = model * vec4(position, 1.0f);
    FragPos = worldPos.xyz; 
    gl_Position = projection * view * worldPos;
    TexCoords = texCoords;
    Normal = CalcNormal();
}



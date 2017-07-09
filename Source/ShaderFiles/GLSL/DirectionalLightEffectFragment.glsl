#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D TexDiffuse;
uniform sampler2D TexSpecular;

uniform Material
{
    float Shininess;
};

uniform Camera
{
    vec3 CameraPosition;
};

uniform DirectionalLightBlock
{
	vec3 Direction;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular; 
};

void main()
{
	vec3 ambient = Ambient * vec3(texture(TexDiffuse, TexCoord));

	vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(Direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = Diffuse * diff * vec3(texture(TexDiffuse, TexCoord));

    vec3 viewDir = normalize(CameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Shininess);
    vec3 specular = Specular * spec * vec3(texture(TexSpecular, TexCoord));

    color = vec4(ambient + diffuse + specular, 1.0f);
    //color = vec4(texture(TexDiffuse, TexCoord));
}
#version 330 core

out vec4 color;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform Light
{
	vec4 LightPosition;
    vec4 LightAmbient;
    vec4 LightDiffuse;
    vec4 LightSpecular;
};

uniform Material 
{
	vec4 MaterialAmbient;
    vec4 MaterialDiffuse;
    vec4 MaterialSpecular;    
    float MaterialShininess;
};

uniform vec4 viewPos;

void main()
{
	vec3 a_LightPosition = vec3(LightPosition);
    vec3 a_LightAmbient = vec3(LightAmbient);
    vec3 a_LightDiffuse = vec3(LightDiffuse);
    vec3 a_LightSpecular = vec3(LightSpecular);

	vec3 a_MaterialAmbient = vec3(MaterialAmbient);
    vec3 a_MaterialDiffuse = vec3(MaterialDiffuse);
    vec3 a_MaterialSpecular = vec3(MaterialSpecular);

    vec3 a_viewPos = vec3(viewPos);

    vec3 ambient = a_LightAmbient * vec3(texture(ourTexture1, TexCoord));


    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(a_LightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = a_LightDiffuse * diff * vec3(texture(ourTexture1, TexCoord));


    vec3 viewDir = normalize(a_viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), MaterialShininess);
    vec3 specular = a_LightSpecular * spec * vec3(texture(ourTexture2, TexCoord));


	color = vec4(ambient + diffuse + specular, 1.0f);  
}
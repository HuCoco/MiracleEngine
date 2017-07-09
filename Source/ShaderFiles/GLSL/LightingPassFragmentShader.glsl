#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

#define MAX_NUM_OF_DIRECTIONAL_LIGHTS 1
#define MAX_NUM_OF_POINT_LIGHTS 32
#define MAX_NUM_OF_SPOT_LIGHTS 1

struct DirectionalLightData 
{
    vec3 Direction;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Color;
}; 

struct PointLightData 
{
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Color;
    float ColorAlpha;
    float Constant;
    float Linear;
    float Quadratic;

}; 

struct SpotLightData 
{
    vec3 Direction;
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    vec3 Color;
    float ColorAlpha;
    float Constant;
    float Linear;
    float Quadratic;
    float CutOff;
    float OuterCutOff;
}; 

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform DirectionalLight
{
    DirectionalLightData DirectionalLights[MAX_NUM_OF_DIRECTIONAL_LIGHTS];
};

uniform NumActiveDirectionalLights
{
    int NumDirectionalLights;
};

uniform PointLight
{
    PointLightData PointLights[MAX_NUM_OF_POINT_LIGHTS];
};

uniform NumActivePointLights
{
    int NumPointLights;
};

uniform SpotLight
{
    SpotLightData SpotLights[MAX_NUM_OF_SPOT_LIGHTS];
};

uniform NumActiveSpotLights
{
    int NumSpotLights;
};

uniform Camera
{
    vec3 CameraPosition;
};

vec3 CalcDirectionalLight(vec3 Albedo, float Specular,
     vec3 Normal, DirectionalLightData Light, vec3 ViewDirection);

vec3 CalcPointLight(vec3 FragPos, vec3 Albedo, float Specular,
     vec3 Normal, PointLightData Light, vec3 ViewDirection);

vec3 CalcSpotLight(vec3 FragPos, vec3 Albedo, float Specular,
     vec3 Normal, SpotLightData Light, vec3 ViewDirection);

void main()
{             
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Albedo  = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    vec3 ViewDirection = normalize(CameraPosition - FragPos);
    vec3 result;

    for(int i = 0; i < NumDirectionalLights; i++)
    {
        result += CalcDirectionalLight(Albedo, Specular, Normal, DirectionalLights[i], ViewDirection);
    }

    for(int i = 0; i < NumPointLights; i++)
    {
        result += CalcPointLight(FragPos, Albedo, Specular, Normal, PointLights[i], ViewDirection);
    }

    for(int i = 0; i < NumSpotLights; i++)
    {
        result += CalcSpotLight(FragPos, Albedo, Specular, Normal, SpotLights[i], ViewDirection);
    }

    FragColor = vec4(result,1.0);
}


vec3 CalcDirectionalLight(vec3 Albedo, float Specular,
     vec3 Normal, DirectionalLightData Light, vec3 ViewDirection)
{
    vec3 LightDirection = normalize(-Light.Direction);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    vec3 HalfWayDirection = normalize(  + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 32.0);

    vec3 ambient = Light.Ambient * Albedo;
    vec3 diffuse = Light.Diffuse * Diff * Albedo;
    vec3 specular = Light.Specular * Spec * Specular;

    return (ambient + diffuse + specular) * Light.Color;
}

vec3 CalcPointLight(vec3 FragPos, vec3 Albedo, float Specular,
     vec3 Normal, PointLightData Light, vec3 ViewDirection)
{
    vec3 LightDirection = normalize(Light.Position - FragPos);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    vec3 HalfWayDirection = normalize(LightDirection + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 32.0);

    vec3 ambient = Light.Ambient * Albedo;
    vec3 diffuse = Light.Diffuse * Diff * Albedo;
    vec3 specular = Light.Specular * Spec * Specular;

    float Distance = length(Light.Position - FragPos);
    float Attenuation = 1.0 / (Light.Constant + Light.Linear * Distance + Light.Quadratic * (Distance * Distance));  
    ambient *= Attenuation;
    diffuse *= Attenuation;
    specular *= Attenuation;

    return (ambient + diffuse + specular) * Light.Color;
}

vec3 CalcSpotLight(vec3 FragPos, vec3 Albedo, float Specular,
     vec3 Normal, SpotLightData Light, vec3 ViewDirection)
{
    vec3 LightDirection = normalize(Light.Position - FragPos);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    vec3 HalfWayDirection = normalize(LightDirection + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 32.0);

    vec3 ambient = Light.Ambient * Albedo;
    vec3 diffuse = Light.Diffuse * Diff * Albedo;
    vec3 specular = Light.Specular * Spec * Specular;

    float Theta = dot(LightDirection, normalize(-Light.Direction));
    float Epsilon = Light.CutOff - Light.OuterCutOff;
    float Intensity = clamp((Theta - Light.OuterCutOff) / Epsilon, 0.0, 1.0);
    diffuse *= Intensity;
    specular *= Intensity;

    float Distance = length(Light.Position - FragPos);
    float Attenuation = 1.0 / (Light.Constant + Light.Linear * Distance + Light.Quadratic * (Distance * Distance));  
    ambient *= Attenuation;
    diffuse *= Attenuation;
    specular *= Attenuation;

    return (ambient + diffuse + specular) * Light.Color;;
}


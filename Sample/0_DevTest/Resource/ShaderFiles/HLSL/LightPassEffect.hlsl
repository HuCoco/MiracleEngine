Texture2D gPosition : register( t0 );
Texture2D gNormal : register( t1 );
Texture2D gAlbedoSpec : register( t2 );
SamplerState samLinear : register( s0 );

#define MAX_NUM_OF_DIRECTIONAL_LIGHTS 1
#define MAX_NUM_OF_POINT_LIGHTS 32
#define MAX_NUM_OF_SPOT_LIGHTS 1

struct DirectionalLightData 
{
    float3 Direction;
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
    float3 Color;
}; 

struct PointLightData 
{
    float3 Position;
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
    float3 Color;
    float ColorAlpha;
    float Constant;
    float Linear;
    float Quadratic;

}; 

struct SpotLightData 
{
    float3 Direction;
    float3 Position;
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
    float3 Color;
    float ColorAlpha;
    float Constant;
    float Linear;
    float Quadratic;
    float CutOff;
    float OuterCutOff;
}; 


cbuffer DirectionalLight : register ( b0 )
{
    DirectionalLightData DirectionalLights[MAX_NUM_OF_DIRECTIONAL_LIGHTS];
};

cbuffer NumActiveDirectionalLights : register ( b1 )
{
    int NumDirectionalLights;
};

cbuffer PointLight : register ( b2 )
{
    PointLightData PointLights[MAX_NUM_OF_POINT_LIGHTS];
};

cbuffer NumActivePointLights : register ( b3 )
{
    int NumPointLights;
};

cbuffer SpotLight : register ( b4 )
{
    SpotLightData SpotLights[MAX_NUM_OF_SPOT_LIGHTS];
};

cbuffer NumActiveSpotLights : register ( b5 )
{
    int NumSpotLights;
};

cbuffer Camera : register ( b6 )
{
    float3 CameraPosition;
};



struct VS_INPUT
{	
    float4 Pos : POSITION;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float3 CalcDirectionalLight(float3 Albedo, float Specular,
     float3 Normal, DirectionalLightData Light, float3 ViewDirection);

float3 CalcPointLight(float3 FragPos, float3 Albedo, float Specular,
     float3 Normal, PointLightData Light, float3 ViewDirection);

float3 CalcSpotLight(float3 FragPos, float3 Albedo, float Specular,
     float3 Normal, SpotLightData Light, float3 ViewDirection);

PS_INPUT VS_Main( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = input.Pos;
	output.Tex.x = input.Tex.x;
	output.Tex.y = 1.0 - input.Tex.y;
	return output;
}

float4 PS_Main( PS_INPUT input) : SV_Target
{
	float3 FragPos = (float3)gPosition.Sample( samLinear, input.Tex );
	float3 Normal = (float3)gNormal.Sample( samLinear, input.Tex );
	float3 Albedo = (float3)gAlbedoSpec.Sample( samLinear, input.Tex );
	float Specular = gAlbedoSpec.Sample( samLinear, input.Tex ).a;

    float3 ViewDirection = normalize(CameraPosition - FragPos);
    float3 result;

	for(int i = 0; i < NumDirectionalLights; i++)
    {
        result += CalcDirectionalLight(Albedo, Specular, Normal, DirectionalLights[i], ViewDirection);
    }

    for(int j = 0; j < NumPointLights; j++)
    {
        result += CalcPointLight(FragPos, Albedo, Specular, Normal, PointLights[j], ViewDirection);
    }

    for(int k = 0; k < NumSpotLights; k++)
    {
        result += CalcSpotLight(FragPos, Albedo, Specular, Normal, SpotLights[k], ViewDirection);
    }

    return float4(result,1.0);
}

float3 CalcDirectionalLight(float3 Albedo, float Specular,
     float3 Normal, DirectionalLightData Light, float3 ViewDirection)
{
    float3 LightDirection = normalize(-Light.Direction);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    float3 HalfWayDirection = normalize(  + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 68.0);

    float3 ambient = Light.Ambient * Albedo;
    float3 diffuse = Light.Diffuse * Diff * Albedo;
    float3 specular = Light.Specular * Spec * Specular;

    return (ambient + diffuse + specular) * Light.Color;
}

float3 CalcPointLight(float3 FragPos, float3 Albedo, float Specular,
     float3 Normal, PointLightData Light, float3 ViewDirection)
{
    float3 LightDirection = normalize(Light.Position - FragPos);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    float3 HalfWayDirection = normalize(LightDirection + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 68.0);

    float3 ambient = Light.Ambient * Albedo;
    float3 diffuse = Light.Diffuse * Diff * Albedo;
    float3 specular = Light.Specular * Spec * Specular;

    float Distance = length(Light.Position - FragPos);
    float Attenuation = 1.0 / (Light.Constant + Light.Linear * Distance + Light.Quadratic * (Distance * Distance));  
    ambient *= Attenuation;
    diffuse *= Attenuation;
    specular *= Attenuation;

    return (ambient + diffuse + specular) * Light.Color;;
}

float3 CalcSpotLight(float3 FragPos, float3 Albedo, float Specular,
     float3 Normal, SpotLightData Light, float3 ViewDirection)
{
    float3 LightDirection = normalize(Light.Position - FragPos);

    float Diff = max(dot(Normal, LightDirection), 0.0);

    float3 HalfWayDirection = normalize(LightDirection + ViewDirection);
    float Spec = pow(max(dot(Normal, HalfWayDirection), 0.0), 68.0);

    float3 ambient = Light.Ambient * Albedo;
    float3 diffuse = Light.Diffuse * Diff * Albedo;
    float3 specular = Light.Specular * Spec * Specular;

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

    return (ambient + diffuse + specular);
}


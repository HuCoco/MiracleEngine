Texture2D TexDiffuse : register( t0 );
Texture2D TexSpecular : register( t1 );
SamplerState samLinear : register( s0 );


cbuffer AffineMatrixs : register ( b0 )
{
	float4x4 Model;
	float4x4 InverseModel;
	float4x4 View;
	float4x4 Projection;
}

cbuffer Material : register ( b1 )
{
    float Shininess;
};

cbuffer Camera : register ( b2 )
{
    float3 CameraPosition;
};

cbuffer DirectionalLightBlock : register ( b3 )
{
	float3 Direction;
	float3 Ambient;
	float3 Diffuse;
	float3 Specular; 
};

struct VS_INPUT
{	
    float4 Pos : POSITION;
    float3 Nor : NORMAL;
    float2 Tex : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float3 Nor : NORMAL;
    float2 Tex : TEXCOORD0;
    float4 PosW : POSITION;
};


PS_INPUT VS_Main( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, Model );
    output.PosW = mul( input.Pos, Model );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Nor = mul( input.Nor , (float3x3)Model);
    output.Tex = input.Tex;

    return output;
}

float4 PS_Main( PS_INPUT input) : SV_Target
{

	float3 ambient = Ambient * (float3)TexDiffuse.Sample( samLinear, input.Tex );

    float3 norm = normalize(input.Nor);
    float3 lightDir = normalize(Direction);
    float diff = max(dot(norm, lightDir), 0.0);
    float3 diffuse = Diffuse * diff * (float3)TexDiffuse.Sample( samLinear, input.Tex);

   	float3 viewDir = normalize(CameraPosition - (float3)input.PosW);
    float3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Shininess);
    float3 specular = Specular * spec * (float3)TexSpecular.Sample( samLinear, input.Tex);

    float4 result = float4(ambient + diffuse + specular,1.0f);

	return result;
}
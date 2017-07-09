
Texture2D TexDiffuse : register( t0 );
Texture2D TexSpecular : register( t1 );
SamplerState samLinear : register( s0 );

cbuffer AffineMatrixs : register ( b0 )
{
	float4x4 Model;
	float4x4 InverseModel;
	float4x4 View;
	float4x4 Projection;
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

struct PS_OUTPUT
{
	float4 gPosition : SV_Target0;
	float4 gNormal : SV_Target1;
	float4 gAlbedoSpec : SV_Target2; 
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

PS_OUTPUT PS_Main( PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	output.gPosition = input.PosW;
	output.gPosition.w = 1.0f;
	output.gNormal = float4(normalize(input.Nor),1.0f);
	float3 Albedo = (float3)TexDiffuse.Sample( samLinear, input.Tex );
	float Spec = (TexSpecular.Sample( samLinear, input.Tex )).r;
	output.gAlbedoSpec = float4(Albedo,Spec);

	return output;
}
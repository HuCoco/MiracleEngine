TextureCube TexSkyBox;
SamplerState SkyBoxSampler;

cbuffer SkyBoxMatrixs : register ( b0 )
{
	float4x4 model;
	float4x4 view;
	float4x4 projection;
};

struct VS_INPUT
{	
    float4 Pos : POSITION;
};

struct PS_INPUT
{	
	float4 Pos : SV_POSITION;
    float3 TexCoords : POSITION;
};

PS_INPUT VS_Main( VS_INPUT input )
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul( input.Pos, model );
    output.Pos = mul( output.Pos, view );
    output.Pos = mul( output.Pos, projection );
    output.Pos = output.Pos.xyww;
    output.TexCoords = float3(input.Pos.x ,-input.Pos.y , input.Pos.z);
    return output;
}

float4 PS_Main( PS_INPUT input ) : SV_Target
{
	return TexSkyBox.Sample(SkyBoxSampler,input.TexCoords);
}
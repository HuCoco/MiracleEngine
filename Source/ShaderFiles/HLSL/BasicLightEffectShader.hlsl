
Texture2D txDiffuse : register( t0 );
Texture2D txSpecular : register( t1 );
SamplerState samLinear : register( s0 );

cbuffer MVP : register ( b0 )
{
	float4x4 World;
    float4x4 View;
    float4x4 Projection;
    float4x4 NormalWorld;
};

cbuffer Light : register ( b1 )
{
	float4 LightPosition;
    float4 LightAmbient;
    float4 LightDiffuse;
    float4 LightSpecular;
};

cbuffer Material : register ( b2 )
{
	float4 MaterialAmbient;
    float4 MaterialDiffuse;
    float4 MaterialSpecular;    
    float MaterialShininess;
};

cbuffer viewPos : register ( b3 )
{
	float4 eye;
};

struct VS_INPUT
{	
    float4 Pos : POSITION;
    float4 Nor : NORMAL;
    float4 Tex : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
    float4 Nor : NORMAL;
    float4 Tex : TEXCOORD0;
};

PS_INPUT VS_Main( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    //output.Pos = input.Pos;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Nor = mul( input.Nor , World );
    //output.Nor = input.Nor;
    output.Tex = input.Tex;

    return output;
}


float4 PS_Main( PS_INPUT input) : SV_Target
{
	 float3 a_LightPosition = LightPosition;
 //    float3 a_LightAmbient = float3(LightAmbient);
 //    float3 a_LightDiffuse = float3(LightDiffuse);
 //    float3 a_LightSpecular = float3(LightSpecular);

	// float3 a_MaterialAmbient = float3(MaterialAmbient);
 //    float3 a_MaterialDiffuse = float3(MaterialDiffuse);
 //    float3 a_MaterialSpecular = float3(MaterialSpecular);

 //    float3 a_eye = float3(eye);

 //    float3 ambient = a_LightAmbient * txDiffuse.Sample( samLinear, input.Tex );

 //    float3 norm = normalize(input.Nor);
 //    float3 lightDir = normalize(a_LightPosition - input.Pos);
 //    float diff = max(dot(norm, lightDir), 0.0);
 //    float3 diffuse = a_LightDiffuse * diff * float3(txDiffuse.Sample( samLinear, input.Tex));

 //   	float3 viewDir = normalize(a_eye - input.Pos);
 //    float3 reflectDir = reflect(-lightDir, norm);  
 //    float spec = pow(max(dot(viewDir, reflectDir), 0.0), MaterialShininess);
 //    float3 specular = a_LightSpecular * spec * float3(txSpecular.Sample( samLinear, input.Tex));


 //    float4 result = ambient + diffuse + specular;
 //    result.a = 1.0f;	
 //    return result;
 		return float4(0.0f,0.0f,0.0f,0.0f);
}

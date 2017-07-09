#include "HLSLSamplerState.h"



Miracle::HLSLSamplerState::HLSLSamplerState(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc, _U32 a_Index)
	: HLSLResource(a_Desc,a_Index,0)
{

}

Miracle::HLSLSamplerState::HLSLSamplerState(const D3D11_SHADER_INPUT_BIND_DESC& a_Desc)
	: HLSLResource(a_Desc,0)
{

}

Miracle::HLSLSamplerState::~HLSLSamplerState()
{
}

#include <Rendering/Base/Resource/State/SamplerState.h>



Miracle::SamplerState::SamplerState()
	: State(GraphicsObject::SAMPLER_STATE)
	, filter(MIN_P_MAG_P_MIP_P)
	, mipLODBias(0.0f)
	, maxAnisotropy(1)
	, comparison(NEVER)
	, minLOD(-FLT_MAX)
	, maxLOD( FLT_MAX)
{
	mode[0] = WRAP;
	mode[1] = WRAP;
	mode[2] = WRAP;
	borderColor = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
}


Miracle::SamplerState::~SamplerState()
{
}

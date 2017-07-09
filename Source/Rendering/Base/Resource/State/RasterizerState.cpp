#include <Rendering/Base/Resource/State/RasterizerState.h>



Miracle::RasterizerState::RasterizerState()
	: State(GraphicsObject::RASTERIZER_STATE)
	, fillMode(FILL_SOLID)
	, cullMode(CULL_NONE)
	, frontCCW(false)
	, depthBias(0)
	, depthBiasClamp(0.0f)
	, slopeScaledDepthBias(0.0f)
	, enableDepthClip(true)
	, enableScissor(false)
	, enableMultisample(false)
	, enableAntialiasedLine(false)
{

}


Miracle::RasterizerState::~RasterizerState()
{
}

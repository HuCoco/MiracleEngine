#include <Rendering/Base/Resource/State/BlendState.h>

Miracle::BlendState::BlendState()
	: State(GraphicsObject::BLEND_STATE)
	, enableAlphaToCoverage(false)
	, enableIndependentBlend(false)
	, sampleMask(0xffffffff)
{
	blendColor = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
}

Miracle::BlendState::~BlendState()
{

}

Miracle::BlendState::Target::Target()
	: enable(false)
	, srcColor(Mode::ONE)
	, dstColor(Mode::ZERO)
	, opColor(Operation::ADD)
	, srcAlpha(Mode::ONE)
	, dstAlpha(Mode::ZERO)
	, opAlpha(Operation::ADD)
	, mask(ColorWrite::ENABLE_ALL)
{

}

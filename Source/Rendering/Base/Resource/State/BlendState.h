#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/State/State.h>
#include <Core/Mathematics/GraphicsMathematics.h>

NAMESPACE_MENGINE_BEGIN

class BlendState : public State
{
public:

	enum Mode
	{
		ZERO,
		ONE,
		SRC_COLOR,
		INV_SRC_COLOR,
		SRC_ALPHA,
		INV_SRC_ALPHA,
		DEST_ALPHA,
		INV_DEST_ALPHA,
		DEST_COLOR,
		INV_DEST_COLOR,
		SRC_ALPHA_SAT,
		FACTOR,
		INV_FACTOR,
		SRC1_COLOR,
		INV_SRC1_COLOR,
		SRC1_ALPHA,
		INV_SRC1_ALPHA
	};

	enum Operation
	{
		ADD,
		SUBTRACT,
		REV_SUBTRACT,
		MIN,
		MAX
	};

	enum ColorWrite
	{
		ENABLE_RED = 1,
		ENABLE_GREEN = 2,
		ENABLE_BLUE = 4,
		ENABLE_ALPHA = 8,
		ENABLE_ALL = 15
	};

	enum { NUM_TARGETS  = 8 };

	struct Target
	{
		bool enable;
		Mode srcColor;
		Mode dstColor;
		Operation opColor;
		Mode srcAlpha;
		Mode dstAlpha;
		Operation opAlpha;
		_U8 mask;

		Target();
	};

	BlendState();
	virtual ~BlendState();

	bool enableAlphaToCoverage;
	bool enableIndependentBlend;;
	Target target[NUM_TARGETS];
	Vector4f blendColor;
	_U32 sampleMask;
};

NAMESPACE_MENGINE_END
#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/State/State.h>

NAMESPACE_MENGINE_BEGIN

class DepthStencilState : public State
{
public:

	enum WriteMask
	{
		MASK_ZERO,
		MASK_ALL
	};

	enum Comparison
	{
		NEVER,
		LESS,
		EQUAL,
		LESS_EQUAL,
		GREATER,
		NOT_EQUAL,
		GREATER_EQUAL,
		ALWAYS
	};

	enum Operation
	{
		KEEP,
		ZERO,
		REPLACE,
		INCR_SAT,
		DECR_SAT,
		INVERT,
		INCR,
		DECR
	};

	struct Face
	{
		Operation fail{ Operation::KEEP };
		Operation depthFail{ Operation::KEEP };
		Operation pass{ Operation::KEEP };
		Comparison comparison{ Comparison::ALWAYS };
	};


	DepthStencilState();
	virtual ~DepthStencilState();

	bool depthEnable{ true };                  
	WriteMask writeMask{ WriteMask::MASK_ALL };
	Comparison comparison{ Comparison::LESS_EQUAL };
	bool stencilEnable{ false };
	_U8 stencilReadMask{ 0xff };
	_U8 stencilWriteMask{ 0xff };
	Face frontFace;                     
	Face backFace;                      
	_U32 reference{ 0 };
};

NAMESPACE_MENGINE_END
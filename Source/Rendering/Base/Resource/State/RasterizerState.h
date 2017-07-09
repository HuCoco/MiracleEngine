#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Resource/State/State.h>

NAMESPACE_MENGINE_BEGIN

class RasterizerState : public State
{
public:

	enum FillMode
	{
		FILL_SOLID,
		FILL_WIREFRAME
	};

	enum CullMode
	{
		CULL_NONE,
		CULL_FRONT,
		CULL_BACK
	};



	RasterizerState();
	virtual ~RasterizerState();

	FillMode fillMode;            
	CullMode cullMode;
	bool frontCCW;
	_I32 depthBias;                  
	_F32 depthBiasClamp;          
	_F32 slopeScaledDepthBias;    
	bool enableDepthClip;         
	bool enableScissor;          
	bool enableMultisample;      
	bool enableAntialiasedLine;  
};

NAMESPACE_MENGINE_END
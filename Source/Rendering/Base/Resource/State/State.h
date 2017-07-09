#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/GraphicsObject.h>

NAMESPACE_MENGINE_BEGIN

class State : public GraphicsObject
{
public:
	State(_U32 a_Type = GraphicsObject::STATE);
	virtual ~State();
};

NAMESPACE_MENGINE_END

#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Component/Scene/SceneComponent.h>

NAMESPACE_MENGINE_BEGIN
class World;
class PrimitiveComponent : public SceneComponent
{
public:
	PrimitiveComponent();
	~PrimitiveComponent();

	virtual void RenderFunc() = 0;
	virtual void AddUpdateFuncToUpdateManager(World* a_World);

};

NAMESPACE_MENGINE_END
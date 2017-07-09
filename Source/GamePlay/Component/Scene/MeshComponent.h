#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/File/Model/Mesh.h>
#include <GamePlay/Component/Scene/PrimitiveComponent.h>

NAMESPACE_MENGINE_BEGIN

class MeshComponent : public PrimitiveComponent
{
public:
	MeshComponent(Mesh* a_Mesh);
	~MeshComponent();

	virtual void RenderFunc();


private:
	Mesh* m_Mesh;
};

NAMESPACE_MENGINE_END
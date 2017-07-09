#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Rendering/VisualEffect/VisualEffect.h>

NAMESPACE_MENGINE_BEGIN

class VisualEffectManager
{
public:
	VisualEffectManager();
	~VisualEffectManager();

	void AddEffect(const std::string& a_Name, std::shared_ptr<VisualEffect> a_Effect);
	std::shared_ptr<VisualEffect> GetEffect(const std::string& a_Name);

private:
	MSet<std::string, std::shared_ptr<VisualEffect>> m_EffectTree;
};

NAMESPACE_MENGINE_END
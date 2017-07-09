#include "VisualEffectManager.h"



Miracle::VisualEffectManager::VisualEffectManager()
{
}


Miracle::VisualEffectManager::~VisualEffectManager()
{
}

void Miracle::VisualEffectManager::AddEffect(const std::string& a_Name, std::shared_ptr<VisualEffect> a_Effect)
{
	bool Successful = m_EffectTree.Insert(a_Name, a_Effect);
	MENGINE_ASSERT_MSG(Successful == true, "Already have this effect.");
}

std::shared_ptr<Miracle::VisualEffect> Miracle::VisualEffectManager::GetEffect(const std::string& a_Name)
{
	auto EffectNode = m_EffectTree.Find(a_Name);
	std::shared_ptr<Miracle::VisualEffect> ret;
	if (EffectNode == nullptr)
	{
		ret = nullptr;
	}
	else
	{
		ret = EffectNode->Value;
	}
	return ret;
}



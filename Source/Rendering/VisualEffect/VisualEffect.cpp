#include <Rendering/VisualEffect/VisualEffect.h>

Miracle::VisualEffect::VisualEffect(VisualProgram* a_Program)
	: m_Program(a_Program)
	, m_NeedUpdateAffineMatrixs(false)
	, m_NeedUpdateTextures(false)
{

}

Miracle::VisualEffect::VisualEffect()
{

}

Miracle::VisualEffect::~VisualEffect()
{
}

std::string Miracle::VisualEffect::GetEffectType() const
{
	return std::string("VisualEffect");
}

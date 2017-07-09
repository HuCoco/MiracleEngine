#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/ProgramFactory.h>
#include <Independent/File/Model/Mesh.h>
#include <Rendering/Base/DataBlockInShader.h>
NAMESPACE_MENGINE_BEGIN

class VisualEffect
{
public:
	VisualEffect(VisualProgram* a_Program);
	~VisualEffect();

	virtual void UpdateAffineMatrixs(AffineMatrixs* a_AffineMatrixs) = 0;
	virtual void UpdateTextures(std::shared_ptr<Texture2D> a_DiffuseTexture, std::shared_ptr<Texture2D> a_SpecularTexture) = 0;

	inline const std::shared_ptr<VisualProgram>& GetProgram() const;
	inline const std::shared_ptr<VertexShader>& GetVertexShader() const;
	inline const std::shared_ptr<PixelShader>& GetPixelShader() const;
	
	virtual std::string GetEffectType() const;

	inline bool IsNeedUpdateAffineMatrixs() const;
	inline bool IsNeedUpdateTxtures() const;
protected:
	VisualEffect();

protected:
	std::shared_ptr<VisualProgram> m_Program;
	bool m_NeedUpdateAffineMatrixs;
	bool m_NeedUpdateTextures;

};


inline const std::shared_ptr<VisualProgram>& VisualEffect::GetProgram() const
{
	return m_Program;
}

inline const std::shared_ptr<VertexShader>& VisualEffect::GetVertexShader() const
{
	return m_Program->GetVertexShader();
}

inline const std::shared_ptr<PixelShader>& VisualEffect::GetPixelShader() const
{
	return m_Program->GetPixelShader();
}

inline bool VisualEffect::IsNeedUpdateAffineMatrixs() const
{
	return m_NeedUpdateAffineMatrixs;
}

inline bool VisualEffect::IsNeedUpdateTxtures() const
{
	return m_NeedUpdateTextures;
}

NAMESPACE_MENGINE_END
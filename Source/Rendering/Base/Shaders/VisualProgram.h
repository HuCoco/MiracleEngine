#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Rendering/Base/Shaders/VertexShader.h>
#include <Rendering/Base/Shaders/PixelShader.h>

NAMESPACE_MENGINE_BEGIN

class VisualProgram
{
public:
	VisualProgram();
	virtual ~VisualProgram();

	inline const std::shared_ptr<VertexShader>& GetVertexShader() const;
	inline const std::shared_ptr<PixelShader>& GetPixelShader() const;

	inline void SetVertexShader(const std::shared_ptr<VertexShader>& a_VertexShader);
	inline void SetPixelShader(const std::shared_ptr<PixelShader>& a_PixelShader);

private:
	std::shared_ptr<VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;
};

inline const std::shared_ptr<VertexShader>& VisualProgram::GetVertexShader() const
{
	return m_VertexShader;
}

inline const std::shared_ptr<PixelShader>& VisualProgram::GetPixelShader() const
{
	return m_PixelShader;
}

inline void Miracle::VisualProgram::SetVertexShader(const std::shared_ptr<VertexShader>& a_VertexShader)
{
	m_VertexShader = a_VertexShader;
}

inline void Miracle::VisualProgram::SetPixelShader(const std::shared_ptr<PixelShader>& a_PixelShader)
{
	m_PixelShader = a_PixelShader;
}


NAMESPACE_MENGINE_END
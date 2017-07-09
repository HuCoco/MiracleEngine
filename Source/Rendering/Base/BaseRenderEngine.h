#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Core/Mathematics/GraphicsMathematics.h>
#include <Rendering/Base/Resource/State/BlendState.h>
#include <Rendering/Base/Resource/State/DepthStencilState.h>
#include <Rendering/Base/Resource/State/RasterizerState.h>
#include <Rendering/Base/Resource/Buffer/Buffer.h>
#include <Rendering/Base/Resource/Texture/TextureSingle.h>


NAMESPACE_MENGINE_BEGIN

class BaseRenderEngine
{
public:
	virtual ~BaseRenderEngine();

	virtual void SetViewport(_I32 a_X, _I32 a_Y, _I32 a_Width, _I32 a_Height) = 0;
	virtual void GetViewport(_I32& a_X, _I32& a_Y, _I32& a_Width, _I32& a_Height) const = 0;
	virtual void SetDepthRange(_F32 a_Near, _F32 a_Far) = 0;
	virtual void GetDepthRange(_F32& a_Near, _F32& a_Far) const = 0;

	virtual bool Resize(_U32 a_Width, _U32 a_Height) = 0;

	inline void SetClearColor(const Vector4f& a_Color);
	inline const Vector4f& GetClearColor() const;

	inline void SetClearDepth(_F32 a_Depth);
	inline _F32 GetClearDepth() const;

	inline void SetClearStencil(_U32 a_ClearStencil);
	inline _U32 GetClearStencil() const;
	
	//virtual void DisplayColorBuffer(_U32 a_SyncInterval) = 0;

	/* BlendState */
	virtual void SetBlendState(const std::shared_ptr<BlendState>& state) = 0;
	inline const std::shared_ptr<BlendState>& GetBlendState() const;
	inline void SetDefaultBlendState();
	inline const std::shared_ptr<BlendState>& GetDefaultBlendState() const;

	/* DepthStencilState */
	virtual void SetDepthStencilState(const std::shared_ptr<DepthStencilState>& state) = 0;
	inline const std::shared_ptr<DepthStencilState>& GetDepthStencilState() const;
	inline void SetDefaultDepthStencilState();
	inline const std::shared_ptr<DepthStencilState>& GetDefaultDepthStencilState() const;

	/* RasterizerState */
	virtual void SetRasterizerState(const std::shared_ptr<RasterizerState>& state) = 0;
	inline const std::shared_ptr<RasterizerState>& GetRasterizerState() const;
	inline void SetDefaultRasterizerState();
	inline const std::shared_ptr<RasterizerState>& GetDefaultRasterizerState() const;

	//virtual bool Update(const Buffer* a_Buffer) = 0;
	//virtual bool Update(const TextureSingle* a_Buffer) = 0;

protected:
	BaseRenderEngine();
	BaseRenderEngine(BaseRenderEngine const&) = delete;
	BaseRenderEngine& operator=(BaseRenderEngine const&) = delete;

	void CreateDefaultGlobalState();
	virtual void DestroyDefaultGlobalState();

	_U32 m_Width;
	_U32 m_Height;

	Vector4f m_ClearColor;
	_F32 m_ClearDepth;
	_I32 m_ClearStencil;

	std::shared_ptr<BlendState> m_DefaultBlendState;
	std::shared_ptr<BlendState> m_ActiveBlendState;
	std::shared_ptr<DepthStencilState> m_DefaultDepthStencilState;
	std::shared_ptr<DepthStencilState> m_ActiveDepthStencilState;
	std::shared_ptr<RasterizerState> m_DefaultRasterizerState;
	std::shared_ptr<RasterizerState> m_ActiveRasterizerState;


};

inline void BaseRenderEngine::SetClearColor(const Vector4f& a_Color)
{
	m_ClearColor = a_Color;
}

inline const Vector4f& BaseRenderEngine::GetClearColor() const
{
	return m_ClearColor;
}

inline void BaseRenderEngine::SetClearDepth(_F32 a_Depth)
{
	m_ClearDepth = a_Depth;
}

inline _F32 BaseRenderEngine::GetClearDepth() const
{
	return m_ClearDepth;
}

inline void BaseRenderEngine::SetClearStencil(_U32 a_ClearStencil)
{
	m_ClearStencil = a_ClearStencil;
}

inline _U32 BaseRenderEngine::GetClearStencil() const
{
	return m_ClearStencil;
}

inline const std::shared_ptr<BlendState>& BaseRenderEngine::GetBlendState() const
{
	return m_ActiveBlendState;
}

inline void BaseRenderEngine::SetDefaultBlendState()
{
	SetBlendState(m_DefaultBlendState);
}

inline const std::shared_ptr<BlendState>& BaseRenderEngine::GetDefaultBlendState() const
{
	return m_DefaultBlendState;
}

inline const std::shared_ptr<DepthStencilState>& BaseRenderEngine::GetDepthStencilState() const
{
	return m_ActiveDepthStencilState;
}

inline void BaseRenderEngine::SetDefaultDepthStencilState()
{
	SetDepthStencilState(m_DefaultDepthStencilState);
}

inline const std::shared_ptr<DepthStencilState>& BaseRenderEngine::GetDefaultDepthStencilState() const
{
	return m_DefaultDepthStencilState;
}

inline const std::shared_ptr<RasterizerState>& BaseRenderEngine::GetRasterizerState() const
{
	return m_ActiveRasterizerState;
}

inline void BaseRenderEngine::SetDefaultRasterizerState()
{
	SetRasterizerState(m_DefaultRasterizerState);
}

inline const std::shared_ptr<RasterizerState>& BaseRenderEngine::GetDefaultRasterizerState() const
{
	return m_DefaultRasterizerState;
}

NAMESPACE_MENGINE_END
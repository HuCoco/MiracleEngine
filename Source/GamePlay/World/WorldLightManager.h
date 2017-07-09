#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <GamePlay/Base/Lights.h>

NAMESPACE_MENGINE_BEGIN

class WorldLightManager
{
public:
	WorldLightManager();
	~WorldLightManager();

	void ClearLights();

	// Directional Light
	void AddDirectionalLight(const DirectionalLight& a_Light);
	void ClearDirectionalLights();
	inline const void* GetDirectionalLightsData() const
	{
		return m_DirectionalLights.data();
	}

	inline _U32 GetNumActiveDirectionalLights() const
	{
		return m_NumActiveDirectionalLights;
	}

	// Point Light
	void AddPointLight(const PointLight& a_Light);
	void ClearPointLights();
	inline const void* GetPointLightsData() const
	{
		return m_PointLights.data();
	}

	inline _U32 GetNumActivePointLights() const
	{
		return m_NumActivePointLights;
	}

	// Spot Light
	void AddSpotLight(const SpotLight& a_Light);
	void ClearSpotLights();
	inline const void* GetSpotLightsData() const
	{
		return m_SpotLights.data();
	}

	inline _U32 GetNumActiveSpotLights() const
	{
		return m_NumActiveSpotLights;
	}

private:
	_U32 m_NumActiveDirectionalLights;
	std::vector<DirectionalLight> m_DirectionalLights;

	_U32 m_NumActivePointLights;
	std::vector<PointLight> m_PointLights;

	_U32 m_NumActiveSpotLights;
	std::vector<SpotLight> m_SpotLights;
};

NAMESPACE_MENGINE_END
#include "WorldLightManager.h"



Miracle::WorldLightManager::WorldLightManager()
	: m_DirectionalLights(MAX_NUM_OF_DIRECTIONAL_LIGHTS)
	, m_PointLights(MAX_NUM_OF_POINT_LIGHTS)
	, m_SpotLights(MAX_NUM_OF_SPOT_LIGHTS)
	, m_NumActiveDirectionalLights(0)
	, m_NumActivePointLights(0)
	, m_NumActiveSpotLights(0)
{
}


Miracle::WorldLightManager::~WorldLightManager()
{
}

void Miracle::WorldLightManager::ClearLights()
{
	ClearDirectionalLights();
	ClearPointLights();
	ClearSpotLights();
}

void Miracle::WorldLightManager::AddDirectionalLight(const DirectionalLight& a_Light)
{
	if (m_NumActiveDirectionalLights < MAX_NUM_OF_DIRECTIONAL_LIGHTS)
	{
		m_DirectionalLights[m_NumActiveDirectionalLights++] = a_Light;
	}
}

void Miracle::WorldLightManager::ClearDirectionalLights()
{
	m_DirectionalLights.clear();
	m_DirectionalLights.resize(m_NumActiveDirectionalLights);
	m_NumActiveDirectionalLights = 0;
}

void Miracle::WorldLightManager::AddPointLight(const PointLight& a_Light)
{
	if (m_NumActivePointLights < MAX_NUM_OF_POINT_LIGHTS)
	{
		m_PointLights[m_NumActivePointLights++] = a_Light;
	}
}

void Miracle::WorldLightManager::ClearPointLights()
{
	m_PointLights.clear();
	m_PointLights.resize(m_NumActivePointLights);
	m_NumActivePointLights = 0;
}

void Miracle::WorldLightManager::AddSpotLight(const SpotLight& a_Light)
{
	if (m_NumActiveSpotLights < MAX_NUM_OF_SPOT_LIGHTS)
	{
		m_SpotLights[m_NumActiveSpotLights++] = a_Light;
	}
}

void Miracle::WorldLightManager::ClearSpotLights()
{
	m_SpotLights.clear();
	m_SpotLights.resize(m_NumActiveSpotLights);
	m_NumActiveSpotLights = 0;
}


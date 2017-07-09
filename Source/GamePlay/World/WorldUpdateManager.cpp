#include "WorldUpdateManager.h"
#include <Core/Engine/MEngine.h>


Miracle::WorldUpdateManager::WorldUpdateManager()
{
}


Miracle::WorldUpdateManager::~WorldUpdateManager()
{
}

void Miracle::WorldUpdateManager::DoUpdate(_F32 a_DeltaTime)
{
	DoCommonGameUpdate(a_DeltaTime);
	DoCameraUpdate();
	DoLightUpdate();
	MEngine::Instance()->GetRenderSystem()->RenderCurrentWorld();
}

void Miracle::WorldUpdateManager::DoCommonGameUpdate(_F32 a_DeltaTime)
{
	MENGINE_SET_ITERATOR_BEGIN(m_CommonGameUpdateFuncSet)
	{
		MENGINE_SET_GET_VALUE(a_DeltaTime);
	}
	MENGINE_SET_ITERATOR_END(m_CommonGameUpdateFuncSet)
}

void Miracle::WorldUpdateManager::DoCameraUpdate()
{
	MENGINE_SET_ITERATOR_BEGIN(m_CameraUpdateFuncSet)
	{
		MENGINE_SET_GET_VALUE();
	}
	MENGINE_SET_ITERATOR_END(m_CameraUpdateFuncSet)
}

void Miracle::WorldUpdateManager::DoLightUpdate()
{
	MENGINE_SET_ITERATOR_BEGIN(m_LightUpdateFuncSet)
	{
		MENGINE_SET_GET_VALUE();
	}
	MENGINE_SET_ITERATOR_END(m_LightUpdateFuncSet)
}

void Miracle::WorldUpdateManager::DoRender()
{
	MENGINE_SET_ITERATOR_BEGIN(m_RenderFuncSet)
	{
		MENGINE_SET_GET_VALUE();
	}
	MENGINE_SET_ITERATOR_END(m_RenderFuncSet)
}

void Miracle::WorldUpdateManager::AddCommonGameUpdateFunc(const HName& a_FuncName, const CommonGameUpdateFunc& a_Func)
{
	m_CommonGameUpdateFuncSet.Insert(a_FuncName, a_Func);
}

void Miracle::WorldUpdateManager::AddCameraUpdateFunc(const HName& a_FuncName, const CameraUpdateFunc& a_Func)
{
	m_CameraUpdateFuncSet.Insert(a_FuncName, a_Func);
}

void Miracle::WorldUpdateManager::AddLightUpdateFunc(const HName& a_FuncName, const LightUpdateFunc& a_Func)
{
	m_LightUpdateFuncSet.Insert(a_FuncName, a_Func);
}

void Miracle::WorldUpdateManager::AddRenderFunc(const HName& a_FuncName, const RenderFunc& a_Func)
{
	m_RenderFuncSet.Insert(a_FuncName, a_Func);
}

void Miracle::WorldUpdateManager::RemoveCommonGameUpdateFunc(const HName& a_FuncName)
{
	m_CommonGameUpdateFuncSet.Remove(a_FuncName);
}

void Miracle::WorldUpdateManager::RemoveCameraUpdateFunc(const HName& a_FuncName)
{
	m_CameraUpdateFuncSet.Remove(a_FuncName);
}

void Miracle::WorldUpdateManager::RemoveLightUpdateFunc(const HName& a_FuncName)
{
	m_LightUpdateFuncSet.Remove(a_FuncName);
}

void Miracle::WorldUpdateManager::RemoveRenderFunc(const HName& a_FuncName)
{
	m_RenderFuncSet.Remove(a_FuncName);
}

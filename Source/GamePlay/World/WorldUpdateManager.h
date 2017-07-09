#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <Independent/DataStructure/MSet.h>
#include <Core/Foundation/HName.h>
NAMESPACE_MENGINE_BEGIN

class WorldUpdateManager
{
public:
	typedef std::function<void(_F32)> CommonGameUpdateFunc;
	typedef std::function<void(void)> CameraUpdateFunc;
	typedef std::function<void(void)> LightUpdateFunc;
	typedef std::function<void(void)> RenderFunc;


	WorldUpdateManager();
	~WorldUpdateManager();

	void DoUpdate(_F32 a_DeltaTime);

	void AddCommonGameUpdateFunc(const HName& a_FuncName, const CommonGameUpdateFunc& a_Func);
	void RemoveCommonGameUpdateFunc(const HName& a_FuncName);

	void AddCameraUpdateFunc(const HName& a_FuncName, const CameraUpdateFunc& a_Func);
	void RemoveCameraUpdateFunc(const HName& a_FuncName);

	void AddLightUpdateFunc(const HName& a_FuncName, const LightUpdateFunc& a_Func);
	void RemoveLightUpdateFunc(const HName& a_FuncName);

	void AddRenderFunc(const HName& a_FuncName, const RenderFunc& a_Func);
	void RemoveRenderFunc(const HName& a_FuncName);

private:
	void DoCommonGameUpdate(_F32 a_DeltaTime);
	void DoCameraUpdate();
	void DoLightUpdate();
public:
	void DoRender();


private:
	MSet<HName, CommonGameUpdateFunc> m_CommonGameUpdateFuncSet;
	MSet<HName, CameraUpdateFunc> m_CameraUpdateFuncSet;
	MSet<HName, LightUpdateFunc> m_LightUpdateFuncSet;
	MSet<HName, RenderFunc> m_RenderFuncSet;
};

NAMESPACE_MENGINE_END
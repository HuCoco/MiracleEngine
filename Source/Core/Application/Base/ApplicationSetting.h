#pragma once
#include <Independent/Platform/PreCompileHeader.h>

class ApplicationSetting
{
public:
	ApplicationSetting();
	~ApplicationSetting();

	void LoadSetting();
	void SetDefaultSetting();
	enum class AppRenderMode
	{
		Unkown,
		OpenGL,
		DirectX11
	};
private:
	struct AppResolution
	{
		_U32 Width;
		_U32 Height;
	}; 



public:
	AppResolution Resolution;
	AppRenderMode RenderMode;
};


#include "ApplicationSetting.h"



ApplicationSetting::ApplicationSetting()
	: RenderMode(AppRenderMode::Unkown)
{
}


ApplicationSetting::~ApplicationSetting()
{
}

void ApplicationSetting::LoadSetting()
{

}

void ApplicationSetting::SetDefaultSetting()
{
	RenderMode = AppRenderMode::OpenGL;
	Resolution.Width = 800;
	Resolution.Height = 600;
}

#include "DefaultWorldContext.h"
#include "DisplayGunModelWorld.h"
#include "DisplayFlashLightWorld.h"
#include "DisplayMultipleLightsWorld.h"


DefaultWorldContext::DefaultWorldContext()
{
}


DefaultWorldContext::~DefaultWorldContext()
{
}

void DefaultWorldContext::Initialize()
{
	auto DisplayWorld = std::make_shared<DisplayMultipleLightsWorld>();
	AddWorld(DisplayWorld);

	SetCurrentWorld(DisplayWorld->GetName());
}

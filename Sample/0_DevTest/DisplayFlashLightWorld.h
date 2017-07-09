#pragma once
#include <GamePlay/World.h>

USING_NAMESPACE_MENGINE

class DisplayFlashLightWorld : public World
{
public:
	DisplayFlashLightWorld();
	~DisplayFlashLightWorld();

	virtual void Load();
	virtual void Update(_F32 a_DeltaTime);

private:
	std::shared_ptr<GameObject> NanoSuitObject[25];
	std::shared_ptr<GameObject> LightObject;
	std::shared_ptr<GameObject> CameraObject;
};


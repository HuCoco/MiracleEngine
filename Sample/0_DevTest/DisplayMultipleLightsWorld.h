#pragma once
#include <GamePlay/World.h>

USING_NAMESPACE_MENGINE

class DisplayMultipleLightsWorld : public World
{
public:
	DisplayMultipleLightsWorld();
	~DisplayMultipleLightsWorld();

	virtual void Load();
	virtual void Update(_F32 a_DeltaTime);

private:
	std::shared_ptr<GameObject> NanoSuitObject[25];
	std::shared_ptr<GameObject> DirectionalLightObject;
	std::shared_ptr<GameObject> PointLightObject[2];
	std::shared_ptr<GameObject> CameraObject;
};


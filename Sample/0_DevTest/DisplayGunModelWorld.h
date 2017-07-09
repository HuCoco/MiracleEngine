#pragma once
#include <GamePlay/World.h>

USING_NAMESPACE_MENGINE 

class DisplayGunModelWorld : public World
{
public:
	DisplayGunModelWorld();
	~DisplayGunModelWorld();

	virtual void Load();
	virtual void Update(_F32 a_DeltaTime);

private:
	std::shared_ptr<GameObject> GunObject;
	std::shared_ptr<GameObject> LightObject;
	std::shared_ptr<GameObject> CameraObject;
};


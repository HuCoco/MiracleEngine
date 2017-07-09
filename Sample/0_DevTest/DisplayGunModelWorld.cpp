#include "DisplayGunModelWorld.h"
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/Component/Component.h>
#include <GamePlay/Component/Scene/SceneComponent.h>
#include <GamePlay/Component/Scene/CameraComponent.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Component/Scene/MeshComponent.h>
#include <GamePlay/Component/Scene/DirectionalLightComponent.h>
#include <GamePlay/Component/Scene/PointLightComponent.h>
#include <GamePlay/Component/Scene/PerspectiveCameraComponent.h>
#include <GamePlay/Component/Functional/ControllerComponent.h>
#include <GamePlay/Controller/CameraMotionController.h>
#include <ResourceManager/GameResourceSystem.h>


DisplayGunModelWorld::DisplayGunModelWorld()
	: GunObject(std::make_shared<GameObject>())
	, LightObject(std::make_shared<GameObject>())
	, CameraObject(std::make_shared<GameObject>())
{
	SetName("DisplayGunModelWorld");
}


DisplayGunModelWorld::~DisplayGunModelWorld()
{
}

void DisplayGunModelWorld::Load()
{
	// Load CameraObject
	CameraObject->SetName("MainCamera");
	std::shared_ptr<ControllerComponent> ControllerCmp = std::make_shared<ControllerComponent>();
	CameraMotionController* Controller = new CameraMotionController;
	Controller->SetDefaulControllKey();
	ControllerCmp->SetController(Controller);
	std::shared_ptr<PerspectiveCameraComponent> PerspectiveCameraCmp = std::make_shared<PerspectiveCameraComponent>();
	PerspectiveCameraCmp->SetName("MainCamera");
	CameraObject->AppendComponent(PerspectiveCameraCmp);
	CameraObject->AppendComponent(ControllerCmp);
	CameraObject->GetTransform()->RotateYaw(MENGINE_PI);
	CameraObject->GetTransform()->MoveYZ(0.0f, 20.0f);
	AddGameObject(CameraObject);
	GetCameraManager().SwitchCamera(CameraObject->GetName());

	// Load GunObject
	auto model = GameResourceSystem::Instance()->GetModel(HName("./Resource/Obj/gun.obj"));
	for each(auto mesh in model->GetMeshs())
	{
		GunObject->AppendComponent(std::make_shared<MeshComponent>(mesh));
	}
	GunObject->GetTransform()->SetScale3D(Vector3f(0.2f, 0.2f, 0.2f));
	//GunObject->GetTransform()->RotateYaw(MENGINE_PI / 2);
	AddGameObject(GunObject);

	// Load LightObject
	DirectionalLight DirectionLightInfo(
		Vector4f(-1.0f, -1.0f, -1.0f, 0.0f),
		Vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4f(0.64f, 0.64f, 0.64f, 0.64f),
		Vector4f(0.5f, 0.5f, 0.5f, 0.5f));

	std::shared_ptr<DirectionalLightComponent> DirectionLightCmp = std::make_shared<DirectionalLightComponent>(DirectionLightInfo);
	LightObject->AppendComponent(DirectionLightCmp);
	AddGameObject(LightObject);

}

void DisplayGunModelWorld::Update(_F32 a_DeltaTime)
{
	//TODO: AnimationComponent can do rotate action.
	GunObject->GetTransform()->RotateYaw(a_DeltaTime * 0.5f);
	World::Update(a_DeltaTime);
}

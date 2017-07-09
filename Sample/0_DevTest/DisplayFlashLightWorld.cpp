#include "DisplayFlashLightWorld.h"
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/Component/Component.h>
#include <GamePlay/Component/Scene/SceneComponent.h>
#include <GamePlay/Component/Scene/CameraComponent.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Component/Scene/MeshComponent.h>
#include <GamePlay/Component/Scene/FlashLightComponent.h>
#include <GamePlay/Component/Scene/PerspectiveCameraComponent.h>
#include <GamePlay/Component/Functional/ControllerComponent.h>
#include <GamePlay/Controller/CameraMotionController.h>
#include <ResourceManager/GameResourceSystem.h>


DisplayFlashLightWorld::DisplayFlashLightWorld()
	: LightObject(std::make_shared<GameObject>())
	, CameraObject(std::make_shared<GameObject>())
{
	for (int i = 0; i < 25; ++i)
	{
		NanoSuitObject[i] = std::make_shared<GameObject>();
	}
	SetName("DisplayFlashLightWorld");
}


DisplayFlashLightWorld::~DisplayFlashLightWorld()
{
}

void DisplayFlashLightWorld::Load()
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

	


	// Load LightObject
	SpotLight SpotLightInfo(
		Vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4f(0.8f, 0.8f, 0.8f, 0.8f),
		Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0.07f,
		0.017f,
		std::cos(MathUtils::Angle2Radian(12.5f)),
		std::cos(MathUtils::Angle2Radian(17.5f)),
		Vector4f(1.0f, 1.0f, 1.0f, 1.0f));



	std::shared_ptr<FlashLightComponent> DirectionLightCmp = std::make_shared<FlashLightComponent>(SpotLightInfo);
	CameraObject->AppendComponent(DirectionLightCmp);
	//LightObject->GetTransform()->SetTranslate(Vector3f(0.0f,0.0f,10.0f));
	AddGameObject(CameraObject);
	GetCameraManager().SwitchCamera(CameraObject->GetName());
	//AddGameObject(LightObject);


	// Load GunObject
	auto model = GameResourceSystem::Instance()->GetModel(HName("./Resource/nanosuit/nanosuit.obj"));
	for (int i = 0; i < 25; ++i)
	{
		for each(auto mesh in model->GetMeshs())
		{
			NanoSuitObject[i]->AppendComponent(std::make_shared<MeshComponent>(mesh));
		}
		NanoSuitObject[i]->GetTransform()->SetTranslate(Vector3f((i % 5) * 10.0f, 0.0f, (i / 5) * 10.0f));
		NanoSuitObject[i]->SetName(StringUtils::Format("Nanosuit%d", i));
		AddGameObject(NanoSuitObject[i]);
	}


}

void DisplayFlashLightWorld::Update(_F32 a_DeltaTime)
{
	//TODO: AnimationComponent can do rotate action.
	//LightObject->GetTransform()->RotateYaw(a_DeltaTime * 0.5f);
	World::Update(a_DeltaTime);
}

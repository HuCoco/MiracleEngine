#include "DisplayMultipleLightsWorld.h"
#include <GamePlay/GameoObject/GameObject.h>
#include <GamePlay/Component/Component.h>
#include <GamePlay/Component/Scene/SceneComponent.h>
#include <GamePlay/Component/Scene/CameraComponent.h>
#include <GamePlay/Component/Scene/LightComponent.h>
#include <GamePlay/Component/Scene/MeshComponent.h>
#include <GamePlay/Component/Scene/DirectionalLightComponent.h>
#include <GamePlay/Component/Scene/PointLightComponent.h>
#include <GamePlay/Component/Scene/FlashLightComponent.h>
#include <GamePlay/Component/Scene/PerspectiveCameraComponent.h>
#include <GamePlay/Component/Functional/ControllerComponent.h>
#include <GamePlay/Controller/CameraMotionController.h>
#include <ResourceManager/GameResourceSystem.h>



DisplayMultipleLightsWorld::DisplayMultipleLightsWorld()
	: World()
	, CameraObject(std::make_shared<GameObject>())
	, DirectionalLightObject(std::make_shared<GameObject>())
{
	for (int i = 0; i < 25; ++i)
	{
		NanoSuitObject[i] = std::make_shared<GameObject>();
	}
	PointLightObject[0] = std::make_shared<GameObject>();
	PointLightObject[1] = std::make_shared<GameObject>();
}


DisplayMultipleLightsWorld::~DisplayMultipleLightsWorld()
{
}

void DisplayMultipleLightsWorld::Load()
{

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
	CameraObject->GetTransform()->MoveYZ(20.0f, 20.0f);
	
	SpotLight SpotLightInfo(
		Vector4f(0.3f, 0.3f, 0.3f, 0.3f),
		Vector4f(0.8f, 0.8f, 0.8f, 0.8f),
		Vector4f(1.0f, 1.0f, 1.0f, 1.0f),
		1.0f,
		0.09f,
		0.032f,
		std::cos(MathUtils::Angle2Radian(12.5f)),
		std::cos(MathUtils::Angle2Radian(17.5f)),
		Vector4f(0.0f,1.0f,1.0f,1.0f));



	std::shared_ptr<FlashLightComponent> FlashLightCmp = std::make_shared<FlashLightComponent>(SpotLightInfo);
	CameraObject->AppendComponent(FlashLightCmp);

	AddGameObject(CameraObject);
	GetCameraManager().SwitchCamera(CameraObject->GetName());

	auto model = GameResourceSystem::Instance()->GetModel(HName("./Resource/nanosuit/nanosuit.obj"));
	for (int i = 0; i < 25; ++i)
	{
		for each(auto mesh in model->GetMeshs())
		{
			NanoSuitObject[i]->AppendComponent(std::make_shared<MeshComponent>(mesh));
		}
		NanoSuitObject[i]->GetTransform()->SetTranslate(Vector3f((i % 5) * 10.0f,0.0f, (i / 5) * 10.0f));
		NanoSuitObject[i]->SetName(StringUtils::Format("Nanosuit%d", i));
		AddGameObject(NanoSuitObject[i]);
	}

	{
		PointLight PointLightInfo(
			Vector4f(0.3f, 0.3f, 0.3f, 0.3f),
			Vector4f(0.64f, 0.64f, 0.64f, 0.64f),
			Vector4f(0.5f, 0.5f, 0.5f, 0.5f),
			1.0f,
			0.045f,
			0.0075f,
			Vector4f(1.0f, 0.0f, 0.0f, 1.0f)
		);
		std::shared_ptr<PointLightComponent> PointLightCmp = std::make_shared<PointLightComponent>(PointLightInfo);
		PointLightObject[0]->AppendComponent(PointLightCmp);
		PointLightObject[0]->GetTransform()->SetTranslate(Vector3f(10.0f, 20.0f, 10.0f));
		AddGameObject(PointLightObject[0]);
	}

	{
		PointLight PointLightInfo(
			Vector4f(0.3f, 0.3f, 0.3f, 0.3f),
			Vector4f(0.64f, 0.64f, 0.64f, 0.64f),
			Vector4f(0.5f, 0.5f, 0.5f, 0.5f),
			1.0f,
			0.045f,
			0.0075f,
			Vector4f(0.0f, 1.0f, 0.0f, 1.0f)
		);
		std::shared_ptr<PointLightComponent> PointLightCmp = std::make_shared<PointLightComponent>(PointLightInfo);
		PointLightObject[1]->AppendComponent(PointLightCmp);
		PointLightObject[1]->GetTransform()->SetTranslate(Vector3f(40.0f, 20.0f, 40.0f));
		AddGameObject(PointLightObject[1]);
	}




	DirectionalLight DirectionLightInfo(
		Vector4f(-1.0f, -1.0f, -1.0f, 0.0f),
		Vector4f(0.1f, 0.1f, 0.1f, 0.1f),
		Vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4f(0.0f, 0.0f, 0.0f, 0.0f),
		Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

	std::shared_ptr<DirectionalLightComponent> DirectionLightCmp = std::make_shared<DirectionalLightComponent>(DirectionLightInfo);
	DirectionalLightObject->AppendComponent(DirectionLightCmp);
	AddGameObject(DirectionalLightObject);


}

void DisplayMultipleLightsWorld::Update(_F32 a_DeltaTime)
{
	World::Update(a_DeltaTime);
}

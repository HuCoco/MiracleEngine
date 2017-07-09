#pragma once
#include <GamePlay/GameInstance.h>

USING_NAMESPACE_MENGINE

class DefaultGameInstance : public GameInstance
{
public:
	DefaultGameInstance();
	~DefaultGameInstance();

	virtual void Initialize() override;
};


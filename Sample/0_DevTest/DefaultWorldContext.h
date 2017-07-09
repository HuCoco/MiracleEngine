#pragma once
#include <GamePlay/WorldContext.h>

USING_NAMESPACE_MENGINE

class DefaultWorldContext : public WorldContext
{
public:
	DefaultWorldContext();
	~DefaultWorldContext();

	virtual void Initialize() override;
};


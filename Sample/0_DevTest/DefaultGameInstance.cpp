#include "DefaultGameInstance.h"
#include "DefaultWorldContext.h"


DefaultGameInstance::DefaultGameInstance()
{
}


DefaultGameInstance::~DefaultGameInstance()
{
}

void DefaultGameInstance::Initialize()
{
	DefaultWorldContext* Context = new DefaultWorldContext();
	Context->Initialize();
	SetWorldContext(Context); 
}

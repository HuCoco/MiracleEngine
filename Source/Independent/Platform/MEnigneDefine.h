#pragma once

#if defined(ME_DLL_EXPORT)
#define ME_EXPORT __declspec(dllexport)
#else
#define ME_EXPORT 
#endif


#define NAMESPACE_MENGINE_BEGIN		namespace Miracle {
#define NAMESPACE_MENGINE_END		};

#define USING_NAMESPACE_MENGINE		using namespace Miracle;


#define ARRAY_SIZE_OF( args )		sizeof(args) / sizeof(args[0])

#if defined(__GNUC__) 
#define MENGINE_ALIGN(Alignment)  __attribute__ ((aligned (Alignment)))
#elif defined(_WIN32)
#define MENGINE_ALIGN(Alignment)   __declspec(align(Alignment))
#else
#define MENGINE_ALIGN(Alignment)   
#endif
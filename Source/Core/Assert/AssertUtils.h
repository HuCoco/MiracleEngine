#pragma once

#include <corecrt.h>


template <bool>
struct static_assert_util;
template <>
struct static_assert_util<true> {};

extern "C" {

# undef MENGINE_ASSERT
# undef MENGINE_ASSERT_MSG

#ifdef NDEBUG

#define  MENGINE_ASSERT( expression )					((void)0)
#define  MENGINE_ASSERT_MSG( expression, message )		((void)0)
#define  MENGINE_STATIC_ASSERT( expression )			((void)0)

#else

	_ACRTIMP void __cdecl _wassert(
		_In_z_ wchar_t const* _Message,
		_In_z_ wchar_t const* _File,
		_In_   unsigned       _Line
	);

#define MENGINE_ASSERT(expression) (void)(														 \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \
        )

#define MENGINE_ASSERT_MSG( expression, message ) (void)(											 \
            (!!(expression)) ||                                                              \
            (_wassert(_CRT_WIDE(message), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0)	 \
        )


#define MENGINE_STATIC_ASSERT(expression) static_assert_util<(expression)>()

#endif




}
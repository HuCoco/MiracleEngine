#pragma once
#include <Independent/Platform/PreCompileHeader.h>
#include <math.h>

//
#define RSQRT_NUMBER				0x5F375A86u
#define LEADING_BIT_NUMBER			0x07C4ACDDu
#define TRAILING_BIT_NUMBER			0x077CB531u
#define BIT_1_GET_EVEN_POSITION		0xAAAAAAAAu
#define BIT_1_GET_ODD_POSITION		0x55555555u
#define BIT_2_GET_EVEN_POSITION		0x33333333u
#define BIT_2_GET_ODD_POSITION		0xCCCCCCCCu
#define BIT_4_GET_EVEN_POSITION		0x0F0F0F0Fu
#define BIT_4_GET_ODD_POSITION		0xF0F0F0F0u
#define BIT_8_GET_EVEN_POSITION		0x00FF00FFu
#define BIT_8_GET_ODD_POSITION		0xFF00FF00u
#define BIT_16_GET_EVEN_POSITION	0x0000FFFFu
#define BIT_16_GET_ODD_POSITION		0xFFFF0000u
#define RADIAN_TO_ANGLE				57.32484076433121019108f
#define ANGLE_TO_RADIAN				0.017444444444444444444f


#define GET_I64(v) v##LL
#define GET_U64(v) v##ULL
#define GET_LO_I64(v) (int32_t)((v) & 0x00000000ffffffffLL)
#define GET_HI_I64(v) (int32_t)(((v) >> 32) & 0x00000000ffffffffLL)
#define GET_LO_U64(v) (uint32_t)((v) & 0x00000000ffffffffULL)
#define GET_HI_U64(v) (uint32_t)(((v) >> 32) & 0x00000000ffffffffULL)
#define SET_LO_I64(v,lo) (((v) & 0xffffffff00000000LL) | (int64_t)(lo))
#define SET_HI_I64(v,hi) (((v) & 0x00000000ffffffffLL) | ((int64_t)(hi) << 32))
#define MAKE_I64(hi,lo)  ((int64_t)(lo) | ((int64_t)(hi) << 32))
#define SET_LO_U64(v,lo) (((v) & 0xffffffff00000000ULL) | (uint64_t)(lo))
#define SET_HI_U64(v,hi) (((v) & 0x00000000ffffffffULL) | ((uint64_t)(hi) << 32))
#define MAKE_U64(hi,lo)  ((uint64_t)(lo) | ((uint64_t)(hi) << 32))


#define MENGINE_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define MENGINE_MIN(a,b)            (((a) < (b)) ? (a) : (b))


NAMESPACE_MENGINE_BEGIN

class MathUtils
{
public:
	static bool FloatEqual(_F32 a_Float1, _F32 a_Float2);
	
	template<typename T>
	static T Clamp(T a_Value, T a_Min, T a_Max);

	static _F32 Rsqrt(_F32 number);
	static _F32 Angle2Radian(_F32 angle);
	static _F32 Radian2Angle(_F32 Radian);
	static bool IsPowerOfTwo(_U32 value);
	static bool IsPowerOfTwo(_I32 value);

	static _U32 Log2(_U32 powerOfTwo);
	static _I32 Log2(_I32 powerOfTwo);

	static _U32 GetLeadingBit(_U32 value);
	static _U32 GetLeadingBit(_I32 value);
	static _U32 GetLeadingBit(_U64 value);
	static _U32 GetLeadingBit(_I64 value);

	static _U32 GetTrailingBit(_U32 value);
	static _U32 GetTrailingBit(_I32 value);
	static _U32 GetTrailingBit(_U64 value);
	static _U32 GetTrailingBit(_I64 value);

	static _U64 RoundUpToPowerOfTwo(_U32 value);
	static _U32 RoundDownToPowerOfTwo(_U32 value);
private:

	static const _U32 LeadingBitTable[];
	static const _U32 TrailingBitTable[];
};

template<typename T>
T MEngine::MathUtils::Clamp(T a_Value, T a_Min, T a_Max)
{
	MeAssertM(a_Min < a_Max, "Error Min & Max value in MathUtils::Clamp function");

	if (a_Value < a_Min)
	{
		return a_Min;
	}
	else if(a_Value > a_Max)
	{
		return a_Max;
	}
	return a_Value;
}

NAMESPACE_MENGINE_END
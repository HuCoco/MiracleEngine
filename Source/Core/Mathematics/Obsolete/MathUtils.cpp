#include <Core/Mathematics/MathUtils.h>


const _U32 MEngine::MathUtils::LeadingBitTable[] =
{
	0,  9,  1, 10, 13, 21,  2, 29,
	11, 14, 16, 18, 22, 25,  3, 30,
	8, 12, 20, 28, 15, 17, 24,  7,
	19, 27, 23,  6, 26,  5,  4, 31
};

const _U32 MEngine::MathUtils::TrailingBitTable[] =
{
	0,  1, 28,  2, 29, 14, 24,  3,
	30, 22, 20, 15, 25, 17,  4,  8,
	31, 27, 13, 23, 21, 19, 16,  7,
	26, 12, 18,  6, 11,  5, 10,  9
};


_F32 MEngine::MathUtils::Rsqrt(_F32 number)
{
	_U64 i;
	_F32 x2, y;
	const _F32 threehalfs = 1.5F;
	x2 = number * 0.5F;
	y = number;
	i = *reinterpret_cast<_I32*>(&y);
	i = RSQRT_NUMBER - (i >> 1);
	y = *reinterpret_cast<_F32*>(&i);
	y = y * (threehalfs - (x2 * y * y));
	return y;
}

_F32 MEngine::MathUtils::Angle2Radian(_F32 angle)
{
	return ANGLE_TO_RADIAN * angle;
}

_F32 MEngine::MathUtils::Radian2Angle(_F32 Radian)
{
	return RADIAN_TO_ANGLE * Radian;
}

bool MEngine::MathUtils::IsPowerOfTwo(_U32 value)
{
	return (value > 0) && ((value & (value - 1)) == 0);
}

bool MEngine::MathUtils::IsPowerOfTwo(_I32 value)
{
	return (value > 0) && ((value & (value - 1)) == 0);
}

_U32 MEngine::MathUtils::Log2(_U32 powerOfTwo)
{
	_U32 log2 = (powerOfTwo & BIT_1_GET_EVEN_POSITION) != 0;
	log2 |= ((powerOfTwo & BIT_16_GET_ODD_POSITION) != 0) << 4;
	log2 |= ((powerOfTwo & BIT_8_GET_ODD_POSITION) != 0) << 3;
	log2 |= ((powerOfTwo & BIT_4_GET_ODD_POSITION) != 0) << 2;
	log2 |= ((powerOfTwo & BIT_2_GET_ODD_POSITION) != 0) << 1;
	return log2;
}

_I32 MEngine::MathUtils::Log2(_I32 powerOfTwo)
{
	_U32 log2 = (powerOfTwo & BIT_1_GET_EVEN_POSITION) != 0;
	log2 |= ((powerOfTwo & BIT_16_GET_ODD_POSITION) != 0) << 4;
	log2 |= ((powerOfTwo & BIT_8_GET_ODD_POSITION) != 0) << 3;
	log2 |= ((powerOfTwo & BIT_4_GET_ODD_POSITION) != 0) << 2;
	log2 |= ((powerOfTwo & BIT_2_GET_ODD_POSITION) != 0) << 1;
	return static_cast<_I32>(log2);
}

_U32 MEngine::MathUtils::GetLeadingBit(_U32 value)
{
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	_U32 key = (value * LEADING_BIT_NUMBER) >> 27;
	return LeadingBitTable[key];
}

_U32 MEngine::MathUtils::GetLeadingBit(_I32 value)
{
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	_U32 key = (value * LEADING_BIT_NUMBER) >> 27;
	return LeadingBitTable[key];
}

_U32 MEngine::MathUtils::GetLeadingBit(_U64 value)
{
	_U32 v1 = GET_HI_U64(value);
	if (v1 != 0)
	{
		return GetLeadingBit(v1) + 32;
	}

	_U32 v0 = GET_LO_U64(value);
	return GetLeadingBit(v0);
}

_U32 MEngine::MathUtils::GetLeadingBit(_I64 value)
{
	_I32 v1 = GET_HI_I64(value);
	if (v1 != 0)
	{
		return GetLeadingBit(v1) + 32;
	}

	_I32 v0 = GET_LO_I64(value);
	return GetLeadingBit(v0);
}

_U32 MEngine::MathUtils::GetTrailingBit(_U32 value)
{
	_I32 const& iValue = reinterpret_cast<_I32 const&>(value);
	_U32 key = ((_U32)((iValue & -iValue) * TRAILING_BIT_NUMBER)) >> 27;
	return TrailingBitTable[key];
}

_U32 MEngine::MathUtils::GetTrailingBit(_I32 value)
{
	_U32 key = ((_U32)((value & -value) * TRAILING_BIT_NUMBER)) >> 27;
	return TrailingBitTable[key];
}


_U32 MEngine::MathUtils::GetTrailingBit(_U64 value)
{
	_U32 v0 = GET_LO_U64(value);
	if (v0 != 0)
	{
		return GetTrailingBit(v0);
	}

	_U32 v1 = GET_HI_U64(value);
	return GetTrailingBit(v1) + 32;
}

_U32 MEngine::MathUtils::GetTrailingBit(_I64 value)
{
	_I32 v0 = GET_LO_I64(value);
	if (v0 != 0)
	{
		return GetTrailingBit(v0);
	}

	_I32 v1 = GET_HI_I64(value);
	return GetTrailingBit(v1) + 32;
}

_U64 MEngine::MathUtils::RoundUpToPowerOfTwo(_U32 value)
{
	if (value > 0)
	{
		_I32 leading = GetLeadingBit(value);
		_U32 mask = (1 << leading);
		if ((value & ~mask) == 0)
		{
			return static_cast<uint64_t>(value);
		}
		else
		{
			return (static_cast<uint64_t>(mask) << 1);
		}
	}
	else
	{
		return GET_U64(1);
	}
}

_U32 MEngine::MathUtils::RoundDownToPowerOfTwo(_U32 value)
{
	if (value > 0)
	{
		_I32 leading = GetLeadingBit(value);
		_U32 mask = (1 << leading);
		return mask;
	}
	else
	{
		return 0;
	}
}

bool MEngine::MathUtils::FloatEqual(_F32 a_Float1, _F32 a_Float2)
{
	float diff = std::abs(a_Float1 - a_Float2);
	if (diff < 0.0001)
	{
		return true;
	}
	return false;
}

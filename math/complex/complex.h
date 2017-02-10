#pragma once

#include <type_traits>

template <typename ComponentType>
struct ComplexGeneric
{
	static_assert(std::is_floating_point<ComponentType>::value, "ComponentType must be a floating point type.");

	explicit ComplexGeneric(ComponentType imaginative = (ComponentType)0, ComponentType real = (ComponentType)0) :
		re(real),
		im(imaginative)
	{}

	ComplexGeneric operator* (const ComplexGeneric& other) const
	{
		return ComplexGeneric{re * other.re - im * other.im, re * other.im + im * other.re};
	}

	ComplexGeneric operator+ (const ComplexGeneric& other) const
	{

	}

	ComplexGeneric operator- (const ComplexGeneric& other) const
	{

	}

	ComponentType re;
	ComponentType im;
};

using ComplexF = ComplexGeneric<float>;
using ComplexD = ComplexGeneric<double>;
using ComplexL = ComplexGeneric<long double>;

using Complex = ComplexF;

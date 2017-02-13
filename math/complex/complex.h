#pragma once
#include "compiler/compiler_warnings_control.h"

#include <math.h>
#include <type_traits>

STORE_COMPILER_WARNINGS
DISABLE_MSVC_WARNING(4324) // 'ComplexGeneric<float>': structure was padded due to alignment specifier

template <typename ComponentType>
struct alignas(32) ComplexGeneric
{
	static_assert(std::is_floating_point<ComponentType>::value, "ComponentType must be a floating point type.");

	typedef ComponentType ScalarType;

	explicit ComplexGeneric(ComponentType real = (ComponentType)0, ComponentType imaginative = (ComponentType)0) :
		re(real),
		im(imaginative)
	{}

	ComplexGeneric operator* (const ComplexGeneric& other) const
	{
		return ComplexGeneric(*this) *= other;
	}

	ComplexGeneric& operator*= (const ComplexGeneric& other)
	{
		const auto new_re = re * other.re - im * other.im;

		im = re * other.im + im * other.re;
		re = new_re;

		return *this;
	}

	// Scalar multiplication
	ComplexGeneric operator* (const ComponentType scalar) const
	{
		return ComplexGeneric(*this) *= scalar;
	}

	ComplexGeneric& operator*= (const ComponentType scalar)
	{
		im *= scalar;
		re *= scalar;

		return *this;
	}

	ComplexGeneric operator/ (const ComplexGeneric& other) const
	{
		return ComplexGeneric(*this) /= other;
	}

	ComplexGeneric& operator/= (const ComplexGeneric& other)
	{
		const auto denominator = other.re * other.re + other.im * other.im;

		const auto new_re = (re * other.re + im * other.im) / denominator;

		im = (im * other.re - re * other.im) / denominator;
		re = new_re;
		return *this;
	}

	ComplexGeneric operator+ (const ComplexGeneric& other) const
	{
		return ComplexGeneric(*this) += other;
	}

	ComplexGeneric& operator+= (const ComplexGeneric& other)
	{
		re += other.re;
		im += other.im;
		return *this;
	}

	ComplexGeneric operator- (const ComplexGeneric& other) const
	{
		return ComplexGeneric(*this) -= other;
	}

	ComplexGeneric& operator-= (const ComplexGeneric& other)
	{
		re -= other.re;
		im -= other.im;
		return *this;
	}

	ComponentType modulus() const
	{
		return sqrt(modulusSqr());
	}

	ComponentType modulusSqr() const
	{
		return re * re + im * im;
	}

	bool operator== (const ComplexGeneric& other) const
	{
		return re == other.re && im == other.im;
	}

	bool operator!= (const ComplexGeneric& other) const
	{
		return re != other.re && im != other.im;
	}

	ComponentType re;
	ComponentType im;
};

RESTORE_COMPILER_WARNINGS

using ComplexF = ComplexGeneric<float>;
using ComplexD = ComplexGeneric<double>;
using ComplexL = ComplexGeneric<long double>;

using Complex = ComplexD;

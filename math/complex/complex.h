#pragma once

#include <math.h>
#include <type_traits>

template <typename ComponentType>
struct ComplexGeneric
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
		re = re * other.re - im * other.im;
		im = re * other.im + im * other.re;
		return *this;
	}

	ComplexGeneric operator/ (const ComplexGeneric& other) const
	{
		return ComplexGeneric(*this) /= other;
	}

	ComplexGeneric& operator/= (const ComplexGeneric& other)
	{
		const auto denominator = other.re * other.re + other.im * other.im;
		re = (re * other.re + im * other.im) / denominator;
		im = (im * other.re - re * other.im) / denominator;
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
		return sqrt(re * re + im * im);
	}

	ComponentType re;
	ComponentType im;
};

using ComplexF = ComplexGeneric<float>;
using ComplexD = ComplexGeneric<double>;
using ComplexL = ComplexGeneric<long double>;

using Complex = ComplexF;

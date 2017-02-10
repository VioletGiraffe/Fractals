#include "cmandelbrotset.h"

#include <limits>


size_t CMandelbrotSet::checkPoint(const Complex &c, const size_t iterationsLimit) const
{
	constexpr auto bound = Complex::ScalarType(1e20);
	constexpr auto scale = Complex::ScalarType(0.02);

	Complex z {0, 0};
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		z = z * z + c * scale;
		if (z.modulus() > bound)
			return i; // Unbound
	}

	return iterationsLimit + 1; // Bound
}

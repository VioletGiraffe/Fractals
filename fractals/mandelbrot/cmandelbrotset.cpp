#include "cmandelbrotset.h"

#include <limits>


size_t CMandelbrotSet::checkPoint(const Complex &c, const size_t iterationsLimit) const
{
	constexpr auto bound = typename Complex::ScalarType(1e20);

	Complex z {0, 0};
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		z = z * z + c;
		if (z.modulus() > bound)
			return i; // Unbound
	}

	return iterationsLimit + 1; // Bound
}

#include "cmandelbrotset.h"

#include <limits>

#define fp_literal(x) Complex::ScalarType(x)

size_t CMandelbrotSet::checkPoint(const Complex &c, Complex::ScalarType zoomFactor, const size_t iterationsLimit) const
{
	constexpr auto bound = fp_literal(1e20);
	constexpr auto baseScale = fp_literal(0.02);

	const auto scale = baseScale + zoomFactor * fp_literal(0.1) * baseScale;

	Complex z {0, 0};
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		z = z * z + c * scale;
		if (z.modulus() > bound)
			return i; // Unbound
	}

	return iterationsLimit + 1; // Bound
}

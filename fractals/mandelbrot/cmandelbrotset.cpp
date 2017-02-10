#include "cmandelbrotset.h"

#include <limits>

#define fp_literal(x) Complex::ScalarType(x)

size_t CMandelbrotSet::checkPoint(const Complex &c, Complex::ScalarType zoomFactor, const size_t iterationsLimit) const
{
	constexpr auto bound = fp_literal(1e10);
	constexpr auto baseScale = fp_literal(0.02);

	const auto scale = baseScale + zoomFactor * fp_literal(0.1) * baseScale;
	const auto scaledC = c * scale;

	Complex z {0, 0};
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		// z = z^2 + c
		z *= z;
		z += scaledC;

		if (z.modulusSqr() > bound)
			return i; // Unbound
	}

	return iterationsLimit + 1; // Bound
}

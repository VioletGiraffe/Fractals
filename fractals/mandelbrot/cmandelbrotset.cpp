#include "cmandelbrotset.h"

#include <limits>

#define to_fp(x) Complex::ScalarType(x)

Complex::ScalarType CMandelbrotSet::checkPoint(const Complex &c, Complex::ScalarType zoomFactor, const size_t iterationsLimit) const
{
	constexpr auto bound = to_fp(1e10);
	constexpr auto baseScale = to_fp(0.02);

	const auto scale = baseScale * zoomFactor;
	const auto scaledC = c * scale;

	Complex z {0, 0};
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		// z = z^2 + c
		z *= z;
		z += scaledC;

		if (z.modulusSqr() > bound)
			return to_fp(i + 1) / iterationsLimit; // Unbound
	}

	return to_fp(0.0); // Bound
}

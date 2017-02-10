#include "cmandelbrotset.h"
#include "math/math.hpp"

#include <limits>

#define to_fp(x) Complex::ScalarType(x)

// https://en.wikipedia.org/wiki/Mandelbrot_set#Optimizations
inline bool pointBelongsToCardioid(const Complex &pt)
{
	const auto x_offset = pt.re - to_fp(0.25);
	const auto im_sqr = pt.im * pt.im;

	const auto q = x_offset * x_offset + im_sqr;
	return q * (q + x_offset) < to_fp(0.25) * im_sqr;
}

Complex::ScalarType CMandelbrotSet::checkPoint(const Complex &c, Complex::ScalarType zoomFactor, const size_t iterationsLimit) const
{
	constexpr auto bound = to_fp(1e10);
	constexpr auto baseScale = to_fp(0.005);

	const auto scale = baseScale * zoomFactor;
	const auto scaledC = c * scale;

	if (pointBelongsToCardioid(scaledC))
		return to_fp(0.0); // Belongs to the set

	Complex z {0, 0};

	Complex prevValues[2];
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		// z = z^2 + c
		prevValues[0] = prevValues[1];
		prevValues[1] = z;

		z *= z;
		z += scaledC;

		if (z == prevValues[0]) // Cycle of period 2
			return to_fp(0.0); // Belongs to the set

		if (z.modulusSqr() > bound)
			return pow(to_fp(i + 1) / iterationsLimit, to_fp(0.45)); // Unbound - does not belong to the set
	}

	return to_fp(0.0); // Belongs to the set
}

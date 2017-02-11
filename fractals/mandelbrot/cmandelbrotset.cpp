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

size_t CMandelbrotSet::checkPoint(const Complex &c, Complex::ScalarType zoomFactor, const size_t iterationsLimit) const
{
	constexpr auto bound = to_fp(15); // 4.0 (2^2) should be enough since no point with magnitude over 2.0 can be part of the set, but this value affects the coloring of the outside regions
	constexpr auto baseScale = to_fp(0.005);

	const auto scale = baseScale * zoomFactor;
	const auto scaledC = c * scale;

	if (pointBelongsToCardioid(scaledC))
		return 0; // Belongs to the set

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
			return 0; // Belongs to the set

		if (z.modulusSqr() > bound)
			return i;
	}

	return 0; // Belongs to the set
}

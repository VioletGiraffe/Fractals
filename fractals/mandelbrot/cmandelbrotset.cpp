#include "cmandelbrotset.h"
#include "math/math.hpp"

DISABLE_COMPILER_WARNINGS
#include <CL/CL.hpp>
RESTORE_COMPILER_WARNINGS

#include <limits>

#define to_fp(x) Complex::ScalarType(x)

CMandelbrotSet::CMandelbrotSet()
{
// 	_zoom = to_fp(0.00145);
// 	_offset = Complex(to_fp(0.0), to_fp(0.0));

	_zoom = to_fp(1.06825e-08);
	_offset = Complex(to_fp(0.4376), to_fp(0.210502));
}

// https://en.wikipedia.org/wiki/Mandelbrot_set#Optimizations
inline bool pointBelongsToCardioid(const Complex &pt)
{
	const auto x_offset = pt.re - to_fp(0.25);
	const auto im_sqr = pt.im * pt.im;

	const auto q = x_offset * x_offset + im_sqr;
	return q * (q + x_offset) < to_fp(0.25) * im_sqr;
}

size_t CMandelbrotSet::checkPoint(const Complex& point, const size_t iterationsLimit) const
{
	const auto scaledPoint = point * _zoom + _offset;

	if (pointBelongsToCardioid(scaledPoint))
		return 0; // Belongs to the set

	Complex z {0, 0};

	Complex prevValues[3];
	for (size_t i = 0; i < iterationsLimit; ++i)
	{
		iterate(z, scaledPoint);

		if (z == prevValues[0]) // Cycle of period 2
			return 0; // Belongs to the set

		prevValues[0] = prevValues[1];
		prevValues[1] = z;

		constexpr auto bound = to_fp(15); // 4.0 (2^2) should be enough since no point with magnitude over 2.0 can be part of the set, but this value affects the coloring of the outside regions
		if (z.modulusSqr() > bound)
			return i;
	}

	return 0; // Belongs to the set
}

void CMandelbrotSet::iterate(Complex& z, const Complex& c) const
{
	// z = z^2 + c

	z *= z;
	z += c;
}

#include "cburningshipset.h"

#define to_fp(x) Complex::ScalarType(x)

CBurningShipSet::CBurningShipSet()
{
	_zoom = to_fp(0.00145);
	_offset = Complex(to_fp(0.0), to_fp(0.0));
}

void CBurningShipSet::iterate(Complex& z, const Complex& c) const
{
	z.re = fabs(z.re);
	z.im = fabs(z.im);

	z *= z;
	z += c;
}

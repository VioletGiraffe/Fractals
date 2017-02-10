#pragma once

#include "complex/complex.h"

class CFractal
{
public:
	inline virtual ~CFractal() {}

	// Returns the number of iterations in which the point left the bounds
	virtual size_t checkPoint(const Complex& c, Complex::ScalarType zoomFactor, const size_t iterationsLimit = 1000) const = 0;
};

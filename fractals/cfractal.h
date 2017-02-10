#pragma once

#include "complex/complex.h"

class CFractal
{
public:
	inline virtual ~CFractal() {}

	// Returns the metric of this point in the [0.0; 1.0] range.
	virtual Complex::ScalarType checkPoint(const Complex& c, Complex::ScalarType zoomFactor, const size_t iterationsLimit = 1000) const = 0;
};

#pragma once

#include "../cfractal.h"

class CMandelbrotSet : public CFractal
{
public:
	// Returns the number of iterations in which the point left the bounds
	size_t checkPoint(const Complex& c, Complex::ScalarType zoomFactor, const size_t iterationsLimit = 1000) const override;
};

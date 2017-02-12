#pragma once

#include "../cfractal.h"

class CMandelbrotSet : public CFractal
{
public:
	CMandelbrotSet();

	// Returns the metric of this point in the [0.0; 1.0] range.
	size_t checkPoint(const Complex& point, const size_t iterationsLimit = 1000) const override;
};

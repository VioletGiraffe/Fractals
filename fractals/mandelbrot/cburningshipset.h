#pragma once

#include "cmandelbrotset.h"

class CBurningShipSet : public CMandelbrotSet
{
public:
	CBurningShipSet();

protected:
	void iterate(Complex& z, const Complex& c) const override;
};

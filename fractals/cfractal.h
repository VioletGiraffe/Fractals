#pragma once

#include "complex/complex.h"

STORE_COMPILER_WARNINGS
DISABLE_MSVC_WARNING(4324)

class CFractal
{
public:
	inline virtual ~CFractal() {}

	// Returns the metric of this point in the [0.0; 1.0] range.
	virtual size_t checkPoint(const Complex& point, const size_t iterationsLimit = 1000) const = 0;

	inline Complex::ScalarType zoom() const {
		return _zoom;
	}

	inline void setZoom(const Complex::ScalarType newZoom) {
		_zoom = newZoom;
	}

	inline Complex offset() const {
		return _offset;
	}

	inline void setOffset(const Complex& newOffset) {
		_offset = newOffset;
	}

	void* operator new(size_t n)
	{
		return _aligned_malloc(n, alignof(Complex));
	}

	void operator delete(void* p)
	{
		_aligned_free(p);
	}

protected:
	Complex _offset;
	Complex::ScalarType _zoom;
};

RESTORE_COMPILER_WARNINGS

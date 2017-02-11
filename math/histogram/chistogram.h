#pragma once

#include <assert.h>
#include "math/math.hpp"

template <typename T, size_t MaxValue>
class CHistogram
{
public:
	void addSample(const T sample)
	{
		assert(Math::isInRange(sample, T(0), T(MaxValue - 1)));

		++_bands[sample];
		++_numSamplesCollected;
	}

	size_t numSamplesTotal() const
	{
		return _numSamplesCollected;
	}

	size_t numSamplesForBand(const size_t bandIndex) const
	{
		return _bands[bandIndex];
	}

	size_t numSamplesForValue(const T value) const
	{
		return _bands[value];
	}

private:
	size_t _bands[MaxValue] = {0};
	size_t _numSamplesCollected = 0;
};

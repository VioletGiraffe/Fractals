#pragma once

#include <assert.h>
#include <atomic>

template <typename T, size_t UpperBound>
class CHistogram
{
public:
	// Allowed range: [0; UpperBound)
	void addSample(const T sample)
	{
		assert(sample >= T(0) && sample < T(UpperBound));

		++_bands[sample];
		++_numSamplesCollected;
	}

	size_t numSamplesTotal() const
	{
		return _numSamplesCollected;
	}

	size_t numSamplesForValue(const T value) const
	{
		return _bands[value];
	}

	constexpr size_t numBands() const
	{
		return UpperBound;
	}

private:
	std::atomic<size_t> _bands[UpperBound] = {0};
	std::atomic<size_t> _numSamplesCollected = 0;
};

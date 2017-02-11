#include "cfractalwidget.h"
#include "cfractal.h"
#include "system/ctimeelapsed.h"
#include "histogram/chistogram.h"

DISABLE_COMPILER_WARNINGS
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
RESTORE_COMPILER_WARNINGS

#include <omp.h>

CFractalWidget::CFractalWidget(QWidget *parent) : QWidget(parent)
{
}

void CFractalWidget::paintEvent(QPaintEvent *event)
{
	event->accept();

	if (!_fractal)
		return;

	CTimeElapsed timer(true);

	QImage bitmap(size(), QImage::Format_RGB32);

	const int w = width(), h = height();

	constexpr size_t maxNumIterations = 500;
	CHistogram<size_t, maxNumIterations> histogram;

	#pragma omp parallel for schedule(static)
	for (int y = 0; y < h; ++y)
	{
		const auto resultsLine = _fractalFunctionValues.get() + y * w;

		for (int x = 0; x < w; ++x)
		{
			const auto result = _fractal->checkPoint(Complex{Complex::ScalarType(x - w / 2), Complex::ScalarType(y - h / 2)}, _zoomFactor, maxNumIterations);
			histogram.addSample(result);
			resultsLine[x] = result;
		}
	}

	for (int y = 0; y < h; ++y)
	{
		const auto valuesLine = _fractalFunctionValues.get() + y * w;
		uint32_t* const scanline = (uint32_t*)bitmap.scanLine(y);

		for (int x = 0; x < w; ++x)
		{
			const auto value = valuesLine[x];
			const float totalNumSamples = histogram.numSamplesTotal();
			if (value > 0)
			{
				float hue = 0.0f;
				for (size_t i = 0; i < value; ++i)
					hue += histogram.numSamplesForValue(i) / totalNumSamples;

				scanline[x] = QColor::fromHsv((int)hue * 360, 255, 255).rgba();
			}
			else
				scanline[x] = 0xFF000000;
		}
	}

	qDebug() << "Calculating the fractal took" << timer.elapsed() << "ms";

	QPainter painter(this);
	painter.drawImage(0, 0, bitmap);
}

void CFractalWidget::wheelEvent(QWheelEvent *event)
{
	event->accept();

	if (event->angleDelta().y() != 0)
	{
		const float delta = event->angleDelta().y() / 8.0f / 15.0f;
		if (_zoomFactor >= 1.0f && delta < 0.0f)
			_zoomFactor *= pow(1.1f, -delta);
		else
			_zoomFactor /= pow(1.1f, delta);

		update();
	}
}

void CFractalWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	_fractalFunctionValues = std::make_unique<size_t[]>(event->size().width() * event->size().height());
}

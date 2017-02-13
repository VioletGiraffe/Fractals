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

inline QDebug& operator<<(QDebug& stream, const Complex& c)
{
	stream << QPointF(c.re, c.im);
	return stream;
}

CFractalWidget::CFractalWidget(QWidget *parent) : QWidget(parent)
{
	_palette.reserve(360);
	for (int i = 0; i < 360; ++i)
		_palette.emplace_back(QColor::fromHsv(i, 255, 255).rgb());

	_mouseDragTimer.start(200);
	connect(&_mouseDragTimer, &QTimer::timeout, this, &CFractalWidget::processMouseDrag);
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
	CHistogram<size_t, maxNumIterations-1> histogram; // -1 because we're not putting zeros in the histogram

	#pragma omp parallel for schedule(static)
	for (int y = 0; y < h; ++y)
	{
		const auto resultsLine = _fractalFunctionValues.get() + y * w;

		for (int x = 0; x < w; ++x)
		{
			const auto result = _fractal->checkPoint(Complex{Complex::ScalarType(x - w / 2), Complex::ScalarType(y - h / 2)}, maxNumIterations);
			if (result > 0)
				histogram.addSample(result - 1); // -1 because we're not putting zeros in the histogram
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
			const size_t totalNumSamples = histogram.numSamplesTotal();
			if (value > 0)
			{
				size_t numberOfPointsWithValueUpToCurrent = 0;
				for (size_t i = 0, max = value - 1; i < max; ++i) // -1 because we're not putting zeros in the histogram
					numberOfPointsWithValueUpToCurrent += histogram.numSamplesForValue(i);

				scanline[x] = _palette[static_cast<size_t>(numberOfPointsWithValueUpToCurrent / (float)totalNumSamples * 360.0f)];
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
	if (!_fractal)
		return;

	if (event->angleDelta().y() != 0)
	{
		auto zoomFactor = _fractal->zoom();
		const float delta = event->angleDelta().y() / 8.0f / 15.0f;
		if (delta < 0.0f)
			zoomFactor *= pow(1.1f, -delta);
		else
			zoomFactor /= pow(1.1f, delta);

		_fractal->setZoom(zoomFactor);

		qDebug() << "Zoom:" << zoomFactor;
		qDebug() << "Offset:" << _fractal->offset();

		update();
	}
}

void CFractalWidget::mouseMoveEvent(QMouseEvent *event)
{
	qDebug() << "pos:" << event->pos() << "\noffset:" << event->pos() - _prevMousePos << "\naccumulated:" << _accumulatedMouseOffset;
	if (event->buttons() & Qt::LeftButton)
		_accumulatedMouseOffset += event->pos() - _prevMousePos;

	_prevMousePos = event->pos();
}

// Mouse move events are only displatched to the widget if a mouse button is pressed, so it's necessary to update the prev. cursor position upon butoon press to aboid the image jumping around
void CFractalWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		_prevMousePos = event->pos();
}

void CFractalWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);

	_fractalFunctionValues = std::make_unique<size_t[]>(event->size().width() * event->size().height());
}

void CFractalWidget::processMouseDrag()
{
	if (_accumulatedMouseOffset.manhattanLength() == 0)
		return;

	const auto newOffset = _fractal->offset() + Complex(-(Complex::ScalarType)_accumulatedMouseOffset.x(), -(Complex::ScalarType)_accumulatedMouseOffset.y()) * _fractal->zoom();
	qDebug() << "Zoom:" << _fractal->zoom();
	qDebug() << "Offset:" << newOffset;
	_fractal->setOffset(newOffset);
	update();

	_accumulatedMouseOffset = QPoint(0, 0);
}

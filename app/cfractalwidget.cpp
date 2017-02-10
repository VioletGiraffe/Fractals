#include "cfractalwidget.h"
#include "cfractal.h"
#include "system/ctimeelapsed.h"

DISABLE_COMPILER_WARNINGS
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
RESTORE_COMPILER_WARNINGS

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

	for (int y = 0, yMax = height(); y < yMax; ++y)
	{
		uint32_t* const scanline = (uint32_t*)bitmap.scanLine(y);
		for (int x = 0, xMax = width(); x < xMax; ++x)
		{
			constexpr size_t maxIterations = 500;
			const auto result = _fractal->checkPoint(Complex{Complex::ScalarType(x - xMax / 2), Complex::ScalarType(y - yMax / 2)}, _zoomFactor, maxIterations);
			if (result > 0.0f)
			{
				const uint8_t shade = 0xFF * result;
				scanline[x] = 0xFF000000 | (shade << 16) | shade;
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

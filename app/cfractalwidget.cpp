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

	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);

	if (!_fractal)
		return;

	CTimeElapsed timer(true);

	for (int y = event->rect().top(), yMax = event->rect().bottom(); y < yMax; ++y)
	{
		for (int x = event->rect().left(), xMax = event->rect().right(); x < xMax; ++x)
		{
			constexpr size_t maxIterations = 500;
			const auto result = _fractal->checkPoint(Complex{Complex::ScalarType(x - xMax / 2), Complex::ScalarType(y - yMax / 2)}, _zoomFactor, maxIterations);
			if (result > 0.0f)
			{
				painter.setPen(QColor(255 * result, 0, 255 * result));
				painter.drawPoint(x, y);
			}
		}
	}

	qDebug() << "Painting the fractal took" << timer.elapsed() << "ms";
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

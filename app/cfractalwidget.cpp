#include "cfractalwidget.h"
#include "cfractal.h"

DISABLE_COMPILER_WARNINGS
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
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

	for (int y = event->rect().top(), yMax = event->rect().bottom(); y < yMax; ++y)
	{
		for (int x = event->rect().left(), xMax = event->rect().right(); x < xMax; ++x)
		{
			constexpr size_t maxIterations = 1000;
			const auto result = _fractal->checkPoint(Complex{Complex::ScalarType(x), Complex::ScalarType(y)}, maxIterations);
			if (result > maxIterations)
			{
				painter.setPen(Qt::yellow);
			}
			else
				painter.setPen(QColor(255 * result / maxIterations, 0, 255 * result / maxIterations));

			painter.drawPoint(x, y);
		}
	}
}

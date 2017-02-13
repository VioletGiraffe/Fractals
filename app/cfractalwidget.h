#pragma once

#include "compiler/compiler_warnings_control.h"

DISABLE_COMPILER_WARNINGS
#include <QTimer>
#include <QWidget>
RESTORE_COMPILER_WARNINGS

#include <memory>
#include <vector>

class CFractal;

class CFractalWidget : public QWidget
{
public:
	explicit CFractalWidget(QWidget* parent = 0);

	template <typename FractalType>
	void setFractal() {
		_fractal = std::make_unique<FractalType>();
		update();
	}

protected:
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

private:
	void processMouseDrag();

private:
	std::unique_ptr<CFractal> _fractal;
	std::unique_ptr<size_t[]> _fractalFunctionValues;

	std::vector<uint32_t> _palette;

	QTimer _mouseDragTimer;

	QPoint _prevMousePos;
	QPoint _accumulatedMouseOffset;
};

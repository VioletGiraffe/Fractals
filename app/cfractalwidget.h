#pragma once

#include "compiler/compiler_warnings_control.h"

DISABLE_COMPILER_WARNINGS
#include <QWidget>
RESTORE_COMPILER_WARNINGS

#include <memory>

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

private:
	std::unique_ptr<CFractal> _fractal;

	float _zoomFactor = 1.0f;
};

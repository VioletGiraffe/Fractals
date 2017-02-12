#pragma once

#include "compiler/compiler_warnings_control.h"
#include "complex/complex.h"

DISABLE_COMPILER_WARNINGS
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
	void resizeEvent(QResizeEvent *event) override;

private:
	std::unique_ptr<CFractal> _fractal;
	std::unique_ptr<size_t[]> _fractalFunctionValues;

	float _zoomFactor = 1.0f;

	std::vector<uint32_t> _palette;
};

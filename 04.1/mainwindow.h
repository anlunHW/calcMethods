#pragma once

#include <QMainWindow>
#include "inverseFunctionInterpolation.h"

class InverseFunctionInterpolation;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	void prepareProblemTable();
	void prepareFirstMethodTable(int polynomDegree);

	Ui::MainWindow *ui;
	InverseFunctionInterpolation* interpolator;

private slots:
	void interpolate();
};

#include "mainWindow.h"
#include "ui_mainWindow.h"

#include <QMessageBox>
#include <cmath>

#include "function.h"

#include "integralCalc.h"
#include "middleRectangleIntegralCalc.h"
#include "trapeziumIntegralCalc.h"
#include "simpsonIntegralCalc.h"

MainWindow::MainWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::MainWindow) {
	ui->setupUi(this);

	connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calculate()));
	ui->functionLabel->setText(Function::funcString());
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::calculate() {
	double a = ui->aEdit->text().toDouble();
	double b = ui->bEdit->text().toDouble();

	int m = ui->mEdit->text().toInt();
	int l = ui->lEdit->text().toInt();

	if ((l <= 1) || (m <= 1) || (a >= b)) {
		QMessageBox msg;
		msg.setText("Error in problem parameters!");
		msg.exec();
		return;
	}

	double trueIntegralValue = Function::funcIntegral(b) - Function::funcIntegral(a);

	IntegralCalc* integralCalcs[3];
	integralCalcs[0] = new MiddleRectangleIntegralCalc<Function>(a, b);
	integralCalcs[1] = new TrapeziumIntegralCalc<Function>(a, b);
	integralCalcs[2] = new SimpsonIntegralCalc<Function>(a, b);

	double s_m[3];
	double s_lm[3];
	double i_ad[3];
	for (int i = 0; i < 3; i++) {
		s_m[i] = integralCalcs[i]->calculateIntegral(m);
		s_lm[i] = integralCalcs[i]->calculateIntegral(l * m);
		i_ad[i] = s_lm[i] + integralCalcs[i]->mainCalcError(m, l);
	}

	int curColumn = 0;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(s_m[i]));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}
	curColumn++;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(fabs(trueIntegralValue - s_m[i])));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}
	curColumn++;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(s_lm[i]));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}
	curColumn++;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(fabs(trueIntegralValue - s_lm[i])));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}
	curColumn++;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(i_ad[i]));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}
	curColumn++;
	for (int i = 0; i < 3; i++) {
		QTableWidgetItem* curItem = new QTableWidgetItem(QString::number(fabs(trueIntegralValue - i_ad[i])));
		curItem->setFlags(Qt::ItemIsEnabled);
		ui->resultTable->setItem(i, curColumn, curItem);
	}

	delete integralCalcs[0];
	delete integralCalcs[1];
	delete integralCalcs[2];
}

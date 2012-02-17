#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QList>
#include <QPair>
#include <QTableWidgetItem>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(interpolate()));

	ui->funcLabel->setText(FuncClass::funcStr());

	//ui->firstResultLayout
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::interpolate() {
	double startPoint = ui->startPointEdit->text().toDouble();
	int nodeNumber = ui->lastNodeNumberEdit->text().toInt() + 1;
	double nodeStep = ui->nodeStepEdit->text().toDouble();

	interpolator = InverseFunctionInterpolation::createInterpolator(startPoint, nodeNumber, nodeStep);

	if (interpolator == 0) {
		QMessageBox error;
		error.setText("Error in problem parameters!");
		error.exec();
		return;
	}

	if (!interpolator->checkMonotony(0, nodeNumber)) {
		QMessageBox error;
		error.setText("Function isn't monotony on these nodes!");
		error.exec();

		delete interpolator;
		return;
	}

	prepareProblemTable();

	double interPoint = ui->interPointEdit->text().toDouble();
	int polynomDegree = ui->firstMethodPolynomDegreeEdit->text().toInt();
	double firstMethodResult = interpolator->interpolateInverseFunction_1(interPoint, polynomDegree);
	prepareFirstMethodTable(polynomDegree);

	ui->firstResultX_label->setText(QString::number(firstMethodResult));
	ui->firstResultDisperancy_label->setText(QString::number(fabs(FuncClass::func(firstMethodResult) - interPoint)));

	//second method workspace
	interpolator->setSecondMethodPolynomDegree(ui->secondMethodPolynomDegreeEdit->text().toInt());
	interpolator->setSecondMethodAccurancy(ui->secondMethodAccuracyEdit->text().toDouble());
	interpolator->setInterpolationValue(interPoint);
	double secondMethodResult = interpolator->interpolateInverseFunction_2();

	ui->secondMethodResultX_label->setText(QString::number(secondMethodResult));
	ui->secondMethodDisperancy_label->setText(QString::number(fabs(FuncClass::func(secondMethodResult) - interPoint)));

	if (interpolator)
		delete interpolator;
}

void MainWindow::prepareProblemTable() {
	ui->tableWidget->clear();

	QList< QPair<double, double> > tableContent = interpolator->nodeTable();

	ui->tableWidget->setRowCount(interpolator->nodeNumber());
	ui->tableWidget->setColumnCount(2);

	QPair<double, double> curLine;
	int curRow = 0;
	foreach (curLine, tableContent) {
		QTableWidgetItem* curItemNode = new QTableWidgetItem(QString::number(curLine.first));
		curItemNode->setFlags(Qt::ItemIsEnabled);

		QTableWidgetItem* curItemValue = new QTableWidgetItem(QString::number(curLine.second));
		curItemValue->setFlags(Qt::ItemIsEnabled);

		ui->tableWidget->setItem(curRow, 0, curItemNode);
		ui->tableWidget->setItem(curRow, 1, curItemValue);

		curRow++;
	}
}


void MainWindow::prepareFirstMethodTable(int polynomDegree) {
	ui->tableWidget_2->clear();

	QVector< QPair<double, double> > tableContent = interpolator->firstMethodTable();

	ui->tableWidget_2->setRowCount(polynomDegree + 1);
	ui->tableWidget_2->setColumnCount(2);

	QPair<double, double> curLine;
	int curRow = 0;
	foreach (curLine, tableContent) {
		QTableWidgetItem* curItemNode = new QTableWidgetItem(QString::number(curLine.first));
		curItemNode->setFlags(Qt::ItemIsEnabled);

		QTableWidgetItem* curItemValue = new QTableWidgetItem(QString::number(curLine.second));
		curItemValue->setFlags(Qt::ItemIsEnabled);

		ui->tableWidget_2->setItem(curRow, 0, curItemNode);
		ui->tableWidget_2->setItem(curRow, 1, curItemValue);

		curRow++;
	}
}

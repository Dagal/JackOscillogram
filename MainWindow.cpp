#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	qDebug("Création de la fenêtre principale.");
	QWidget* widget = new QWidget(this);
	QVBoxLayout* box = new QVBoxLayout;
//	box.setParent(&widget);
	oscillo1 = new QJackOscillogram(this);
	box->addWidget(oscillo1);
	oscillo2 = new QJackOscillogram(this);
	box->addWidget(oscillo2);
	widget->setLayout(box);
	setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
	qDebug("Destruction de la fenêtre principale");
}


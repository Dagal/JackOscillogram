#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mCJackClient = new CJackClient("QJackOscillogram");
	qDebug("MainWindow: Création d'un client Jack");

	QWidget* widget = new QWidget(this);
	qDebug("MainWindow: Création du widget principal");
	QVBoxLayout* box = new QVBoxLayout;
//	box.setParent(&widget);
	oscillo1 = new QJackOscillogram(mCJackClient, this);
	qDebug() << "MainWindow: Création d'un widget oscillogram ("
					 << oscillo1
					 << ")";
	box->addWidget(oscillo1);
//	oscillo2 = new QJackOscillogram(mCJackClient, this);
//	box->addWidget(oscillo2);
	widget->setLayout(box);
	setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
	qDebug("Destruction de la fenêtre principale");
}


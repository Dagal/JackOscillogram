#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	mCJackClient = new CJackClient("QJackOscillogram");
	// TODO: Création des ports d'entrée
	qDebug("MainWindow: Création d'un client Jack");

	QWidget* widget = new QWidget(this);
	qDebug("MainWindow: Création du widget principal");
	QVBoxLayout* box = new QVBoxLayout;

	oscillo1 = new QJackOscillogram(mCJackClient, "Input 1", this);
	// TODO: Liaison à un port à la place du client
	qDebug() << "MainWindow: Création d'un widget oscillogram ("
					 << oscillo1
					 << ")";
	box->addWidget(oscillo1);

	oscillo2 = new QJackOscillogram(mCJackClient, "Input 2", this);
	qDebug() << "MainWindow: Création d'un widget oscillogram ("
					 << oscillo2
					 << ")";
	box->addWidget(oscillo2);

	widget->setLayout(box);
	setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
	qDebug("Destruction de la fenêtre principale");
}


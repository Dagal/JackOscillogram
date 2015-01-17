#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QVBoxLayout>

#include "QJackOscillogram.h"

#include <jack/jack.h>

#include "CJackClient.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:

private:
	// Le client Jack
	CJackClient* mCJackClient;
	QJackOscillogram* oscillo1;
	QJackOscillogram* oscillo2;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QDebug>

#include <jack/jack.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	static int staticProcess(jack_nframes_t nframes, void* arg);
	int process(jack_nframes_t nframes);
	static int staticFrameRateChanged(jack_nframes_t nframes, void* arg);
	int frameRateChanged(jack_nframes_t nframes);
	static int staticBufferSizeChanged(jack_nframes_t nframes, void* arg);
	int bufferSizeChanged(jack_nframes_t nframes);
	void paintEvent(QPaintEvent* ev);

private slots:
	void startingBlock();

private:
	QTimer mTimer1;
	jack_client_t* mClientJack;
	jack_port_t* mPortJack;
	jack_default_audio_sample_t* mBufferJack;
	QVector<float> mBufferDatagram;
	jack_nframes_t mJackFrames;
	jack_nframes_t mJackBufferSize;
};

#endif // MAINWINDOW_H

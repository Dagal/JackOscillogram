#ifndef QJACKOSCILLOGRAM_H
#define QJACKOSCILLOGRAM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <jack/jack.h>

class QJackOscillogram : public QWidget
{
	Q_OBJECT
public:
	explicit QJackOscillogram(QWidget *parent = 0);
	~QJackOscillogram();

	static int staticProcess(jack_nframes_t nframes, void* arg);
	int process(jack_nframes_t nframes);
	static int staticFrameRateChanged(jack_nframes_t nframes, void* arg);
	int frameRateChanged(jack_nframes_t nframes);
	static int staticBufferSizeChanged(jack_nframes_t nframes, void* arg);
	int bufferSizeChanged(jack_nframes_t nframes);
	void updateJackBuffer(jack_default_audio_sample_t* bufferJack);
	void paintEvent(QPaintEvent* ev);

signals:

public slots:
	void startingBlock();

private:
	QTimer mTimer1;
	jack_client_t* mJackClient;
	jack_port_t* mJackPort;
	jack_default_audio_sample_t* mJackBuffer;
	QVector<qreal> mDatagramBuffer;
	jack_nframes_t mJackFPS;
	jack_nframes_t mJackBufferSize;
};

#endif // QJACKOSCILLOGRAM_H

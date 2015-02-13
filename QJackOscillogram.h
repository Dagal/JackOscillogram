#ifndef QJACKOSCILLOGRAM_H
#define QJACKOSCILLOGRAM_H

#include <QWidget>
#include "IJackClient.h"
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <jack/jack.h>

class QJackOscillogram : public QWidget, public IJackClient
{
	Q_OBJECT
public:
	explicit QJackOscillogram(CJackClient* cjc, const char* name, QWidget *parent = 0);
	~QJackOscillogram();

	virtual int subProcess(jack_nframes_t nframes);
	void paintEvent(QPaintEvent* ev);

signals:

private:
	jack_port_t* mJackPort;
	jack_default_audio_sample_t* mJackBuffer;
	QVector<qreal> mDatagramBuffer;
	jack_nframes_t mJackFPS;
	jack_nframes_t mJackBufferSize;
};

#endif // QJACKOSCILLOGRAM_H

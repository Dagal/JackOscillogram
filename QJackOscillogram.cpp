#include "QJackOscillogram.h"

QJackOscillogram::QJackOscillogram(CJackClient* cjc, const char* name, QWidget *parent) :
	QWidget(parent), IJackClient(cjc)
{
	qDebug() << "QJackOscillogram: Création" << this;

	// Récupération du nombre de port
	// Création du port d'entrée audio
	mJackPort = jack_port_register(getClient()->getClient(),
																 name,
																 JACK_DEFAULT_AUDIO_TYPE,
																 JackPortIsInput,
																 0);
	qDebug() << "QJackOscillogram: Audio Input Port créé" << mJackPort;

	mJackBufferSize = jack_get_buffer_size(getClient()->getClient());
	mJackFPS = jack_get_sample_rate(getClient()->getClient());
}

QJackOscillogram::~QJackOscillogram()
{
	qDebug("QJackOscillogram: Destruction");
}

int QJackOscillogram::subProcess(jack_nframes_t nframes)
{
//	qDebug("QJackOscillogram: Démarrage du sous processus");
	jack_nframes_t tailleBuffer = jack_get_buffer_size(getClient()->getClient());
//	qDebug() << "QJackOscillogram: Taille du buffer " << tailleBuffer;
	mJackBuffer = (jack_default_audio_sample_t*) jack_port_get_buffer(mJackPort,
																																		nframes);
//	qDebug() << "QJackOscillogram: Buffer " << mJackBuffer;
	for (int i=0;i<nframes;++i)
	{
		mDatagramBuffer.append(mJackBuffer[i]);
		if (mDatagramBuffer.count() >= nframes)
		{
			mDatagramBuffer.pop_front();
		}
	}
	update();
}

void QJackOscillogram::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	painter.setBackground(Qt::black);
	painter.setPen(Qt::red);
	if(!mDatagramBuffer.isEmpty())
	{
		float lastX;
		float lastY;
		for (int i=0;i < mDatagramBuffer.count();++i)
		{
			float x = (i * width() / mDatagramBuffer.count());
			float y = (mDatagramBuffer[i] / 2.0 + 1) * height() / 2.0;
			if (i != 0)
			{
				painter.drawLine(lastX,
												 lastY,
												 x,
												 y);
			}
			lastX = x;
			lastY = y;
		}
	}
	else
	{
		qDebug("QJackOscillogram: Le buffer est vide");
		painter.drawRect(10,10,10,10);
	}
}

#include "QJackOscillogram.h"

QJackOscillogram::QJackOscillogram(QWidget *parent) : QWidget(parent)
{
	qDebug("Création d'un QJackOscillogram.");
	// Temporisation avant le démarrage de l'écoute
	mTimer1.setInterval(1000);
	mTimer1.start();
	connect(&mTimer1,SIGNAL(timeout()),
					this, SLOT(startingBlock()));
	//mBufferDatagram.
	mJackBufferSize = 0;
}

QJackOscillogram::~QJackOscillogram()
{
	qDebug("Destruction d'un QJackOscillogram");
	mTimer1.stop();

	qDebug("Destruction du client jack à revoir au plus vite");
	jack_client_close(mJackClient);
}

int QJackOscillogram::staticProcess(jack_nframes_t nframes, void* arg)
{
	static_cast<QJackOscillogram*>(arg)->process(nframes);
}

int QJackOscillogram::process(jack_nframes_t nframes)
{
	jack_nframes_t tailleBuffer = jack_get_buffer_size(mJackClient);
	mJackBuffer = (jack_default_audio_sample_t*) jack_port_get_buffer(mJackPort,
																																		nframes);
	//mBufferDatagram.clear();
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

int QJackOscillogram::staticFrameRateChanged(jack_nframes_t nframes, void* arg)
{

}

int QJackOscillogram::frameRateChanged(jack_nframes_t nframes)
{

}

int QJackOscillogram::staticBufferSizeChanged(jack_nframes_t nframes, void* arg)
{
	static_cast<QJackOscillogram*>(arg)->bufferSizeChanged(nframes);
}

int QJackOscillogram::bufferSizeChanged(jack_nframes_t nframes)
{
	if (mDatagramBuffer.count() != nframes)
	{
		qDebug() << "JackOscillogram : Buffer Size Change from " << mJackBufferSize << " to " << nframes;
		mJackBufferSize = nframes;
		mDatagramBuffer.fill(0,nframes);
	}
}

void QJackOscillogram::updateJackBuffer(jack_default_audio_sample_t* bufferJack)
{

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
		for (int i=0;i < mJackBufferSize;++i)
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
}

void QJackOscillogram::startingBlock()
{
	qDebug("Démarrage du programme");
	mTimer1.stop();

	// Création du client jack
	mJackClient = jack_client_open("JackOscillogram",
																 JackNullOption,
																 NULL);

	// Liaison avec la fonction de processing
	jack_set_process_callback(mJackClient,
														staticProcess,
														this);

	// Liaison avec la fonction de changement de la taille du buffer
	// Ce qui va permettre d'ajuster la taille du buffer pour l'affichage
	jack_set_buffer_size_callback(mJackClient,
																staticBufferSizeChanged,
																this);

	// Création du port d'entrée audio
	mJackPort = jack_port_register(mJackClient,
																 "Input",
																 JACK_DEFAULT_AUDIO_TYPE,
																 JackPortIsInput,
																 0);

	// Activation du client jack
	jack_activate(mJackClient);
}


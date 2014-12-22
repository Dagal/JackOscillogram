#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	qDebug("Création de la fenêtre principale.");
	mTimer1.setInterval(1000);
	mTimer1.start();
	connect(&mTimer1,SIGNAL(timeout()),
					this, SLOT(startingBlock()));
	//mBufferDatagram.
	mJackBufferSize = 0;
}

MainWindow::~MainWindow()
{
	qDebug("Destruction de la fenêtre principale");
	mTimer1.stop();

	qDebug("Destruction du client jack");
	jack_client_close(mClientJack);
}

int MainWindow::staticProcess(jack_nframes_t nframes,
															void* arg)
{
	static_cast<MainWindow*>(arg)->process(nframes);
}

int MainWindow::process(jack_nframes_t nframes)
{
	jack_nframes_t tailleBuffer = jack_get_buffer_size(mClientJack);
	mBufferJack = (jack_default_audio_sample_t*) jack_port_get_buffer(mPortJack,
																																		nframes);
	//mBufferDatagram.clear();
	for (int i=0;i<nframes;++i)
	{
		mBufferDatagram.append(mBufferJack[i]);
		if (mBufferDatagram.count() >= nframes)
		{
			mBufferDatagram.pop_front();
		}
	}
	update();
}

int MainWindow::staticBufferSizeChanged(jack_nframes_t nframes, void* arg)
{
	static_cast<MainWindow*>(arg)->bufferSizeChanged(nframes);
}

int MainWindow::bufferSizeChanged(jack_nframes_t nframes)
{
	if (mBufferDatagram.count() != nframes)
	{
		qDebug() << "JackOscillogram : Buffer Size Change from " << mJackBufferSize << " to " << nframes;
		mJackBufferSize = nframes;
		mBufferDatagram.fill(0,nframes);
	}
}

void MainWindow::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	painter.setBackground(Qt::black);
	painter.setPen(Qt::red);
	if(!mBufferDatagram.isEmpty())
	{
		float lastX;
		float lastY;
		for (int i=0;i < mJackBufferSize;++i)
		{
			float x = (i * width() / mBufferDatagram.count());
			float y = (mBufferDatagram[i] + 1) * height() / 4.0;
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

void MainWindow::startingBlock()
{
	qDebug("Démarrage du programme");
	mTimer1.stop();

	// Création du client jack
	mClientJack = jack_client_open("JackOscillogram",
																 JackNullOption,
																 NULL);

	// Liaison avec la fonction de processing
	jack_set_process_callback(mClientJack,
														staticProcess,
														this);

	// Liaison avec la fonction de changement de la taille du buffer
	// Ce qui va permettre d'ajuster la taille du buffer pour l'affichage
	jack_set_buffer_size_callback(mClientJack,
																staticBufferSizeChanged,
																this);

	// Création du port d'entrée audio
	mPortJack = jack_port_register(mClientJack,
																 "Input",
																 JACK_DEFAULT_AUDIO_TYPE,
																 JackPortIsInput,
																 0);

	// Activation du client jack
	jack_activate(mClientJack);

}

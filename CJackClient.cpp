#include "CJackClient.h"

CJackClient::CJackClient()
{
	CJackClient("NoName");
}

CJackClient::CJackClient(const char* name)
{
	// Par défaut, on crée un client avec pour nom "NoName".
	qDebug() << "CJackClient : Création du client Jack : " << name;
	mJackClient = jack_client_open(name,
																 JackNullOption,
																 NULL);

	// Liaison avec la méthode du processus principale pas si statique que ça.
	qDebug() << "CJackClient : Liaison avec la méthode 'process'";
	jack_set_process_callback(mJackClient,
														staticProcess,
														this);

	// Liaison avec la méthode de redimensionnement du buffer.
	qDebug() << "CJackClient : Liaison avec la méthode 'bufferSizeChanged'";
	jack_set_buffer_size_callback(mJackClient,
																staticBufferSizeChanged,
																this);

	// Activation du client, ce qui met en route les évènements
	qDebug() << "CJackClient : Activation du client";
	jack_activate(mJackClient);
}

CJackClient::~CJackClient()
{

}

int CJackClient::staticProcess(jack_nframes_t nframes, void* arg)
{
	return static_cast<CJackClient*>(arg)->process(nframes);
}

int CJackClient::process(jack_nframes_t nframes)
{
	if (!mIJackClients.isEmpty())
	{
		foreach (IJackClient* ijc, mIJackClients)
		{
			ijc->subProcess(nframes);
		}
	}
	return 0;
}

int CJackClient::staticFrameRateChanged(jack_nframes_t nframes, void* arg)
{
	return static_cast<CJackClient*>(arg)->frameRateChanged(nframes);
}

int CJackClient::frameRateChanged(jack_nframes_t nframes)
{
	qDebug() << "CJackClient : La fréquence d'échantillonnage a changé de " << mJackFrameRate << " en " << nframes;
	mJackFrameRate = nframes;
	return 0;
}

int CJackClient::staticBufferSizeChanged(jack_nframes_t nframes, void* arg)
{
	return static_cast<CJackClient*>(arg)->bufferSizeChanged(nframes);
}

int CJackClient::bufferSizeChanged(jack_nframes_t nframes)
{
	qDebug() << "CJackClient : La taille du buffer a changé de " << mJackBufferSize << " en " << nframes;
	mJackBufferSize = nframes;
	return 0;
}

void CJackClient::updateJackBuffer(jack_default_audio_sample_t* bufferJack)
{

}

void CJackClient::addInterface(IJackClient* ijc)
{
	mIJackClients.append(ijc);
}


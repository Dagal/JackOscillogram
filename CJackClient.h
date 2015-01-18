#ifndef CJACKCLIENT_H
#define CJACKCLIENT_H

#include <jack/jack.h>
#include <QDebug>

#include "IJackClient.h"
class IJackClient;

class CJackClient
{
public:
	CJackClient();
	CJackClient(const char* name);
	~CJackClient();

	static int staticProcess(jack_nframes_t nframes, void* arg);
	int process(jack_nframes_t nframes);
	static int staticFrameRateChanged(jack_nframes_t nframes, void* arg);
	int frameRateChanged(jack_nframes_t nframes);
	static int staticBufferSizeChanged(jack_nframes_t nframes, void* arg);
	int bufferSizeChanged(jack_nframes_t nframes);
	void updateJackBuffer(jack_default_audio_sample_t* bufferJack);

	jack_client_t* getClient() const;

	void addInterface(IJackClient* ijc);

private:
	jack_client_t* mJackClient;
	jack_nframes_t mJackFrameRate;
	jack_nframes_t mJackBufferSize;

	QList<IJackClient*> mIJackClients;
};

#endif // CJACKCLIENT_H

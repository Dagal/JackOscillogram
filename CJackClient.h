#ifndef CJACKCLIENT_H
#define CJACKCLIENT_H

#include <jack/jack.h>
#include <QDebug>

class CJackClient
{
public:
	CJackClient();
	CJackClient(char* name);
	~CJackClient();

	static int staticProcess(jack_nframes_t nframes, void* arg);
	int process(jack_nframes_t nframes);
	static int staticFrameRateChanged(jack_nframes_t nframes, void* arg);
	int frameRateChanged(jack_nframes_t nframes);
	static int staticBufferSizeChanged(jack_nframes_t nframes, void* arg);
	int bufferSizeChanged(jack_nframes_t nframes);
	void updateJackBuffer(jack_default_audio_sample_t* bufferJack);

private:
	jack_client_t* mJackClient;
	jack_nframes_t mJackFrameRate;
	jack_nframes_t mJackBufferSize;
};

#endif // CJACKCLIENT_H

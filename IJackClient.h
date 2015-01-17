#ifndef IJACKCLIENT_H
#define IJACKCLIENT_H

#include "CJackClient.h"
class CJackClient;

class IJackClient
{
public:
	IJackClient(CJackClient* client);
	~IJackClient();

	int subProcess(jack_nframes_t nframes);

	CJackClient* getClient();

private:
	CJackClient* mCJackClient;
};

#endif // IJACKCLIENT_H

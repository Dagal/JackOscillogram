#include "IJackClient.h"

IJackClient::IJackClient(CJackClient* client)
{
	mCJackClient = client;
	client->addInterface(this);
}

IJackClient::~IJackClient()
{

}

int IJackClient::subProcess(jack_nframes_t nframes)
{
	return 0;
}

CJackClient*IJackClient::getClient()
{
	return mCJackClient;
}


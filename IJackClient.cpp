#include "IJackClient.h"

IJackClient::IJackClient(CJackClient* client)
{
	mCJackClient = client;
}

IJackClient::~IJackClient()
{

}

int IJackClient::subProcess(jack_nframes_t nframes)
{

}

CJackClient*IJackClient::getClient()
{
	return mCJackClient;
}


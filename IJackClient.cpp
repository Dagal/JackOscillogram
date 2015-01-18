#include "IJackClient.h"

IJackClient::IJackClient(CJackClient* client)
{
	mCJackClient = client;
	client->addInterface(this);
}

IJackClient::~IJackClient()
{

}

CJackClient*IJackClient::getClient()
{
	return mCJackClient;
}


#include "IJackClient.h"

IJackClient::IJackClient(CJackClient* client)
{
	mCJackClient = client;
}

IJackClient::~IJackClient()
{

}

CJackClient*IJackClient::getClient()
{
	return mCJackClient;
}


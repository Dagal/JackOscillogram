#ifndef IJACKCLIENT_H
#define IJACKCLIENT_H

#include "CJackClient.h"


class IJackClient
{
public:
	IJackClient(CJackClient* client);
	~IJackClient();

private:
	CJackClient* mCJackClient;
};

#endif // IJACKCLIENT_H

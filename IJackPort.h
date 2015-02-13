#ifndef IJACKPORT_H
#define IJACKPORT_H

#include <jack/jack.h>

class IJackPort
{
public:
	IJackPort();
	~IJackPort();

	virtual int subProcess(jack_nframes_t nframes) = 0;
};

#endif // IJACKPORT_H

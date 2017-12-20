#include "random.h"

#define SEEDINIT  -1

static int Seed = SEEDINIT;

#if !defined(WIN32) && !defined(_WIN32_WCE)
#ifdef __linux
#include <stdint.h>
#include <stddef.h>
#endif
#include <sys/types.h>
#include <sys/time.h>
#else
#include <windows.h>
#ifdef _MSC_VER
typedef  unsigned __int64 uint64_t;
#else
#include <stdint.h> /*provided by mingw32*/
#endif
#endif


#ifdef __MACH__
#include <sys/types.h>
#include <sys/timeb.h>
#endif


// get current time as the seed of random number generator, unit is millisecond
static uint64_t get_cur_time(void *unused)
{
#if defined(_WIN32_WCE)
	DWORD timemillis = GetTickCount();
	return timemillis;
#elif defined(WIN32)
//	return timeGetTime() ;
	DWORD timemillis = GetTickCount();
	return timemillis;
#elif defined(__MACH__) && defined(__GNUC__) && (__GNUC__ >= 3)
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000LL) + ((tv.tv_usec+500LL)/1000LL);
#elif defined(__MACH__)
	struct timespec ts;
	struct timeb time_val;
	
	ftime (&time_val);
	ts.tv_sec = time_val.time;
	ts.tv_nsec = time_val.millitm * 1000000;
	return (ts.tv_sec*1000LL) + ((ts.tv_nsec+500000LL)/1000000LL);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000LL) + ((tv.tv_usec+500LL)/1000LL);
#endif
}


// update the seed of random number generator
void RAND_seed(void)
{
	Seed = (int) get_cur_time(NULL);
}


// generate one random number, between 0 ~ 32767
int  RAND_number(void)
{
	if (Seed == SEEDINIT)
		RAND_seed();
	Seed = Seed * 0x000343FD + 0x00269EC3;
	return (Seed >> 16) & 0x00007FFF;
}


// generate pure random number and fill the buffer
int RAND_bytes(unsigned char *buf, int num)
{
	//ZCY UNDO: here we use pseudo random number instead of pure random number
	return RAND_pseudo_bytes(buf, num);
}


// generate pseudo random number and fill the buffer
int  RAND_pseudo_bytes(unsigned char *buf, int num)
{
	if (buf != NULL && num > 0)
	{
		int i;
		for (i=0; i<num; i++)
			*buf++ = (unsigned char) (RAND_number() & 0x00ff);
		return num;
	}
	return -1;
}

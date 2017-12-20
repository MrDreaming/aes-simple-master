#ifndef _MY_LOCK_H
#define _MY_LOCK_H

#include<stdio.h>
#include<pthread.h>

class StaticLock
{
public:
	StaticLock()
	{
		pthread_mutex_init(&g_csTerm, NULL);
	};
	~StaticLock()
	{
		pthread_mutex_destroy(&g_csTerm);
	};
	void lockon()
	{
		pthread_mutex_lock(&g_csTerm); 
	};
	void lockoff()
	{
		pthread_mutex_unlock(&g_csTerm); 
	};
private:
	pthread_mutex_t g_csTerm;
};

#endif
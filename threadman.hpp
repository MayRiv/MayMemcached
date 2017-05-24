#ifndef __THREAD_MAN_HPP
#define __THREAD_MAN_HPP

//#include "List.hpp"
#include "mutexsync.hpp"
#include <list>
#include "thread.hpp"
using namespace lb;
using namespace std;
class ThreadManager : public MutexSyncData
{
public:
	ThreadManager();
	virtual ~ThreadManager();
	void Newtask(); 
	virtual void Remove(Thread *thread)
	{
		LockData();
		thrList.remove(thread);
		count--;
		UnLockData();
	};
	virtual void Add(Thread *thread)
	{
		LockData();
		thrList.push_back(thread);
		count++;
		UnLockData();
	};
	friend class Control;
	friend void sig_fatal(int sig);
protected:
	list<Thread*> thrList;
	int count;
};

#endif


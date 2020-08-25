#pragma once
#ifndef __Monitor__
#define __Monitor__

#include "C:\\RTExamples\\RTExamples\\rt.h"

//Need read(), write(),increment() function. 

class monitor {
private:
	struct elevator {
		int floor; // this is the input
	};

	CDataPool* theDataPool;  // a datapool containing the data to be protected double balance; 
	CMutex* theMutex;	       // a pointer to a hidden mutex protecting the ‘Balance’ variable above
	elevator* D_ptr;		// pointer to the data


public:
	monitor(string Name) {
		theMutex = new CMutex(string("__Mutex__") + string(Name));
		theDataPool = new CDataPool(string("__DataPool__") + string(Name), sizeof(struct elevator));
		D_ptr = (struct elevator*)(theDataPool->LinkDataPool());
	}
	~monitor() {
		delete theMutex;
		delete theDataPool;
	}  /* delete mutex and datapool; */

	int read();
	void write(int data);
	void increment();
};

int monitor::read() {
	theMutex->Wait();
	int temp = D_ptr->floor;
	theMutex->Signal();
	return temp;
}

void monitor::increment() {
	theMutex->Wait();
	D_ptr->floor = D_ptr->floor + 1;
	theMutex->Signal();
}

void monitor::write(int data) {
	theMutex->Wait();
	D_ptr->floor = data;
	theMutex->Signal();

}
#endif#pragma once

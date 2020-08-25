#pragma once
#ifndef __Monitor__
#define __Monitor__

#include "C:\\RTExamples\\RTExamples\\rt.h"

//Need read(), write(),increment() function. 


class monitor {
private:
	struct elevator {
		int floor; // this is the input
		int direction; 
		int destination_floor;
	};

	CSemaphore *P1;
	CSemaphore *C1;
	CSemaphore *C2;
	CSemaphore *P2;

private: 
	CDataPool* theDataPool;  // a datapool containing the data to be protected double balance; 
	elevator* D_ptr;		// pointer to the data


public:
	monitor(string Name) {

		//cout << "Monitor constructor\n";
		P1 = new CSemaphore(string("__Mutex1__") + string(Name), 0, 1); // 1 is free 0 is busy 
		P2 = new CSemaphore(string("__Mutex2__") + string(Name), 0, 1);
		C1 = new CSemaphore(string("__Mutex3__") + string(Name), 1, 1);
		C2 = new CSemaphore(string("__Mutex4__") + string(Name), 1, 1);
		theDataPool = new CDataPool(string("__DataPool__") + string(Name), sizeof(struct elevator));
		D_ptr = (struct elevator*)(theDataPool->LinkDataPool());
		D_ptr->floor = 0;
		D_ptr->direction = 101;
		D_ptr->destination_floor = 9;
		
	}

	~monitor() {
	
		delete theDataPool;
		delete C1;
		delete P1; 
		delete C2; 
		delete P2;
		delete D_ptr; 

	
	}  /* delete mutex and datapool; */


	int* read_IO();
	int* read_disp(); 
	void update_status(int dir, int flo);
	//void increment();
};


int* monitor::read_IO() {
	//int *temp1
	static int temp[2];
	P2->Wait();
	temp[0] = D_ptr->direction;
	temp[1] = D_ptr->floor;
	//temp[2] = D_ptr->destination_floor;
	C2->Signal();
	return temp; // change return and impplement logic 
}
int* monitor::read_disp() {
	static int temp2[2];
	P1->Wait();
	temp2[0] = D_ptr->direction;
	temp2[1] = D_ptr->floor;
	//temp2[2] = D_ptr->destination_floor;
	C1->Signal();
	return temp2; // change return and impplement logic 
}

void monitor::update_status(int dir, int flo) {
	//cout << "update status called\n";
	C1->Wait();
	C2->Wait();
	D_ptr->direction = dir;
	D_ptr->floor = flo;
	P1->Signal();
	P2->Signal();

}
#endif#pragma once

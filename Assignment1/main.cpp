#include 	"C:\\RTExamples\\RTExamples\\rt.h"			// change pathlist to this header file according to where it is stored
#include <iostream>
#include "C:\\Users\\Samuel\\Desktop\\Elevator\\Monitor.h"

// Struct 1 to communicate with elevator 1 


struct		struct1 {		// structure template for some data that we intend to write to the pipeline
	int 	struct1_var1;
	float 	struct2_var2;
};

int termination_flag = 0; 

struct		input_from_outside {		// structure template for some data that we intend to write to the pipeline
	int 	direction;
	int 	floor;
};

struct input_from_outside struct_keyboard;

// Second struct for elevator 2 to be used in a data pool. 
struct struct2 {
	int floors; 
	char direction[5]; 
};

CRendezvous r1("MainR", 3); 
CRendezvous r_process("Process_init", 4);

struct struct2 mystruct2 = { 2, "down" }; 
struct input_from_outside struct_keyboard_read;
int new_command = 0;

struct elevator {
	int floor; // this is the input
	int direction;
	int destination_floor;
};

struct elevator E1 = { 0,101,0 };
struct elevator E2 { 0, 101, 0 };


UINT __stdcall Thread1(void*) // Typed pipeline thread from IO to dispatcher and 
{
		r1.Wait();

		CMailbox Mailbox_disp2io;
		

		cout << "Hello from thread 1 \n ";
		CTypedPipe <input_from_outside> pipe1("IO_Dispatch_Pipe", sizeof(input_from_outside));
		while (1) {
			new_command = 0;
			cout << "new_command=0\n";
			pipe1.Read(&struct_keyboard_read);
			cout << "Thread 1 read [" << struct_keyboard_read.direction << "," << struct_keyboard_read.floor << "] from Pipeline.....\n";
			if (struct_keyboard_read.direction == 101 && struct_keyboard_read.floor == 101) {
				termination_flag = 1; 
			}
			else {
				new_command = 1;
				cout << "new_command=1\n";
			}
 		
		};		


		
		_getch();
	return 0;
}

UINT __stdcall Thread2(void*)
{	
		r1.Wait();
		int *Elevator2_Status;
		monitor Elevator2_Monitor("E2_Monitor");


		while (1) {
			Elevator2_Status = Elevator2_Monitor.read_disp();
			E2.floor = Elevator2_Status[1];
			E2.direction = Elevator2_Status[0];
			cout << "Elevator 2 is on " << Elevator2_Status[1] << "\n";


		}

	cout << "Hello from thread 2 \n"; 
	
	//_getch();
	return 0;
}

UINT __stdcall Thread3(void*)
{
	r1.Wait(); 

	int* Elevator1_Status;
	monitor Elevator1_Monitor("E1_Monitor");


	while (1) {
		Elevator1_Status = Elevator1_Monitor.read_disp();
		E1.floor = Elevator1_Status[1];
		E1.direction = Elevator1_Status[0];
		cout << "Elevator 1 is on floor " << Elevator1_Status[1]<<"\n";


	}
	cout << "Hello from thread 3 \n";


	//_getch();
	return 0;
}


int main(void) { 


	cout << "Creating child processess \n"; 

	CProcess Elevator_1("C:\\Users\\Samuel\\Desktop\\Elevator\\Debug\\Elevator_1.exe",
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,					// process has its own window					
		ACTIVE							// process is active immediately
	);

	
	CProcess Elevator_2("C:\\Users\\Samuel\\Desktop\\Elevator\\Debug\\Elevator_2.exe",
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);

	CProcess IO("C:\\Users\\Samuel\\Desktop\\Elevator\\Debug\\IO.exe",
		NORMAL_PRIORITY_CLASS,			// priority
		OWN_WINDOW,						// process has its own window					
		ACTIVE							// process is active immediately
	);
	
	
	// Dispatcher communication with elevator 1. 
	// Rendezvous  
	r_process.Wait();
	cout << "Rendezvous met! \n ";

	cout << "Dispatcher creating thread 1 to communicate with Elevator 1 \n"; 
	CThread	t1(Thread1, ACTIVE, NULL);
	cout << "Thread 1 creation successful \n";
	
	CThread t2(Thread2, ACTIVE, NULL); 
	cout << "Thread 2 creation successful \n"; 
	CThread t3(Thread3, ACTIVE, NULL);
	cout << "Thread 2 creation successful \n";



	

	/*
	CDataPool dp("Elevator2_DataPool", sizeof(struct struct2));
	struct struct2* MyDataPool = (struct struct2*)(dp.LinkDataPool());

	cout << "Dispatcher linked to datapool at address : " << MyDataPool << ".....\n";
	Sleep(400);  // so child has a chance to write it as well. 
	cout << "Dispatcher reads value for floor = " << MyDataPool->floors << endl;
	Sleep(400); 
	cout << "Dispatcher reading direction " << MyDataPool->direction[5];
	//cout << "Child2 Read value for floor = " << MyDataPool->direction << endl;
*/ 

	//cout << "Dispatcher reading from elevator 2's monitor " << test.read();
	monitor test("Elevator_2_Monitor");
	int *ret;
	int dir;
	int floor;
	while (1) {
		if (new_command == 1) {
			cout << "this is " << struct_keyboard_read.direction << "\n";
			cout << " and this is " << struct_keyboard_read.floor << "\n";


			if (struct_keyboard_read.direction == 549) {//inside elevator 1 command
				Elevator_1.Post(struct_keyboard_read.direction * 10 + struct_keyboard_read.floor);
				// so total values are between 5490 and 5499
			
			}
			else if (struct_keyboard_read.direction == 550) {//if inside elevator 2 command is prompted
				Elevator_2.Post(struct_keyboard_read.direction * 10 + struct_keyboard_read.floor);
				// Elevator 2 inside command can be between 5500 and 5509. 
			
			
			}
			else if (struct_keyboard_read.direction == 117)  // means if u is pressed going up 

			{
				cout << "sending up command to E1\n";
				Elevator_1.Post(struct_keyboard_read.floor);

			}

			else if ((int) struct_keyboard_read.direction == 100) { // if d is pressed go down
				cout << "Sending down command to E2\n";
				Elevator_2.Post(struct_keyboard_read.floor);

			}
			/*
			floor = struct_keyboard_read.floor;
			dir = struct_keyboard_read.direction;
			
			test.update_status(dir,floor);
			
			cout << "status updated\n";
			ret = test.read_disp();
			test.read_IO();
			cout << "Monitor outputs\n" << ret[0] << "  " << ret[1] << "  " << ret[2] << "\n";
			*/ 

		}
		if (termination_flag == 1) {
			IO.Post(1110);
		}

	}; 


	

	
	Elevator_1.WaitForProcess();
	Elevator_2.WaitForProcess();
	IO.WaitForProcess();

	return 0;

	
}
#include 	"C:\\RTExamples\\RTExamples\\rt.h"			// change pathlist to this header file according to where it is stored
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "C:\\Users\\Samuel\\Desktop\\Elevator\\Monitor.h"


struct		input_from_outside {		// structure template for some data that we intend to write to the pipeline
	int 	direction;
	int 	floor;
};

struct input_from_outside struct_keyboard;

CRendezvous r_process("Process_init", 4);
CRendezvous r_io_threads("IO_thread_init", 4);


UINT __stdcall Elevator_1(void*)
{
	r_io_threads.Wait();
	cout << "Hello from thread 1 to communicate with elevator 1 \n";

	int* Elevator1_Status;
	monitor Elevator1_Monitor("E1_Monitor");


	while (1) {
		Elevator1_Status = Elevator1_Monitor.read_IO();
		cout << "Elevator 1 is on floor " << Elevator1_Status[1] << "\n";

	}
	//_getch();
	return 0;
}

UINT __stdcall Elevator_2(void*)
{
	r_io_threads.Wait();
	cout << "Hello from thread 2 to communicate with elevator 2 \n";

	int *Elevator2_Status;
	monitor Elevator2_Monitor("E2_Monitor");


	while (1) {
		Elevator2_Status = Elevator2_Monitor.read_IO();
		cout << "Elevator 2 is on " << Elevator2_Status[1] << "\n";
	}

	//_getch();
	return 0;
}

UINT __stdcall Input_From_Keyboard(void*)
{
	
	r_io_threads.Wait();
	Sleep(500);
	int input_1;
	int input_2; //floor 
	int flag = 0;
	cout << "Hello from thread 3 to communicate with keyboard \n";

	CTypedPipe <input_from_outside> pipe1("IO_Dispatch_Pipe", sizeof(input_from_outside));
	while (1) {
		flag = 0;
		cout << "Input first Command Character\n";
		input_1 = _getch();
		if (input_1 == 49 || input_1 == 50) { // 1 or 2 which means inside elevator 
			cout << "1 or 2 entered\n";
			input_1 = input_1+500;
			while (1) {
				cout << "press 0-9 for floor number\n";
				input_2 = _getch();
				if (input_2 == 49 || input_2 == 50 || input_2 == 51 || input_2 == 52 || input_2 == 53 || input_2 == 54 || input_2 == 55 || input_2 == 56 || input_2 == 48 || input_2 == 57) {
					cout << "0-9 entered\n";
					input_2 = input_2 - 48;
					break;
				}
				else {
					cout << "invalid floor number\n";
				}

			}

		}
		else if (input_1 == 117 || input_1 == 100) {
			cout << "up or down selected\n";
			while (1) {
				cout << "press 0-9 for floor number\n";
				input_2 = _getch();
				if (input_2 == 49 || input_2 == 50 || input_2 == 51 || input_2 == 52 || input_2 == 53 || input_2 == 54 || input_2 == 55 || input_2 == 56 || input_2 == 48 || input_2 == 57) {
					cout << "0-9 entered\n";
					input_2 = input_2 - 48;
					break;
				}
				else {
					cout << "invalid floor number\n";
				}
			}
		}
		else if (input_1 == 101) {

			cout << "termination initiated press e again to confirm\n";
			input_2 = _getch();
			if (input_2 == 101) {
				cout << "termination executing\n";

			}
			else {
				cout << "termination execution not confirmed\n";
			}
		}
		
		else {
			cout << "invalid input try again\n";
			flag = 1;
		}

		if (flag == 0) {
		//cout << "\n"<<input_1 << "\n";
		struct_keyboard.direction = input_1;
		struct_keyboard.floor = input_2;
		pipe1.Write(&struct_keyboard);
	}

	}; 



	return 0;
}


int main(void) {

	r_process.Wait();

	UINT Message_disp2io;

	CMailbox Mailbox_disp2io; 

	cout << "IO creating thread for communicating with Elevator 1 \n";
	CThread	E1_thread(Elevator_1, ACTIVE, NULL);
	cout << "Thread 1 creation successful \n";

	cout << "IO creating thread for communicating with elevator E2 \n";
	CThread E2_thread(Elevator_2, ACTIVE, NULL);
	cout << "Thread 2 creation successful \n";

	cout << "IO creating thread 3 for communicating with keyboard \n";
	CThread Input_thread(Input_From_Keyboard, ACTIVE, NULL);
	cout << "Thread 3 creation successful \n";
	r_io_threads.Wait();

	/*
	CDataPool dp("Elevator2_DataPool", sizeof(struct struct2));
	struct struct2* MyDataPool = (struct struct2*)(dp.LinkDataPool());

	cout << "IO linked to datapool at address : " << MyDataPool << ".....\n";
	Sleep(400);  // so child has a chance to write it as well. 
	cout << "IO reads value for floor = " << MyDataPool->floors << endl;
	Sleep(400);
	cout << "IO reading direction " << MyDataPool->direction[5];
	*/ 

	while (1) {

		if (Mailbox_disp2io.TestForMessage() == TRUE) {
			Message_disp2io = Mailbox_disp2io.GetMessage();
			if (Message_disp2io == 1110) { break;
			}
		}

	}; 

	return 0; 

}
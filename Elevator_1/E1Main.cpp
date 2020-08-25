#include 	"C:\\RTExamples\\RTExamples\\rt.h"			// change pathlist to this header file according to where it is stored
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "C:\\Users\\Samuel\\Desktop\\Elevator\\Monitor.h"

struct		struct1 {		// structure template for some data that we intend to write to the pipeline
	int 	struct1_var1;
	float 	struct2_var2;
};

CRendezvous r_process("Process_init", 4);

struct	 struct1 mystruct1 = { 10, 20.10 }; // a structure with an int and a float in it

int main(void) {

	r_process.Wait();


	CMailbox Mailbox_disp2e1;
	UINT Message_disp2e1;
	monitor Elevator1_Monitor("E1_Monitor");
	int destination_floor; 
	int destination_direction;
	int floor = 0;
	
	while (1) {
		if (Mailbox_disp2e1.TestForMessage()) {
			if (Mailbox_disp2e1.TestForMessage(5490, 5499)) {

				Message_disp2e1 = Mailbox_disp2e1.GetMessage(5490, 5499);
				cout << "message " << Message_disp2e1 << "\n";
				destination_floor = Message_disp2e1 % 5490; // this should give us the floor number 
				if (destination_floor > floor) {
					destination_direction = 117;
				}
				else {
					destination_direction = 100;
				}
				cout << "Going to floor " << destination_floor << "\n";
				floor = destination_floor;
				Elevator1_Monitor.update_status(destination_direction, destination_floor); // now tell the monitor the updated dir and floor when you're inside the elevator 
				//check for inbetween floors later on in code writing 
				Sleep((destination_floor - floor) * 100);
				cout << "Arrived at floor " << destination_floor << "\n";
				floor = destination_floor;
			}
			else if (Mailbox_disp2e1.TestForMessage() == TRUE) {

				Message_disp2e1 = Mailbox_disp2e1.GetMessage();

				cout << "Got message: " << Message_disp2e1 << "\n";
				Elevator1_Monitor.update_status(100, Message_disp2e1); // So now you are sending in the floor
				cout << "Going to floor number " << Message_disp2e1 << "\n";
				Sleep(1000);
				cout << "Arrived at floor number " << Message_disp2e1 << "\n";
			}
		}
	}

	/*
	CTypedPipe <struct1> pipe1("Elevator1_Pipe", sizeof(struct1));

	cout << "Elevator 1 writing 10 and 0.1 to Dispatcher through pipeline 1 \n"; 
	pipe1.Write(&mystruct1); 
	cout << "Write Successful! \n"; 
	*/ 

	_getch(); 
	return 0; 

}
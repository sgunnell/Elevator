#include 	"C:\\RTExamples\\RTExamples\\rt.h"			// change pathlist to this header file according to where it is stored
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "C:\\Users\\Samuel\\Desktop\\CPEN333\\Elevator\\Monitor.h"



// Second struct for elevator 2 to be used in a data pool. 
struct struct2 {
	int floors;
	char direction[5];
};
CRendezvous r_process("Process_init", 4);


struct struct2 mystruct2 = { 2, "down" };


int main(void) {
	cout << "This is elevator 2\n";
	r_process.Wait();
	CMailbox Mailbox_disp2e2;
	UINT Message_disp2e2;
	monitor Elevator2_Monitor("E2_Monitor"); 
	cout << "This is elevator 2\n";
	int destination_floor; 
	int floor = 9;
	int destination_direction; 


	/*
	while (1) {
		//cout << "in the while loop\n";
		if (Mailbox_disp2e2.TestForMessage() == TRUE) {
			cout << "in the if statement \n";
			Message_disp2e2 = Mailbox_disp2e2.GetMessage();
			cout << "Got message: " << Message_disp2e2 << "\n";
			Elevator2_Monitor.update_status(100, Message_disp2e2); // So now you are sending in the floor
			cout << "Going to floor number " << Message_disp2e2 << "\n";
			Sleep(1000); 
			cout << "Arrived at floor number " << Message_disp2e2 << "\n";
			
		}
	}
	*/ 
	while (1) {
		if (Mailbox_disp2e2.TestForMessage()) {

			//cout << Mailbox_disp2e2.TestForMessage(5499, 5510);
			if (Mailbox_disp2e2.TestForMessage(5500, 5509)) {

				Message_disp2e2 = Mailbox_disp2e2.GetMessage(5499, 5509);
				cout << "message " << Message_disp2e2 << "\n";
				destination_floor = Message_disp2e2 % 5500; // this should give us the floor number 
				if (destination_floor > floor) {
					destination_direction = 117;
				}
				else {
					destination_direction = 100;
				}
				cout << "Going to floor " << destination_floor << "\n";
				floor = destination_floor;
				Elevator2_Monitor.update_status(destination_direction, destination_floor); // now tell the monitor the updated dir and floor when you're inside the elevator 
				//check for inbetween floors later on in code writing 
				Sleep((destination_floor - floor) * 100);
				cout << "Arrived at floor " << destination_floor << "\n";
				floor = destination_floor;
			}
			else if (Mailbox_disp2e2.TestForMessage() == TRUE) {

				Message_disp2e2 = Mailbox_disp2e2.GetMessage();

				cout << "Got message: " << Message_disp2e2 << "\n";
				Elevator2_Monitor.update_status(100, Message_disp2e2); // So now you are sending in the floor
				cout << "Going to floor number " << Message_disp2e2 << "\n";
				Sleep(1000);
				cout << "Arrived at floor number " << Message_disp2e2 << "\n";
			}
		}
	}



	/*
	cout << "Elevator 2 creating datapool \n "; 
	CDataPool dp("Elevator2_DataPool", sizeof(struct struct2));
	struct struct2* MyDataPool = (struct struct2*)(dp.LinkDataPool());
	cout << "Elevator 2 linked to datapool at address : " << MyDataPool << ".....\n";

	cout << " Elevator 2 writing floor as 2 to datapool"; 
	MyDataPool->floors = 2;
	cout << "Elevator 2 writing direction as d"; 

	MyDataPool->direction[5] = 'd';
	*/ 
	
	/*monitor test2("test2"); 
	cout << "monitor initilaised\n";
	int* temp22;
	temp22 = test2.read_disp();
	cout << "This is the direction" << temp22[0] << "\n";
	cout << "This is the floor" << temp22[1] << "\n";
	cout << "This is the updated direction should be 9 " << temp22[2] << "\n"; 

	
	/*test2.update_status(0, 7); // direction 0 floor should be 20; 
	cout << "updated status\n";
	*temp22 = *test2.read_disp();
	cout << "This is the direction" << temp22[0] << "\n";
	cout << "This is the floor" << temp22[1] << "\n";
	cout << "This going to floor" << temp22[2] << "\n";*/

	



	_getch();
	return 0; 


}

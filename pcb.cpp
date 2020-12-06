/*
 * pcb.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#include<dos.h>
#include"pcb.h"
#include"system.h"
#include"queue.h"
#include"idle.h"
#include"schedule.h"

Queue* PCB::idQueue=new Queue();
int PCB::lastID=0;


PCB::PCB(Thread *thread, StackSize stackSize, Time timeSlice) {

	LOCK;

	id=lastID++;
	idQueue->put(this);
	pcbStackSize=stackSize;
	pcbTimeSlice=timeSlice;
	myThread=thread;

	status=PCB::CREATED;

	stack=new unsigned[this->pcbStackSize];

#ifndef BCC_BLOCK_IGNORE

		        stack[pcbStackSize-1]=0x200;
				stack[pcbStackSize-2]=FP_SEG(&(wrapper));
				stack[pcbStackSize-3]=FP_OFF(&(wrapper));

				this->sp=this->bp=FP_OFF(stack+pcbStackSize-12);
				this->ss=FP_SEG(stack+pcbStackSize-12);
#endif

	blocked=new Queue();
	zavrsio = 0;
	UNLOCK;

}



void PCB::wrapper() {

	System::running->myThread->run();


	LOCK;

	System::running->status=FINISHED;


	PCB* curr=0;;
	while(System::running->blocked->length()>0) {
		curr=System::running->blocked->get();
		curr->status=READY;
		Scheduler::put(curr);
	}
	dispatch();

}

PCB::~PCB() {
	LOCK;
	delete blocked;
	delete stack;
	UNLOCK;


}




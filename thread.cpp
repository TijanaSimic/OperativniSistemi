/*
 * thread.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */
#include"thread.h"
#include"system.h"
#include"pcb.h"
#include"queue.h"
#include"schedule.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	LOCK;
	if(stackSize>defaultStackSize) stackSize=defaultStackSize;
	stackSize/=2;
	myPCB=new PCB(this, stackSize, timeSlice);
	UNLOCK;
}


ID Thread::getId() {
	LOCK;
	ID i=myPCB->id;
	UNLOCK;
	return i;
}

ID Thread::getRunningId() {
	LOCK;
	ID i= System::running->myThread->getId();
	UNLOCK;
	return i;
}


Thread* Thread::getThreadById(ID id) {
	LOCK;
	Thread* t=PCB::idQueue->getThreadById(id);
	UNLOCK;
	return t;
}

void dispatch() {

	LOCK;
	System::dispatch();
	UNLOCK;
}

void Thread::waitToComplete() {
	LOCK;
	if(this==System::mainThread || this==System::idle || myPCB->status==PCB::FINISHED || myPCB==(PCB*)System::running)  {	UNLOCK; return; }

	System::running->status=PCB::BLOCKED;
	myPCB->blocked->put((PCB*)System::running);
	System::dispatch();
	UNLOCK;
}


Thread::~Thread() {

	LOCK;
	waitToComplete();
	delete myPCB;
	UNLOCK;

}

void Thread::start() {
	LOCK;
	myPCB->status=PCB::READY;
	Scheduler::put(myPCB);
	UNLOCK;
}





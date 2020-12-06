/*
 * kernelse.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#include"semaphor.h"
#include"kernelse.h"
#include"semQ.h"
#include"queue.h"
#include"system.h"
#include"pcb.h"
#include"timeQ.h"
#include"schedule.h"


SemQueue* KernelSem::allSems=new SemQueue();

KernelSem::KernelSem(Semaphore *sem, int init) {

	LOCK;
	allSems->put(this);
	mySem=sem;
	value=init;
	blocked=new Queue();
	timeBlocked=new TimeQueue();
	UNLOCK;

}

int KernelSem::val() const { return value; }

int KernelSem::wait(Time maxTimeToWait) {
	LOCK;
	System::running->returnValue=1;
	value--;
	if(value<0) {
		if(maxTimeToWait==0) {
			blocked->put((PCB*)System::running);
			System::running->status=PCB::BLOCKED;
			dispatch();
		}
		else {
			timeBlocked->put((PCB*)System::running,maxTimeToWait);
			System::running->status=PCB::BLOCKED;
			dispatch();
		}
	}
	UNLOCK;
	return System::running->returnValue;

}

int KernelSem::signal(int n) {
	LOCK;
	if(n<0)  { UNLOCK; return n; }
	else if(n==0) {
		value++;
		if(value<=0) {
			PCB *deblock=blocked->get();
			if(deblock==0) deblock=timeBlocked->getTime();
			if(deblock) {
				deblock->status=PCB::READY;
				deblock->returnValue=1;
				Scheduler::put(deblock);
			}
	}
		UNLOCK;
		return 0; }
	else {
		int i=0;
		while(n>0) {
			value++;
					if(value<=0) {
						PCB *deblock=blocked->get();
						if(deblock==0) deblock=timeBlocked->get();
						if(deblock) {
							i++;
							deblock->status=PCB::READY;
							deblock->returnValue=1;
							Scheduler::put(deblock);
						}
					}
			n--;
			}
		UNLOCK;
		return i;
	}
}

KernelSem::~KernelSem() {
	LOCK;
	delete blocked;
	delete timeBlocked;
	UNLOCK;
}

/*
 * kernelEv.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: OS1
 */


#include"kernelev.h"
#include"pcb.h"
#include"SCHEDULE.H"
#include"system.h"
#include"ivtentry.h"
#include"kernelse.h"


KernelEv::KernelEv (IVTNo ivtno) {
	LOCK;
	this->ivtNo=ivtno;
	IVTEntry::IVT[ivtNo]->kernelEvent = this;
//	myKernelSem = new KernelSem(0);
	this->pcbOwner=(PCB*)System::running;
	blocked = 0;
	value=0;
	UNLOCK;
}
/*
void KernelEv::signal() {
	LOCK;

	if (myKernelSem->val() == 1) {
		UNLOCK;
		return;
	}
	myKernelSem->signal();

	UNLOCK;
}

void KernelEv::wait () {
	LOCK;
	if (System::running != pcbOwner) {
		UNLOCK;
		return;
	}

	myKernelSem->wait(0);
	UNLOCK;
}
*/
void KernelEv::signal() {
	LOCK;
	if(blocked==0) value=1;
	else {
			blocked->status =PCB:: READY;
		    Scheduler::put(blocked);
		    blocked = 0;
	}
	UNLOCK;
}

void KernelEv::wait() {
		LOCK;
		if ((PCB*)System::running == pcbOwner) {
			if (value == 0) {
				blocked = (PCB*)System::running;
				blocked->status = PCB::BLOCKED;
	           dispatch();
			}
			else {
			   value = 0;
			}
		}
		 UNLOCK;
}



KernelEv::~KernelEv () {
	LOCK;
	if (IVTEntry::IVT[ivtNo] != 0)
		IVTEntry::IVT[ivtNo]->kernelEvent = 0;
	//delete myKernelSem;
	UNLOCK;
}



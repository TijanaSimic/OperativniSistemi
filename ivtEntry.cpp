/*
 * ivtEntry.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: OS1
 */



#include "system.h"
#include <dos.h>
#include "kernelev.h"
#include "ivtentry.h"

IVTEntry* IVTEntry::IVT[256] = {0};

IVTEntry::IVTEntry(int ivtno ,void interrupt (*newRout)(...)) {
	this->ivtNo=ivtno;
	IVT[ivtNo]=this;
	this->kernelEvent = 0;
	LOCK;
#ifndef BCC_BLOCK_IGNORE
	oldRout = getvect(ivtNo);
	setvect(ivtNo, newRout);
#endif
	UNLOCK;

}

void IVTEntry::callOld() {
	if(oldRout != 0)
	   (*oldRout)(); //oldRout();
	}

void IVTEntry::signal() {
	if (kernelEvent != 0) {
		kernelEvent->signal();
	}
}

IVTEntry::~IVTEntry() {
	LOCK;
	(*oldRout)(); //oldRout();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo, oldRout);
#endif
	this->kernelEvent=0; //
	UNLOCK;
}







/*
 * event.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: OS1
 */

#include "event.h"
#include "system.h"
#include "kernelev.h"
#include "IVTEntry.h"


Event::Event (IVTNo ivtNo) {
	LOCK;
	myImpl = new KernelEv(ivtNo);
	UNLOCK;
}

void Event::signal() {
	LOCK;
	myImpl->signal();
	UNLOCK;
}

void Event::wait () {
	LOCK;
	myImpl->wait();
	UNLOCK;
}

Event::~Event () {
	LOCK;	delete myImpl;
	UNLOCK;
}



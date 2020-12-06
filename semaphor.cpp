/*
 * semaphor.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#include"semaphor.h"
#include"kernelse.h"
#include"system.h"

Semaphore::Semaphore(int init) {

	LOCK;
	myImpl=new KernelSem(this,init);
	UNLOCK;

}

int Semaphore::val() const  {

	LOCK;
	int i= myImpl->val();
	UNLOCK;
	return i;

}

int Semaphore::wait(Time maxTimeToWait) {
	LOCK;
	int i=myImpl->wait(maxTimeToWait);
	UNLOCK;
	return i;
}


int Semaphore::signal(int n) {
	LOCK;
	int i=myImpl->signal(n);
	UNLOCK;
	return i;
}

Semaphore::~Semaphore() {
	LOCK;
	delete myImpl;
	UNLOCK;
}






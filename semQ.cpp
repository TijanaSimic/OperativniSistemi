/*
 * semQ.cpp
 *
 *  Created on: Aug 18, 2019
 *      Author: OS1
 */


#include"semQ.h"
#include"kernelse.h"
#include"system.h"

SemQueue::SemQueue() {
		LOCK;
	    first=0;
		last=0;
		size=0;
		UNLOCK;
}

int SemQueue::length() { LOCK; int i=size; UNLOCK; return i; }

SemQueue::~SemQueue() {
	LOCK;
	while(first) {
			El* temp=first;
			first=first->next;
			delete temp;
		}
		first=0;
		last=0;
		size=0;
		UNLOCK;
}

void SemQueue::put(KernelSem* s) {
	if(s==0) return;
	LOCK;
	 El *newSEM = new El();
	 newSEM->ksem=s;
	 newSEM->next=0;
		 if(first==0) {first=last=newSEM; }
		 else {
		last->next=newSEM;
		last=newSEM; }
		size++;
		UNLOCK;
}

KernelSem* SemQueue::get() {
	if(first==0) return 0;
	LOCK;
	KernelSem* ret=0;
    if(first) {
        El *del=first;
        ret=first->ksem;
        first=first->next;
        delete del;
        if(first==0) last=0;
        size--;
    }
    UNLOCK;
    return ret;
}






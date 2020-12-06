/*
 * queue.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */
#include"system.h"
#include"queue.h"
#include"thread.h"
#include"pcb.h"


Queue::Queue() {
	LOCK;
	first=0;
	last=0;
	size=0;
	UNLOCK;
}

Queue::~Queue() {
	LOCK;
	while(first) {
		Elem* temp=first;
		first=first->next;
		delete temp;
	}
	first=0;
	last=0;
	size=0;
	UNLOCK;
}

int Queue:: length()  {
	LOCK;
	int s=size;
	UNLOCK;
	return s; }

void Queue:: put(PCB* p) {
	LOCK;
	if(p==0) {UNLOCK; return; }
    Elem *newPCB = new Elem();
	 newPCB->pcb=p;
	 newPCB->next=0;
	 if(first==0) {first=last=newPCB; }
	 else {
	last->next=newPCB;
	last=newPCB; }
	size++;
	UNLOCK;
}


PCB* Queue::get() {
	LOCK;
	PCB* ret=0;
    if(first) {
        Elem *del=first;
        ret=first->pcb;
        first=first->next;
        delete del;
        if(first==0) last=0;
        size--;
    }
    UNLOCK;
    return ret;
}



Thread* Queue::getThreadById(ID id) {
	LOCK;
	for(Elem *tek=first; tek; tek=tek->next)
		if(id==tek->pcb->id) {
			UNLOCK;
			return tek->pcb->myThread;
		}
	UNLOCK;
	return 0;
}





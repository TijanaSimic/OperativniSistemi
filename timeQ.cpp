/*
 * timeQ.cpp
 *
 *  Created on: Aug 23, 2019
 *      Author: OS1
 */


#include"timeQ.h"
#include"system.h"
TimeQueue::TimeQueue() {
	LOCK;
	first=0;
	UNLOCK;
}

TimeQueue:: ~TimeQueue()  {
	LOCK;
	while(first) {
		Elem* temp=first;
		first=first->next;
		delete temp;
	}
	first=0;
	UNLOCK;
}

void TimeQueue::put(PCB *pcb,Time time){
	if(pcb==0) return;
	LOCK;
	 Elem *tek=first, *prev=0;
			 Elem *novi=new Elem();
			 novi->pcb=pcb;
			 novi->time=time;
			 novi->next=0;
	        if(first==0) first=novi;
			 else {
				 while(tek && novi->time>=tek->time) {
					 novi->time-=tek->time;
					 prev=tek;
					 tek=tek->next;
				 }
				 if(prev) {
					 if(tek) {
						  tek->time-=novi->time;
						 prev->next=novi;
						 novi->next=tek;
					 } else	 {
						 prev->next=novi;
						 novi->next=0;
			 					}
			 				}
			 				else {
			 				    tek=first;
			 					novi->next=first;
			 					first=novi;
			 					if(tek) { tek->time-=novi->time; }
			 				}
			 			}
	        UNLOCK;
}




PCB* TimeQueue::getTime() {
	if(first==0) return 0;
	LOCK;
	int deleteTime=0;
	PCB* ret=0; Elem* old=first;

		ret=first->pcb;
		deleteTime=first->time;
		first=first->next;
	if(first)	first->time+=deleteTime;
		delete old;
	UNLOCK;
	return ret;
}

PCB* TimeQueue::get(){
	if(first==0) return 0;
	LOCK;
		PCB* ret=0;
		Elem *del=first;
		ret=first->pcb;
		first=first->next;
		delete del;
		UNLOCK;
		return ret;
}


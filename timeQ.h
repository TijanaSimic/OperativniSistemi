/*
 * timeQ.h
 *
 *  Created on: Aug 23, 2019
 *      Author: OS1
 */

#ifndef H_TIMEQ_H_
#define H_TIMEQ_H_



#include "thread.h"


class PCB;

class TimeQueue{
public:
	 struct Elem{
		 PCB *pcb;
		 Time time;
		 Elem *next;
	 };


	 Elem *first;

	  TimeQueue();
	 ~TimeQueue();

	 friend class PCB;
	 friend class System;
	 friend void interrupt timer();
	 friend class KernelSem;


	 void put(PCB *pcb,Time time);
	 PCB* get();
	 PCB* getTime();


};



#endif /* H_TIMEQ_H_ */

/*
 * pcb.h
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_

#include"thread.h"

class Queue;

class PCB {

public:

	enum Status { CREATED, READY, BLOCKED, IDLE, FINISHED};
	volatile Status status;

	Thread *myThread;

	Time pcbTimeSlice;
	StackSize pcbStackSize;

	ID id;
	static int lastID;
	static Queue* idQueue;

	PCB(Thread *thread, StackSize stackSize, Time timeSlice);
	~PCB();

	unsigned* stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;

	friend class System;
	friend class Idle;
	friend void interrupt timer();

	Queue* blocked;
	unsigned zavrsio;

	static void wrapper();

	int returnValue;
	Time timeToWait;








};



#endif /* H_PCB_H_ */

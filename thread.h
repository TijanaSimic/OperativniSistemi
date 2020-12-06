/*
 * thread.h
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#ifndef H_THREAD_H_
#define H_THREAD_H_



typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;



class PCB; // Kernel's implementation of a user's thread


class Thread {

public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);

protected:
	friend class PCB;
	friend class Idle;
	friend class System;
    friend void interrupt timer();

	Thread (StackSize stackSize=defaultStackSize, Time timeSlice=defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
};

void dispatch ();




#endif /* H_THREAD_H_ */

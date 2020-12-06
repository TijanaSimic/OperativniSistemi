/*
 * kernelse.h
 *
 *  Created on: Sep 9, 2019
 *      Author: OS1
 */

#ifndef H_KERNELSE_H_
#define H_KERNELSE_H_

#include"semaphor.h"

class SemQueue;
class Queue;
class TimeQueue;

class KernelSem {

public:

	friend class Semaphor;

	KernelSem(Semaphore *sem,int init=1);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n=0);

	int value;
	int val() const;

	Semaphore* mySem;

	static SemQueue* allSems;

	Queue* blocked;
	TimeQueue* timeBlocked;



};


#endif /* H_KERNELSE_H_ */

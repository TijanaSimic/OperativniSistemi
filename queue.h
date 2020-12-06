/*
 * queue.h
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#ifndef H_QUEUE_H_
#define H_QUEUE_H_

#include"thread.h"
class PCB;
class Thread;

class Queue {

public:
	struct Elem {
		PCB* pcb;
		Elem* next;

	};
	Elem *first, *last;
	int size;



	Queue();
	int length();
	void put(PCB* pcb);

	PCB* get();
	Thread* getThreadById(ID id);
	~Queue();
};





#endif /* H_QUEUE_H_ */

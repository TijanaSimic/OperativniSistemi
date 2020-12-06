/*
 * semQ.h
 *
 *  Created on: Aug 18, 2019
 *      Author: OS1
 */

#ifndef H_SEMQ_H_
#define H_SEMQ_H_

#include"KernelSe.h"

class SemQueue {
public:
	friend class KernelSem;
	friend class System;

	struct El {
		KernelSem* ksem;
		El* next;
	};

	El *first, *last;
	int size;

	SemQueue();
	~SemQueue();
	void put(KernelSem* s);
	KernelSem* get();
	int length();
};



#endif /* H_SEMQ_H_ */

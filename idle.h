/*
 * idle.h
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#ifndef H_IDLE_H_
#define H_IDLE_H_

#include"thread.h"

class Idle: public Thread {

public:
	Idle();
	void start();
	virtual void run();
	friend class Thread;
	friend class PCB;


};




#endif /* H_IDLE_H_ */

/*
 * system.h
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#ifndef H_SYSTEM_H_
#define H_SYSTEM_H_


#define LOCK {asm{pushf; cli;}}

#define UNLOCK {asm{popf}}


void interrupt timer();
class SemQueue;
class Thread;
class PCB;
class Idle;

class System {

public:

	static Thread* mainThread;
	static volatile PCB* running;
	static Idle* idle;



	static void inic();
	static void restore();

	static void dispatch();

	friend class PCB;

};



#endif /* H_SYSTEM_H_ */

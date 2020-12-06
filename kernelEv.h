/*
 * kernelEv.h
 *
 *  Created on: Sep 17, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_


#define PREPAREENTRY(ivtno,old) \
void interrupt interruptRoutine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,interruptRoutine##ivtno); \
void interrupt interruptRoutine##ivtno(...) { \
	if (old) ent##ivtno.callOld(); \
	ent##ivtno.signal(); \
	dispatch(); \
}


#include "event.h"

class Thread;
class PCB;
class KernelSem;

class KernelEv {

public:
//	KernelSem *myKernelSem;
	IVTNo ivtNo;
	PCB* pcbOwner;
	PCB *blocked;
	int value;

	KernelEv(IVTNo ivtno);

	void signal();
	void wait();

	~KernelEv();
};


#endif /* KERNELEV_H_ */

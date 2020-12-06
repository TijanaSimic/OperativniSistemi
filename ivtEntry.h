/*
 * ivtEntry.h
 *
 *  Created on: Sep 17, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

class KernelEv;

class IVTEntry {

public:

	//friend class KernelEv;

	unsigned ivtNo;
	KernelEv* kernelEvent;
	void interrupt (*oldRout)(...);


	IVTEntry(int ivtno,void interrupt(*)(...));

	void callOld();
	void signal();

   ~IVTEntry();

	static IVTEntry* IVT[256];


};




#endif /* IVTENTRY_H_ */

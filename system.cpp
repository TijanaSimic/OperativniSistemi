/*
 * system.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */

#include"system.h"
#include"pcb.h"
#include"thread.h"
#include"queue.h"
#include"schedule.h"
#include"idle.h"
#include"timeQ.h"
#include"kernelse.h"
#include"semQ.h"

extern void tick();
unsigned oldTimerOFF, oldTimerSEG;
volatile int contextOnDemand=0;
volatile int counter=1;

Idle* System::idle=0;
volatile PCB* System::running=0;
Thread* System:: mainThread=0;



 void interrupt timer() {

	static unsigned  tsp,tss,tbp;
	if (contextOnDemand==0) {

		tick();
		asm int 60h;


		for(SemQueue::El* tek=KernelSem::allSems->first;tek;tek=tek->next)
					if(tek->ksem->timeBlocked ->first)
					{
						tek->ksem->timeBlocked ->first->time--;
							 	while(tek->ksem->timeBlocked ->first->time<=0)
							 			{
							 		PCB *ret=tek->ksem->timeBlocked ->get();
							 		if(ret) {
							 						ret->status=PCB::READY;
							 						Scheduler::put(ret);
							 						ret->returnValue=0;
							 						tek->ksem->value++;
							 			}
							 			}
					}


	}

	if (contextOnDemand==0 &&  counter>0 && System::running->pcbTimeSlice!=0) counter--;

	if (!contextOnDemand && (counter>0 || System::running->pcbTimeSlice==0)) return;

	if(System::running->status==PCB::READY && System::running!=System::idle->myPCB)
			Scheduler::put((PCB*)System::running);

  	asm {
			// cuva sp
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}

		System::running->sp = tsp;
		System::running->ss = tss;
		System::running->bp=tbp;

		System::running=Scheduler::get();
		if(System::running==0) {
			System::running=System::idle->myPCB;
			System::running->status=PCB::IDLE;
		}

		tsp = System::running->sp;
		tss = System::running->ss;
		tbp=System::running->bp;

		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
			}

	counter = System::running->pcbTimeSlice;
	contextOnDemand=0;
	return;
}


 void System::dispatch() {

 	LOCK;
 	contextOnDemand=1;
 	asm int 8h;
 	contextOnDemand=0;
 	UNLOCK;
  	return;

 }
 void System::inic() {
 	LOCK;
#ifndef BCC_BLOCK_IGNORE
 	asm{

 					push es
 			 		push ax

 			 		mov ax,0
 			 		mov es,ax

 			 		mov ax, word ptr es:0022h
 			 		mov word ptr oldTimerSEG, ax
 			 		mov ax, word ptr es:0020h
 			 		mov word ptr oldTimerOFF, ax

 			 		mov word ptr es:0022h, seg timer
 			 		mov word ptr es:0020h, offset timer

 			 		mov ax, oldTimerSEG
 			 		mov word ptr es:0182h, ax
 			 		mov ax, oldTimerOFF
 			 		mov word ptr es:0180h, ax

 			 		pop ax
 			 		pop es

 			}

 	#endif
 	mainThread=new Thread(defaultStackSize, 1);
 	mainThread->myPCB->status=PCB::READY;
 	running=(volatile PCB*)mainThread->myPCB;
 	idle=new Idle();
 	idle->start();
 	UNLOCK;
 }

 void System::restore() {
 	LOCK;
 	if((PCB*)running!=mainThread->myPCB) return;

#ifndef BCC_BLOCK_IGNORE


	asm {
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
		}
#endif

	Queue* q=PCB::idQueue;
		delete q;
		q=0;
		SemQueue* sem=KernelSem::allSems;
		delete sem;
		sem=0;
 	delete mainThread;
 	delete idle;
 	UNLOCK;
 }





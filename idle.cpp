/*
 * idle.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */


#include"idle.h"
#include"thread.h"
#include"pcb.h"
#include"system.h"

class Thread;
class PCB;

Idle::Idle(): Thread(512,1) {}

void Idle::start() {
	LOCK;
	this->myPCB->status=PCB::IDLE;
	UNLOCK;
}


void Idle::run() {
	for(;;);
}




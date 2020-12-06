/*
 * main.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: OS1
 */


#include"System.h"

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]) {

	System::inic();
	int doSomething=userMain(argc,argv);
	System::restore();

	return doSomething;
}




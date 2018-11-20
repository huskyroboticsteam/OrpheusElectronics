/*
 * TCB.h
 *
 * Created: 10/25/2018 7:48:31 PM
 *  Author: Akhil Avula
 */ 


#ifndef TCB_H_
#define TCB_H_

	typedef struct tcbStruct 
	{
		void(*task)(void *taskDataPtr);
		void *dataPtr;
		
		struct tcbStruct *prevTCBPtr;
		struct tcbStruct *nextTCBPtr;
		int index;
		
	} TCB;

#endif /* TCB_H_ */
/*
 * scheduler.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"

extern TCB *firstTCBPtr;
extern TCB *lastTCBPtr;

extern char addFlags[];
extern char removeFlags[];
extern TCB *taskArray[];

void scheduler(void) {
	int i = 0;
	for (i = 0; i < NUM_TASKS; i++) {
		if (addFlags[i]) {
			addTask(taskArray[i]);
			addFlags[i] = 0;
		}
		if (removeFlags[i]) {
			remove(taskArray[i]);
			removeFlags[i] = 0;
		}
		executeTask(firstTCBPtr);
	}
}

void executeTask(TCB* node) {
	if (NULL == node) return;
	node->task((void*) node->dataPtr);
	removeFlags[node->index] = 1;
}

void addTask(TCB* node) {
	if (NULL == node) return;
	if (NULL == firstTCBPtr) {
		firstTCBPtr = node;
		lastTCBPtr = node;
		firstTCBPtr->nextTCBPtr = NULL;
	} else {
		TCB *currPtr = firstTCBPtr;
		while(NULL != currPtr->nextTCBPtr)
		{
			if(currPtr == node) return;
			currPtr = currPtr->nextTCBPtr;
		}
		node->prevTCBPtr = lastTCBPtr;
		lastTCBPtr->nextTCBPtr = node;
		lastTCBPtr = node;
		lastTCBPtr->nextTCBPtr = NULL;
	}
}

void removeTask(TCB* node) {
	if (NULL == node) return;
	if (firstTCBPtr == node) {
		firstTCBPtr = firstTCBPtr->nextTCBPtr;
		firstTCBPtr->prevTCBPtr = NULL;
	} else {
		TCB *currPtr = firstTCBPtr;
		while(NULL != currPtr->nextTCBPtr)
		{
			if(currPtr == node) break;
			currPtr = currPtr->nextTCBPtr;
		}
		currPtr->prevTCBPtr = currPtr->nextTCBPtr;
	}
}
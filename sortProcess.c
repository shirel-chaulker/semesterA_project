#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "Structs.h"
#include"oneSnapShot.h"
#pragma warning(disable:4996)


void PrintList()
{
	LogEvent("Print program started");
	PROCESS* move = PROCESS_Head;
	PROCESS* print = PROCESS_Head;

	while (move != NULL)
	{
		print = move;
		move = move->next;
		printf("the number is %d\n", print->numbersOfDLL);
		LogEvent("A document has been printed");

	}
	
}

void PrintCount()
{
	PROCESS* move = PROCESS_Head;
	PROCESS* print = PROCESS_Head;

	while (move != NULL)
	{
		print = move;
		move = move->next;
		printf("the countProcess is %d\n", print->countProcess);
		LogEvent("A document has been printed");

	}
	printf("the tail is %d\n", PROCESS_Tail->countProcess);
	LogEvent(" the print succed");
}


void PrintListDictionary()
{
	LogEvent("Print program started");
	dictionaryDLL* move = dictionaryDLL_Head;
	dictionaryDLL* print = dictionaryDLL_Head;

	while (move != NULL)
	{
		print = move;
		move = move->next;
		printf("the number is %s\n", print->nameOfDLL);
		LogEvent("A document has been printed");

	}
	
	printf("\n\n\n");
}

void replaceBetweenTwoProcess(PROCESS* processToChange)
{
	LogEvent("enter the Replace function");
	PROCESS* changeProcess = processToChange;
	int numOfProcess;

	if (changeProcess == NULL)
	{
		LogEvent("there is no item in list");
	}
	else if (changeProcess->next == NULL)
	{
		LogEvent("no need to swap, there is one item");
	}
	else if (changeProcess == PROCESS_Head && changeProcess->next == PROCESS_Tail)
	{
		LogEvent("swap between two items");
		numOfProcess = changeProcess->countProcess;
		changeProcess->countProcess = changeProcess->next->countProcess;
		changeProcess->next->countProcess = numOfProcess;
		changeProcess->next = NULL;
		changeProcess->prev = PROCESS_Tail;
		PROCESS_Tail->prev = NULL;
		PROCESS_Tail->next = changeProcess;
		PROCESS_Tail = changeProcess;
		PROCESS_Head = changeProcess->prev;

		//only two numbers
	}
	else if (changeProcess == PROCESS_Head)
	{
		
		numOfProcess = changeProcess->countProcess;
		changeProcess->countProcess = changeProcess->next->countProcess;
		changeProcess->next->countProcess = numOfProcess;
		changeProcess->next->prev = NULL;
		changeProcess = changeProcess->next->next;
		PROCESS_Head->next->next = PROCESS_Head;
		PROCESS_Head->prev = PROCESS_Head->next;
		PROCESS_Head->next = changeProcess;
		changeProcess->prev = PROCESS_Head;
		PROCESS_Head = PROCESS_Head->prev;
		changeProcess = PROCESS_Head->next;
		//change from the beginning

	}
	else if (changeProcess->next == PROCESS_Tail)
	{
		LogEvent("swap with the number before the last one");
		numOfProcess = changeProcess->countProcess;
		changeProcess->countProcess = changeProcess->next->countProcess;
		changeProcess->next->countProcess = numOfProcess;
		changeProcess->next->prev = changeProcess->prev;
		changeProcess->prev = PROCESS_Tail;
		PROCESS_Tail->next = changeProcess;
		changeProcess->next = NULL;
		PROCESS_Tail->prev->next = changeProcess->prev;
		PROCESS_Tail = PROCESS_Tail->next;

		//change the tail
	}
	else
	{
		LogEvent("sort from the middle");
		numOfProcess = changeProcess->countProcess;
		changeProcess->countProcess = changeProcess->next->countProcess;
		changeProcess->next->countProcess = numOfProcess;
		changeProcess->next->prev = changeProcess->prev;
		changeProcess->prev = changeProcess->next;
		changeProcess->next = changeProcess->next->next;
		changeProcess->prev->next = changeProcess;
		changeProcess->prev->prev->next = changeProcess->prev;
		changeProcess->next->prev = changeProcess;

		//Change from the middle
	}

	LogEvent("the system has finish to sort");
}

void SortingBetweenTwoProcessCountDLL()
{
	

	PROCESS* curreProcess = PROCESS_Head;
	if (!curreProcess)
	{
		LogError(strerror(GetLastError()));
		return;
	}

	char change = 1;
	while (change != 0)
	{
		

		change = 0;
		while (curreProcess != NULL)
		{
			if (curreProcess->next != NULL && curreProcess->numbersOfDLL > curreProcess->next->numbersOfDLL)
			{
				replaceBetweenTwoProcess(curreProcess);
				change++;
			}
			curreProcess = curreProcess->next;
		}

		curreProcess = PROCESS_Head;
	}
	
	PrintList();

	
}



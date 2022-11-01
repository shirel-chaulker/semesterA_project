#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "Structs.h"
#include "oneSnapShot.h"
#include "dictionaryFunctions.h"
#pragma warning(disable:4996)

dictionaryDLL* dictionaryDLL_Head = NULL;
dictionaryDLL* dictionaryDLL_Tail = NULL;

S_dictionaryProcess* usedDictionaryProcess = NULL;


int countnewDictionaryDLL = 0;
 int notExistsDLLInList = 0;
 char* nameDH = "";
 

void dictionaryProcess(snapshot* snapShotList){
	FirstListProcess = 1;
	snapshot* currSnapShot = snapShotList;
	PROCESS* OldcurrProcess;
	while (currSnapShot != NULL) {

		PROCESS* currProcess = currSnapShot->myprocess;
		

		while(currProcess != NULL) {

			addProcess(currProcess);
			OldcurrProcess = currProcess;
			currProcess = currProcess->next;
		
		}

		currSnapShot = currSnapShot->next;
	}

}


 void dictionaryDLLFunction(PROCESS* sortProcessList){

		PROCESS* currentPro = sortProcessList;
		PROCESS* OldcurrentPro;
		

		dictionaryDLL* currentDictionaryDLL1 = dictionaryDLL_Head;
		DLLName* currentCheckDLL = sortProcessList->dll;


		while (currentPro != NULL)
		{
			currentCheckDLL = currentPro->dll;

		    while (currentCheckDLL != NULL)//new 
		    {
				currentDictionaryDLL1 = dictionaryDLL_Head;
		    
		    	while (currentDictionaryDLL1 != NULL)//origin
		    	{
		    
		    		if (currentDictionaryDLL1->nameOfDLL != NULL && strcmp( currentCheckDLL->nameOfDLL, currentDictionaryDLL1->nameOfDLL) == 0)//checking if the dlls are equal
		    		{
						notExistsDLLInList = 1;
						checkDictionaryDLL(currentCheckDLL, currentPro);
						

						currentDictionaryDLL1 = dictionaryDLL_Tail;
		    		}
					currentDictionaryDLL1 = currentDictionaryDLL1->next;
		    	}
		    	if (notExistsDLLInList != 1)
		    	{
		    		addDictionaryDLL(currentCheckDLL, currentPro);
		    
		    	}
				
		    	currentCheckDLL = currentCheckDLL->next;
				notExistsDLLInList = 0;
		    }

			OldcurrentPro = currentPro;
		currentPro = currentPro->next;
		free(OldcurrentPro);
		}

		
}



void addDictionaryDLL(DLLName* nameSortDLL, PROCESS* processSortDLL) {

	 
	if (nameSortDLL == NULL && processSortDLL == NULL)
	{
		countnewDictionaryDLL = 0;
		dictionaryDLL_Head = NULL;
		return;
	}
	

	dictionaryDLL* newDictionaryDLL = (dictionaryDLL*)malloc(sizeof(dictionaryDLL));
	if (!newDictionaryDLL)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	countnewDictionaryDLL++;
	newDictionaryDLL->countDictionaryDLL = countnewDictionaryDLL;

	MakeProcessDictionary(processSortDLL);
	newDictionaryDLL->dictionaryProcessTail = dictionaryProcess_Tail;
	newDictionaryDLL->dictionaryProcessUsed = dictionaryProcess_Head;
	strcpy(newDictionaryDLL->nameOfDLL, nameSortDLL->nameOfDLL);


	newDictionaryDLL->next = NULL;
	if (dictionaryDLL_Head == NULL) {
		dictionaryDLL_Head = newDictionaryDLL;
		dictionaryDLL_Tail = newDictionaryDLL;
		newDictionaryDLL->prev = NULL;
	}
	else {
		dictionaryDLL_Tail->next = newDictionaryDLL;
		newDictionaryDLL->prev = dictionaryDLL_Tail;
		dictionaryDLL_Tail = newDictionaryDLL;
	}
	MakeProcessDictionary(NULL);
	
	
}





void checkDictionaryDLL(DLLName* dDLL, PROCESS* newProDictionary)
{
	dictionaryDLL* moveDictionaryDLL = dictionaryDLL_Head;

	while (moveDictionaryDLL != NULL)
	{
		if (strcmp(moveDictionaryDLL->nameOfDLL, dDLL->nameOfDLL) == 0)
		{
			 addDictionaryProcess(moveDictionaryDLL, newProDictionary);
			 moveDictionaryDLL = dictionaryDLL_Tail;
		}

		moveDictionaryDLL = moveDictionaryDLL->next;
	}



}



#include <string.h>
#include <stdio.h>
#include "log.h"
#include "Structs.h"
#include "SnapShotList.h"
#pragma warning(disable:4996)

extern int ExistsDLL = 0;
void checkListDLL(PROCESS* currentProcess, DLLName * CheckDLL)
{
	DLLName* currentDLL = currentProcess->dll;
	DLLName* currentCheckDLL = CheckDLL;
	while (currentCheckDLL != NULL)//new 
	{
		currentDLL = currentProcess->dll;
		LogEvent("compare between the dll`s");
		while (currentDLL != NULL)//origin
		{

			if (strcmp(currentCheckDLL->nameOfDLL,currentDLL->nameOfDLL) == 0 )//checking if the dlls are equal
			{
				currentDLL = DLLName_Tail;
				ExistsDLL = 1;
			}
				currentDLL = currentDLL->next; 
		}
	     if (ExistsDLL != 1)
	      {
			
			 DLLName* dllTailProcessCurrent;
			 dllTailProcessCurrent = addDLLToExistList(currentProcess->dllTail, currentCheckDLL);
			 currentProcess->dllTail = dllTailProcessCurrent;
			 currentProcess->numbersOfDLL = dllTailProcessCurrent->countDLL;
	     	
	      }
		currentCheckDLL = currentCheckDLL->next;
		ExistsDLL = 0;
		
	}


}


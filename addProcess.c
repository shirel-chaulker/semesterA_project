#include <stdlib.h>
#include <stdio.h>
#include "Structs.h"
#include "log.h"
#include "oneSnapShot.h"
#include "typesFilesHeader.h"
#include "resetCollectionsFile.h"
#include "structHeaderFunction.h"
#include "SnapShotList.h"
#include "dictionaryFunctions.h"
#pragma warning(disable:4996)

 PROCESS* PROCESS_Head = NULL;
 PROCESS* PROCESS_Tail = NULL;

int countP = 0;
void addProcess(PROCESS* processNew)
{
	addDLL(NULL);
	//LogEvent("creating a new process");
	if (processNew == NULL)
	{
		countP = 0;
		PROCESS_Head = NULL;
		return;
	}

	if (FirstListProcess >0)  // if this is not the first list of process
	{
		checkListProcess(processNew);

		if (processNotExist == 1)
		{
			processNotExist = 0;
			return;
		}

	}

	
	++countP;
	LogEvent("The function has started");
	
	newProcess = (PROCESS*)malloc(sizeof(PROCESS));
	if (!newProcess)
	{
		LogError(strerror(GetLastError()));
		exit(1);
	}
	strcpy(newProcess->nameOfProcess, processNew->nameOfProcess);
	newProcess->PageFaultCount = processNew->PageFaultCount;
	newProcess->WorkingSetSize = processNew->WorkingSetSize;
	newProcess->QuotaPeakPagedPoolUsage = processNew->QuotaPeakPagedPoolUsage;
	newProcess->QuotaPagedPoolUsage = processNew->QuotaPagedPoolUsage;
	newProcess->PagefileUsage = processNew->PagefileUsage;
	newProcess->processId = processNew->processId;
	newProcess->numbersOfDLL = processNew->numbersOfDLL;
	newProcess->countProcess = countP;

	if (loadFormFile == 0)
	{
		newProcess->dll = processNew->dll;
		newProcess->dllTail = processNew->dllTail;
	}

	newProcess->next = NULL;

	if (PROCESS_Head == NULL)
	{

		PROCESS_Head = newProcess;
		PROCESS_Tail = newProcess;
		newProcess->prev = NULL;
	}
	else
	{
		PROCESS_Tail->next = newProcess;
		newProcess->prev = PROCESS_Tail;
		PROCESS_Tail = newProcess;
	}

  headerProcessDetails();
}



void headerProcessDetails()
{
	processHeaderFile->versionProcess = versionOfProcess;
	processHeaderFile->reserve[0];
}
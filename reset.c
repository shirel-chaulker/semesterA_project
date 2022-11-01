#include <stdlib.h> 
#include <stdio.h>
#include "log.h"
#include "Structs.h"
#include "resetCollectionsFile.h"
#include "homePageHTML.h"
#pragma warning(disable:4996)


void resetCollections(snapshot* headSanpSot)
{
	LogEvent("enter the function (resetCollections)");
	firstTimeInFile = 0;
	firstTimeHomePage = 0;
	saveInToFileHTML(readFromFile());
	restet = 1;
	snapshot* currentSnapShot = headSanpSot;
	PROCESS* currentProcess;
	DLLName* currentDLL;
	snapshot* oldSnapShot;
	PROCESS* oldProcess;
	DLLName* oldDLL;
	while (currentSnapShot != NULL)
	{
		currentProcess = currentSnapShot->myprocess;
		while (currentProcess != NULL)
		{
			currentDLL = currentProcess->dll;
			while (currentDLL != NULL)
			{
				oldDLL = currentDLL;
				currentDLL = currentDLL->next;
				free(oldDLL);
			}

			oldProcess = currentProcess;
			currentProcess = currentProcess->next;
			free(oldProcess);

		}

		oldSnapShot = currentSnapShot;
		currentSnapShot = currentSnapShot->next;
		free(oldSnapShot);

	}
	LogEvent("The function (resetCollections) is done and deleted all\n");

}
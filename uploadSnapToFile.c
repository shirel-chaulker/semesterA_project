#include <stdio.h>
#include <stdlib.h> 
#include "Structs.h"
#include "log.h"
#include "typesFilesHeader.h"
#include "fileFunction.h"
#pragma warning(disable:4996)

snapShotHeader* snapShotHeaderFile = NULL;
processHeader* processHeaderFile = NULL;
DLLNameHeaders* DLLHeaderFile = NULL;

char fileName[50] = "";
void uploadSnapToFile() 
{
	int write;
	if (snapShotHeaderFile->versionSnapShot == NULL )
	{
		
		return;
	}
	printf("enter name for file\n");
	scanf("%s", fileName);
	FILE* f = fopen(fileName, "wb");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		exit(1);
	}



	write = fwrite(snapShotHeaderFile,sizeof(snapShotHeader),1,f);
	if (!write)
	{
		LogError(strerror(GetLastError()));
		return;
	}
	write = fwrite(processHeaderFile, sizeof(processHeader), 1, f);
	if (!write)
	{
		LogError(strerror(GetLastError()));
		return;
	}
	
	write = fwrite(DLLHeaderFile, sizeof(DLLNameHeaders), 1, f);
	if (!write)
	{
		LogError(strerror(GetLastError()));
		return;
	}


	snapshot* currentSnapShot = snapshot_Head;
	PROCESS* currentProcess = currentSnapShot->myprocess;
	DLLName* currentDLL = currentProcess->dll;

	while (currentSnapShot != NULL)
	{
	     write = fwrite(currentSnapShot, sizeof(snapshot), 1, f);
		 if (!write)
		 {
			 LogError(strerror(GetLastError()));
			 return;
		 }

		 currentProcess = currentSnapShot->myprocess;

		 while (currentProcess != NULL)
		 {
			 write = fwrite(currentProcess, sizeof(PROCESS), 1, f);
			 if (!write)
			 {
				 LogError(strerror(GetLastError()));
				 return;
			 }

			 currentDLL = currentProcess->dll;

			 while (currentDLL != NULL)
			 {
				 write = fwrite(currentDLL, sizeof(DLLName), 1, f);
				 if (!write)
				 {
					 LogError(strerror(GetLastError()));
					 return;
				 }
				 
				 currentDLL = currentDLL->next;
			 }


			 currentProcess = currentProcess->next;

		 }

		currentSnapShot = currentSnapShot->next;
	}
	fclose(f);
}



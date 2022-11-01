#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "Structs.h"
#include "log.h"
#include "oneSnapShot.h"
#include "GetProcess.h"
#include "structHeaderFunction.h"
#include "typesFilesHeader.h"
#include "MemoryFunction.h"
#include "homePageHTML.h"
#include "displayFunction.h"
#pragma warning(disable:4996)

snapshot* snapshot_Head = NULL;
snapshot* snapshot_Tail = NULL;

int countOfSnapsNumber = 0;
int loadFormFile = 0;
int titleProcesses = 0;
char str[100] = "";

void addOneSnapShot(snapshot* newSnapShotFromFile)
{
	LogEvent("create one snapShot");
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);

	newSnapShot = (snapshot*)malloc(sizeof(snapshot));
	if (!newSnapShot)
	{
		LogError(strerror(GetLastError()));
		exit(1);
	}

	
	addProcess(NULL);  //enter to the function to get process (head_pro)

	//Enter only if it does not download from a file
	if (loadFormFile == 0)
	{
		sprintf(str, "%d.%d.%d/%d:%d:%d", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

		GetProcessesInfo(); //creates a linked list of processors
		SortingBetweenTwoProcessCountDLL();
		PrintCount();
		newSnapShot->myprocess = PROCESS_Head;
		newSnapShot->countOfProcess = PROCESS_Tail->countProcess;
	}
	else
	{
		newSnapShot = newSnapShotFromFile;
	}

	++countOfSnapsNumber;
	newSnapShot->countSnapsNumber = countOfSnapsNumber;
	strcpy(newSnapShot->timeOfSnapshot, str);
	newSnapShot->next = NULL;
	if (snapshot_Head == NULL)  // create sort list of snapshot
	{

		snapshot_Head = newSnapShot;
		snapshot_Tail = newSnapShot;
		newSnapShot->prev = NULL;
	}
	else
	{
		snapshot_Tail->next = newSnapShot;
		newSnapShot->prev = snapshot_Tail;
		snapshot_Tail = newSnapShot;
	}


		headerSnapShotDetails();

		firstTimeInFile = 0;
		char* temporaryHTML = displayProcessesInTable(newSnapShot);  //create dynamic process table
		char* temporaryTitle = displayProcessesInTitle(newSnapShot); // create dynamic process title
		char* linkToSample = dynamicTitleHtml("index2.html", temporaryHTML, temporaryTitle); 
		free(temporaryHTML);

		firstTimeInFile = 0;


		char* dynamicSnap = displaySnapShotInTable(newSnapShot, linkToSample, addingDll(newSnapShot), memoryAverage(newSnapShot));
        free(linkToSample);
		char* nameF = dynamicHtml("index.html", dynamicSnap,NULL);
	
		
}




void headerSnapShotDetails()
{
	snapShotHeaderFile->versionSnapShot = versionOfSnapShot;
	snapShotHeaderFile->countSnapshot = snapshot_Tail->countSnapsNumber;
	snapShotHeaderFile->reserve[0];
}





char* displaySnapShotInTable(snapshot* snapShot_html,char* NameProcessHtml,int countDLLInSnapHTML,SIZE_T sizeOfMemoryHTML) {

	char* lineInTable = (char*)malloc(sizeof(int)*100);
	
	if (!lineInTable)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	sprintf(lineInTable, "<tr>\n<td> %d </td>\n<td><a href =\"%s\" >Sample%d</a></td>\n<td> %d </td>\n<td> %d </td>\n<td> %d </td>\n</tr>\n", snapShot_html->countSnapsNumber, NameProcessHtml, snapShot_html->countSnapsNumber, snapShot_html->countOfProcess, countDLLInSnapHTML, sizeOfMemoryHTML);
	return lineInTable;
		

}

char* displayDLLSInProcess(PROCESS* htmlProcess) {
	DLLName* DLLOption = htmlProcess->dll;
	char* lineInTable = (char*)malloc(sizeof(DLLName) +200);
	char* origin = lineInTable;
	if (!lineInTable)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	char* allTheOptions = (char*)malloc(sizeof(DLLName)* htmlProcess->numbersOfDLL+10000);
	if (!allTheOptions)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	allTheOptions[0] = NULL;
	while (DLLOption != NULL)
	{

		sprintf(lineInTable, "<option> %s </option>\n", DLLOption->nameOfDLL);
		DLLOption = DLLOption->next;
		strcat(allTheOptions, lineInTable);
	   
	    
	}

	free(origin);
	return allTheOptions;

}

char* displayProcessesInTable(snapshot* snapShot_html) {
	PROCESS* processWithBigMemory = theBiggestMemory(snapShot_html);

	PROCESS* process = snapShot_html->myprocess;
	char* lineInTable = (char*)malloc(sizeof(PROCESS)*100000);
	if (!lineInTable)
	{
		LogError(strerror(GetLastError()));
		return 1;
	}
	char* allTheProcesses = (char*)malloc(sizeof(PROCESS) * snapShot_html->countOfProcess + 10000000);
	if (!allTheProcesses)
	{
		LogError(strerror(GetLastError()));
		return 1;
	}
	allTheProcesses[0] = NULL;
	char* optionOfDLL = NULL;
	while (process != NULL)
	{

		if (processWithBigMemory->WorkingSetSize == process->WorkingSetSize) {

			optionOfDLL = displayDLLSInProcess(process);
			lineInTable[0] = "";
			sprintf(lineInTable, "<tr>\n<td> %s </td>\n<td> %lu </td>\n<td> %lu </td>\n<td> %llu <i class=\"fa fa-warning\" style=\"color:red\"> </i></td>\n<td> %llu </td>\n<td> %llu </td>\n<td> %llu </td>\n<td> %d </td>\n<td><select>\n<option selected>dll's list</option>\n%s</select></td>\n</tr>", process->nameOfProcess, process->processId, process->PageFaultCount, process->WorkingSetSize, process->QuotaPagedPoolUsage, process->QuotaPeakPagedPoolUsage, process->PagefileUsage, process->numbersOfDLL, optionOfDLL);

	    }
		else
		{
			optionOfDLL = displayDLLSInProcess(process);
			lineInTable[0] = "";
			sprintf(lineInTable, "<tr>\n<td> %s </td>\n<td> %lu </td>\n<td> %lu </td>\n<td> %llu </td>\n<td> %llu </td>\n<td> %llu </td>\n<td> %llu </td>\n<td> %d </td>\n<td><select>\n<option selected>dll's list</option>\n%s</select></td>\n</tr>", process->nameOfProcess, process->processId, process->PageFaultCount, process->WorkingSetSize, process->QuotaPagedPoolUsage, process->QuotaPeakPagedPoolUsage, process->PagefileUsage, process->numbersOfDLL, optionOfDLL);
		}
		process = process->next;
		strcat(allTheProcesses, lineInTable);

	}
	free(lineInTable);
	free(optionOfDLL);
	return allTheProcesses;


}
char* displayProcessesInTitle(snapshot* snapShot_html) {
	titleProcesses = 1;
	char* lineInTable = (char*)malloc(100);
	lineInTable[0] = NULL;
	if (!lineInTable)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	sprintf(lineInTable, "<h1> Samples List Number : %d At %s </h1>", snapShot_html->countSnapsNumber, snapShot_html->timeOfSnapshot);
	return lineInTable;


}







PROCESS* theBiggestMemory(snapshot* snapShot_html)
{
	PROCESS* theProcess = snapShot_html->myprocess;
	PROCESS* ret = "";
	SIZE_T theBiggesMemory = snapShot_html->myprocess->WorkingSetSize;


	while (theProcess != NULL)
	{
		if (theProcess->WorkingSetSize > theBiggesMemory)
			theBiggesMemory = theProcess->WorkingSetSize;
		ret = theProcess;
		theProcess= theProcess->next;
	}



	return ret;
}


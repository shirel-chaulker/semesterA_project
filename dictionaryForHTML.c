#include <stdio.h>
#include <string.h>
#include "log.h"
#include "Structs.h"
#include "oneSnapShot.h"
#include "dictionaryFunctions.h"
#include "MemoryFunction.h"
#include "homePageHTML.h"
#include "homePageDLL.h"
#pragma warning(disable:4996)



extern PROCESS* sortListProcess = NULL;
int countDLLPageHTML = 0;
char* dynamicNav(int DLLCountHTML, int ProceessCountHTML, SIZE_T MemoryAvgHTML);
char* dynamicDLLTable(dictionaryDLL* D_DLLHeadHtml);
char* dynamicNavHtml(char* nameOfFile, char* addString);
char* dynamicTitleProcessesUsed(dictionaryDLL* oneDictionaryDLL);
char* dynamicTableProcessesUsed(dictionaryDLL* oneDictionaryDLL);

void HtmlPage()
{
	countOfCreateFileIndex3 = 0;
	addProcess(NULL); //reset the list

	addDictionaryDLL(NULL, NULL); //reset in the function and she gets 2 parameters

	dictionaryProcess(snapshot_Head); // get single value
	sortListProcess = PROCESS_Head;
	int b = PROCESS_Tail->countProcess;
	dictionaryDLLFunction(sortListProcess);
	int a = dictionaryDLL_Tail->countDictionaryDLL;
	SIZE_T c = (SIZE_T)memoryAvgForALLSnapshot(); //get memory avg
	char* dataNav = dynamicNav(a,b,c);
	firstTimeHomePage = 1;
	firstTimeInFile = 1;
	dynamicNavHtml("index.html",dataNav);

	dictionaryDLL* currDD = dictionaryDLL_Head;
	firstTimeInFile = 0;
	while (currDD != NULL)
	{
		char* titleDLL = dynamicTitleProcessesUsed(currDD);
		char* tableDLL = dynamicTableProcessesUsed(currDD);
		dynamicTitleHtml("index3.html", tableDLL, titleDLL);
		firstTimeInFile = 0;
		currDD = currDD->next;
	}

	char* nameF = dynamicHtml("index.html",dynamicDLLTable(dictionaryDLL_Head), NULL);
}



char* dynamicNav(int DLLCountHTML, int ProceessCountHTML, SIZE_T MemoryAvgHTML)
{
	char* dataNav = (char*)malloc(sizeof(long));
	dataNav[0] = NULL;
	if (!dataNav)
	{
		LogError(strerror(GetLastError()));
		return ;
	}
	sprintf(dataNav,"\n<div> Dll's cnt: %d </div>\n<div> Processes cnt: %d </div>\n<div> Memory avg: %llu </div>\n", DLLCountHTML, ProceessCountHTML, MemoryAvgHTML);

	return dataNav;
}




char* dynamicDLLTable(dictionaryDLL* D_DLLHeadHtml)
{
	
	dictionaryDLL* currDictionaryDLL = dictionaryDLL_Head;
	char* dataDLLTable = (char*)malloc(500);
	
	char* allTheOptions = (char*)malloc(sizeof(dictionaryDLL) * dictionaryDLL_Tail->countDictionaryDLL+100);
	if (!allTheOptions)
	{
		LogError(strerror(GetLastError()));
		return;
	}
	allTheOptions[0] = NULL;
	while (currDictionaryDLL != NULL)
	{
		countDLLPageHTML++;

	    if (!dataDLLTable)
	    {
			LogError(strerror(GetLastError()));
	    	return;
	    }
		sprintf(dataDLLTable, "\n<tr>\n<td> %s </td >\n<td ><a href = \"useDll_%d.html\" >dll%d.html</a></td>\n</tr>\n", currDictionaryDLL->nameOfDLL, countDLLPageHTML, countDLLPageHTML);

		currDictionaryDLL = currDictionaryDLL->next;
		strcat(allTheOptions, dataDLLTable);
	}
	free(dataDLLTable);
	return allTheOptions;
}

char* dynamicTitleProcessesUsed(dictionaryDLL* oneDictionaryDLL)
{

	char* titelProcesses = (char*)malloc(100);
	titelProcesses[0] = NULL;
	if (!titelProcesses)
	{
		LogError(strerror(GetLastError()));
		return;
	}
	sprintf(titelProcesses, "<h1> %d process used </h1>", oneDictionaryDLL->dictionaryProcessTail->countDictionaryProcess);

	return titelProcesses;

}


char* dynamicTableProcessesUsed(dictionaryDLL* oneDictionaryDLL)
{
	LogEvent("start to make a new table");
	S_dictionaryProcess* processesOfDDLL = oneDictionaryDLL->dictionaryProcessUsed;
	char* tableProcesses = (char*)malloc(10000);
	tableProcesses[0] = NULL;
	char* allTheOptions = (char*)malloc(sizeof(S_dictionaryProcess)* oneDictionaryDLL->dictionaryProcessTail->countDictionaryProcess + 100000);
	allTheOptions[0] = NULL;
	if (!allTheOptions)
	{
		LogError(strerror(GetLastError()));
		return;
	}
	while (processesOfDDLL != NULL)
	{

	     if (!tableProcesses)
	     {
			 LogError(strerror(GetLastError()));
	     	return;
	     }
	     sprintf(tableProcesses, "\n<tr>\n<td><div class=\"namedll\">%d </div></td>\n<td><div class=\"linkdll\"> %s </div>\n</td></tr>\n", processesOfDDLL->countDictionaryProcess, processesOfDDLL->nameOfProcess);
		 processesOfDDLL = processesOfDDLL->next;
		 strcat(allTheOptions, tableProcesses);
	}
	free(tableProcesses);
	return allTheOptions;

}






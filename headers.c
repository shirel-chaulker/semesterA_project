#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include "log.h"
#include "resetCollectionsFile.h"
#include "structHeaderFunction.h"
#pragma warning(disable:4996)


int restet = 0;
void headerMalloc()
{
	snapShotHeaderFile = (snapShotHeader*)malloc(sizeof(snapShotHeader));
	if (!snapShotHeaderFile)
	{
		LogError(strerror(GetLastError()));
		return;
	}

	processHeaderFile = (processHeader*)malloc(sizeof(processHeader));
	if (!processHeaderFile)
	{
		LogError(strerror(GetLastError()));
		return;
	}


	DLLHeaderFile = (DLLNameHeaders*)malloc(sizeof(DLLNameHeaders));
	if (!DLLHeaderFile)
	{
		LogError(strerror(GetLastError()));
		return;
	}

	if (restet == 1)
	{
		restet = 0;
		free(snapShotHeaderFile);
		free(processHeaderFile);
		free(DLLHeaderFile);
	}

}

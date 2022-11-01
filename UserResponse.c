#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "Structs.h"
#include "fileFunction.h"
#include "oneSnapShot.h"
#include "resetCollectionsFile.h"
#include "structHeaderFunction.h"
#include "homePageHTML.h"
#include "dictionaryFunctions.h"
#include "homePageDLL.h"
#include "resetCollectionsFile.h"
#pragma warning(disable:4996)


int userResponse = 0;

int main()
{
	int HTMLUsed = 0;
	firstTimeHomePage = 0;
	headerMalloc();
	
	while (userResponse != 9)
	{

		printf("Please type a number:\n 1 Take One SnapShot\n 2 Take 20 SnapShots\n 3 Start Long SnapShot\n 4 End Long SnapShot\n 5 Generate HTML Report\n 6 Reset Collections\n 7 Save in File\n 8 Load from File\n 9 Quit\n");

		scanf("%d", &userResponse);
		switch (userResponse) {
		case 1:

			addOneSnapShot(NULL);
			LogEvent("the system take one snapShot");
			break;

		case 2:

			addOneSnapShot(NULL);
			LogEvent("the system take 20 snapShot");
			break;
		case 3:

			
			addOneSnapShot(NULL);
			LogEvent("the system is starting long snapShot");
			break;

		case 5:
			HtmlPage();
			HTMLUsed = 1;
			LogEvent("creating a html report");
			break;
		case 6:
			
			if (HTMLUsed == 0) {
				resetCollections(snapshot_Head);
			}
			else {
				deleteDictionaryDLLAndPro();
				resetCollections(snapshot_Head);
				HTMLUsed = 0;
			}
			LogEvent("start to reset collection");

			break;

		case 7:

			uploadSnapToFile();
			LogEvent("save in file");
			break;

		case 8:
			
			loadSnapFromFile();
			LogEvent("load from files");
			break;

		case 9:
			countOfCreateFileIndex2 = 0;
			countOfCreateFileIndex3 = 0;
			firstTimeInFile = 0;
			firstTimeHomePage = 0;

			if (HTMLUsed == 0) {
				resetCollections(snapshot_Head);
			}
			else {
				deleteDictionaryDLLAndPro();
				resetCollections(snapshot_Head);
				HTMLUsed = 0;
			}

			LogEvent("the program is deleted");
			break;
		}


	}
	return 0;
}








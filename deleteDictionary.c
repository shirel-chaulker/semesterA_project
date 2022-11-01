#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include "log.h"
#include "homePageHTML.h"
#include "resetCollectionsFile.h"
#pragma warning(disable:4996)

extern int 	numberOfIndex = 0;

void deleteDictionaryDLLAndPro()
{
	saveInToFileHTML(readFromFile());
	dictionaryDLL* currDictionary = dictionaryDLL_Head;
	dictionaryDLL* OldCurrDictionary;
	S_dictionaryProcess* currDictionaryPro = currDictionary->dictionaryProcessUsed;
	S_dictionaryProcess* OldCurrDictionaryPro;

	while (currDictionary != NULL) {

		currDictionaryPro = currDictionary->dictionaryProcessUsed;
		while (currDictionaryPro != NULL) {

			OldCurrDictionaryPro = currDictionaryPro;
			currDictionaryPro = currDictionaryPro->next;
			free(OldCurrDictionaryPro);
		}
		OldCurrDictionary = currDictionary;
		currDictionary = currDictionary->next;
		free(OldCurrDictionary);
	}

}
















	

	
	
		



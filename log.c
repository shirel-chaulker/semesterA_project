#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "log.h"
#pragma warning (disable:4996)

void log(char message[1000])
{
	FILE* f = fopen("projectA.log", "a");  // open a file for logs
	if (!f)
	{
		LogError(strerror(GetLastError()));

	}
	else
	{
		time_t t;
		time(&t);

		struct tm* timeinfo;
		timeinfo = localtime(&t);
		char str[100];

		sprintf(str, "%d.%d.%d:%d:%d:%d -%s", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
		fputs("\n", f);
		fputs(str, f);
		fclose(f);
	}

}





void LogError(char message[100])
{

	char newmessage[100];
	sprintf(newmessage, "error - %s", message);
	log(newmessage);

}
void LogEvent(char message[100])
{
	char events[100];
	sprintf(events, "event - %s", message);
	log(events);
}

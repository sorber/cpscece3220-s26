#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bank.h"
#include <stdbool.h>

#define MAX_LINE 1024


char *get_line(char *buf, size_t bufsize);




int main(int argc, char **argv)
{
	//pthread_t t;
	
	bank_init(0); //initial balance is zero.

	while (1)
	{
		char buffer[MAX_LINE + 1];

		printf("prompt> ");
		fflush(stdout);
		// make sure the prompt shows up...probably unnecessary, but without it you don't have any guarantee that the prompt will be printed before scanf is called.

		// read command
		if (NULL == get_line(buffer, MAX_LINE))
			break;
		
	
		// use strtok_r to make it thread safe
		char *saveptr;
		char *cmd = strtok_r(buffer, " ", &saveptr);
		if (cmd == NULL)
			continue;
		char *val = strtok_r(NULL, " ,\t\n", &saveptr);
		int value = (val != NULL ? atoi(val) : -1);

		// respond to commands
		int response;

		response = bank_do_command(cmd, value);
		
		
		if (response >= 0)
		{
			printf("Executed(%s). New balance = $%d\n", cmd, response);
			continue;
		}
		if (strcmp(cmd, "exit") == 0)
		{
			break;
		}

		if (strcmp(cmd, "help") == 0)
		{
			printf("Help for our bank account demo.\n"
				   "\tFORMAT:\t\tcommand [value]\n\n"
				   "\tRecognized commands:\n"
				   "\tdeposit\t\tadd [value] dollars to the balance.\n"
				   "\twithdraw\tsubtract [value] dollars from the balance.\n"
				   "\tbalance\t\tprint out the current balance.\n"
				   "\texit\t\tquit the program.\n\n");
			continue;
		}
		printf("Unrecognized or invalid command (cmd=%s, val=%d), try \"help\"\n", cmd, value);
		// unlock here, or do more fine-grained locking
		// if you want to sqeeze out a little more performance.
	}
	printf("Ok. we're all done...Bye.\n");
	return 0;
}

char *get_line(char *buf, size_t bufsize)
{
	char *p = fgets(buf, bufsize, stdin);

	if (p != NULL)
	{
		size_t last = strlen(buf) - 1;

		if (buf[last] == '\n')
			buf[last] = '\0';
	}
	return p;
}

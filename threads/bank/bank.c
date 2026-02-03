#include <string.h>
#include "bank.h"

static int current_balance;


int bank_init(int initial_balance)
{
	int result = RESULT_SUCCESS;
	if (initial_balance < 0) {
		result = ERR_INVALID_ACTION;
	} else {
		current_balance = initial_balance;
	}
	return result;
}

//performs a command on the bank account.
//for recognized commands, the function
//    returns the current balance, whether or not the requested
//    command was performed.
//returns -1 if the command wasn't recognized.
int bank_do_command(char *command, int value)
{
	int result = ERR_UNKNOWN;
	if (strcmp(command, "balance") == 0)
		result = current_balance;
	if (strcmp(command, "deposit") == 0)
	{
		if (value < 0) {
			result=ERR_INVALID_ACTION; //generic error return
		} else {
			current_balance += value;
			result=current_balance;
		}
	}
	if (strcmp(command, "withdraw") == 0)
	{
		if (value < 0 || current_balance < value) {
			result = ERR_INVALID_ACTION;
		} else {
			current_balance -= value;
			result= current_balance;
		}
	}
	return result;
}

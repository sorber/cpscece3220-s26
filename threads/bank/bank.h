#ifndef BANK_H
#define BANK_H

#define ERR_UNKNOWN (-1)
#define ERR_INVALID_ACTION (-2)
#define RESULT_SUCCESS (1)

int bank_init(int initial_balance);

int bank_do_command(char *command, int value);

#endif

#include "shell.h"

/**
 * command_not_found - prints the specified error message when a
 * command does not exist
 * @prog: the program name
 * @command: the command name
 */
void command_not_found(char *prog, char *command)
{
	int prog_len, cmd_len;
	char *mid = ": 1: ";
	char *end = ": not found\n";

	prog_len = strlen(prog);
	cmd_len = strlen(command);

	/* print error message to stdout */
	write(1, prog, prog_len);
	write(1, mid, 5);
	write(1, command, cmd_len);
	write(1, end, 12);

}

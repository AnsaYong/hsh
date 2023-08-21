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

	prog_len = _strlen(prog);
	cmd_len = _strlen(command);

	/* print error message to stdout */
	write(STDERR_FILENO, prog, prog_len);
	write(STDERR_FILENO, mid, 5);
	write(STDERR_FILENO, command, cmd_len);
	write(STDERR_FILENO, end, 12);

}

/**
 * invalid_exit_arg - prints a message if the argument for exit is negative
 * @arg: arg provided to exit
 */
void invalid_exit_arg(char *arg)
{
	int arg_len;

	arg_len = _strlen(arg);

	/* print error message to stdout */
	write(STDERR_FILENO, "./hsh", 5);
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, "exit", 4);
	write(STDERR_FILENO, ": Illegal number: ", 18);
	write(STDERR_FILENO, arg, arg_len);
	write(STDERR_FILENO, "\n", 1);
}

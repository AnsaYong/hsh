#include "shell.h"

/**
 * read_cmd_line - get commands from stdin entered by the user
 * in interactive mode
 *
 * Return: a pointer to the string with user commands
 */
char *read_cmd_line(void)
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;

	chars_read = getline(&buffer, &buffer_size, stdin);
	/*chars_read = _getline(&buffer);*/

	if (chars_read == -1)
	{
		/* only print new line before exiting if input is from terminal */
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		free(buffer);
		buffer = NULL;
		exit(EXIT_SUCCESS);
	}

	if (chars_read > 0 && buffer[chars_read - 1] == '\n')
	{
		buffer[chars_read - 1] = '\0';
	}

	return (buffer);
}

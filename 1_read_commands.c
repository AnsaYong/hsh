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
	/* chars_read = _getline(&buffer, &buffer_size, STDIN_FILENO);*/

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

/**
 * _getline - reads user input
 * @lineptr: stores the user's input
 * @n: buffer size
 * @fd: file descriptor to read data from
 *
 * Return: number of characters read
 */

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	int ch;
	size_t pos = 0, capacity = *n;
	char *new_lineptr;

	if (lineptr == NULL || n == NULL || fd < 0)
		return (-1);  /* Invalid arguments */

	/* Allocate initial memory for the line */
	if (*lineptr == NULL)
	{
		*lineptr = malloc(capacity);
		if (*lineptr == NULL)
			return (-1);  /* Memory allocation error */
	}

	while (read(fd, &ch, 1) == 1)
	{
		if (pos + 1 >= capacity)
		{
			capacity *= 2;
			new_lineptr = realloc(*lineptr, capacity);
			if (new_lineptr == NULL)
			{
				free(*lineptr);
				return (-1);  /* Memory allocation error */
			}
			*lineptr = new_lineptr;
			*n = capacity;
		}
		(*lineptr)[pos++] = ch;
		if (ch == '\n')
			break;
	}
	if (pos == 0)
		return (-1);  /* No characters read */
	(*lineptr)[pos] = '\0';  /* Null-terminate the string */

	return (pos);  /* Return the number of characters read */
}

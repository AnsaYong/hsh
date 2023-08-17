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
	/* chars_read = _getline(&buffer);*/

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
 * @buffer: stores the user's input
 *
 * Return: number of characters read
 */
ssize_t _getline(char **buffer)
{
	static char func_buff[MAX_CHARS];
	size_t pos = 0, chars_read = 0, cmd_size = 0, buff_size = 0;
	char current_char;
	int line_complete = 0;
	*buffer = NULL;

	while (!line_complete)
	{
		if (pos >= chars_read)  /* check if more data needs to be read */
		{
			chars_read = read(STDIN_FILENO, func_buff, MAX_CHARS);
			if (chars_read <= 0)    /* end of input or an error occurred */
			{
				if (cmd_size == 0)      /* No characters read, return chars_read */
					return (chars_read);
				line_complete = 1;      /* Partial line read, indicate completion */
			}

			pos = 0;
		}
		current_char = func_buff[pos++];

		if (cmd_size >= buff_size)      /* check if buffer needs to be resized */
		{
			buff_size = (buff_size == 0) ? MAX_CHARS : buff_size * 2;
			*buffer = malloc(buff_size);
			if (*buffer == NULL)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
		}
		(*buffer)[cmd_size++] = current_char;   /* Append the current char */
		if (current_char == '\0')       /* check if we reached end of the string */
		{
			line_complete = 1;
			(*buffer)[cmd_size - 1] = '\0';
		}
	}
	return (cmd_size - 1);  /* Exclude the null-terminator */
}

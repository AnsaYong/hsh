#include "shell.h"

/**
 * _strtok - a strtok-like function that maintans state between calls
 * @str: string to be tokenized
 * @sep: word(s)delimiter
 * @end: a static pointer variable used to maintain state between calls.
 * It gets updated as the string is tokenized
 *
 * Return: address from which tokenization should continue on next call
 */
char *_strtok(char *str, const char *sep, char **end)
{
	char *token_start;

	if (str != NULL)
		*end = str;

	/* skip leading delimiters */
	while (**end != '\0' && strchr(sep, **end) != NULL)
		(*end)++;

	if (**end == '\0')
		return (NULL);

	token_start = *end;
	while (**end != '\0' && strchr(sep, **end) == NULL)
		(*end)++;

	if (**end != '\0')
		*(*end)++ = '\0';

	return (token_start);
}

/**
 * strip_white_spaces - remove all white from the front, middle and end of a
 * command, only leaving single spaces between words
 * @str: string containing user command
 */
void strip_white_spaces(char **args_arr, int numb_args)
{
	int i, j = 0, k;
	char *str = NULL;
	char last_char = ' ';
	int len = strlen(str);

	for (k = 0; k < numb_args; k++)
	{
		str = args_arr[k];
		for (i = 0; i < len; i++)
		{
			if (str[i] == ' ')
			{
				if (last_char != ' ')
				{
					str[j++] = str[i];
					last_char = ' ';
				}
			}
			else
			{
				str[j++] = str[i];
				last_char = str[i];
			}
		}

		/* remove trailing spaces */
		if (j > 0 && str[j - 1] == ' ')
		{
			str[i - 1] = '\0';
		}
		else
		{
			str[j] = '\0';
		}
	}
}

/**
 * is_all_spaces - checks if the command line only has spaces
 * @line: pointer to user command / command line
 *
 * Return: 1 if command line only has spaces, 0 otherwise
 */
int is_all_spaces(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n' && *line != '\t')
		{
			return (0);
		}
		line++;
	}

	return (1);
}

/**
 * _getline - reads user commands
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

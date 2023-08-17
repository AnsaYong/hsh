#include "shell.h"

/**
 * _strdup - copies the contents of a char array to another char array
 * @str: pointer to array whose content is to be copied
 *
 * Return: pointer to the new array
 */
char *_strdup(char *str)
{
	(void)str;
	return (NULL);
}

/**
 * _strlen - calculates the length of a string
 * @str: null-terminated string
 *
 * Return: length of string, len
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return(len);
}

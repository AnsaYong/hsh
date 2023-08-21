#include "shell.h"

/**
 * _strdup - copies the contents of a char array to another char array
 * @str: pointer to array whose content is to be copied
 *
 * Return: pointer to the new array
 */

char *_strdup(char *str)
{
	int str_len = 0;
	int i;
	char *dup;

	if (str == NULL)
		return (NULL);

	while (str[str_len] != '\0')
		str_len++;

	dup = (char *)malloc(sizeof(char) * (str_len + 1));

	if (dup == NULL)
		return (NULL);

	for (i = 0; i < str_len; i++)
		dup[i] = str[i];

	dup[str_len] = '\0';

	return (dup);
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

	return (len);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination string/address
 * @src: source string/address
 *
 * Return: Nothing
 */

void _strcat(char *dest, char *src)
{
	size_t dest_len, src_len, i;

	dest_len = _strlen(dest);
	src_len = _strlen(src);

	for (i = 0; i < src_len; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0';
}

/**
 * _strchr - Search a given substring in a main string
 * @s: Main string
 * @c: The substring to search
 *
 * Return: Pointer to the searched substring
*/

char *_strchr(const char *s, const char c)
{
	while (*s != '\0')
	{
	if (*s == c)
		return ((char *)s);
	s++;
	}

	if (*s == c)
		return ((char *)s);

	return (NULL);
}

/**
 * _atoi - Convert strings to long integers
 * @str: Main string
 *
 * Return: long integers
*/

int _atoi(const char *str)
{
	int i = 0, num = 0;

	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

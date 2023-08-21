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
	char *str_dup;

	if (str == NULL)
		return (NULL);

	while (str[str_len] != '\0')
		str_len++;

	str_dup = malloc(sizeof(char) * (str_len + 1));
	if (str_dup == NULL)
		return (NULL);

	for (i = 0; i < str_len; i++)
		str_dup[i] = str[i];

	str_dup[str_len] = '\0';

	return (str_dup);
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
 * @s1: destination string/address
 * @s2: source string/address
 */
void _strcat(char *s1, char *s2)
{
	size_t s1_len, s2_len, i;

	s1_len = _strlen(s1);
	s2_len = _strlen(s2);

	for (i = 0; i < s2_len; i++)
	{
		s1[s1_len + i] = s2[i];
	}

	s1[s1_len + i] = '\0';
}

/**
 * _strchr - search a given substring in a main string
 * @s: main string
 * @c: substring to search
 *
 * Return: pointer to the searched substring
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

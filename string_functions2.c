#include "shell.h"

/**
 * _strcpy - Copy strings from source to destination
 * @destination: string 1
 * @source: string 2
 *
 * Return: return pointer to destination string
*/

char *_strcpy(char *destination, const char *source)
{
		char *ptr = destination;

	if (destination == NULL)
		return (NULL);

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';

	return (ptr);
}

/**
 * _strcmp - compares two strings
 * @str1: string 1
 * @str2: string 2
 *
 * Return: integer indicating the outcome of the comparison
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * compare - Compare strings for _strstr() function
 * @main_str: Main string
 * @search_str: String to compare with the main string
 *
 * Return: Pointer to the searched string
*/

int compare(const char *main_str, const char *search_str)
{
	while (*main_str && *search_str)
	{
		if (*main_str != *search_str)
			return (0);

		main_str++;
		search_str++;
	}

	return (*search_str == '\0');
}

/**
 * _strstr - Search a given substring in a main string
 * @main_str: Main string
 * @search_str: The substring to search
 *
 * Return: Pointer to the searched substring
*/
const char *_strstr(const char *main_str, const char *search_str)
{
	while (*main_str != '\0')
	{
		if ((*main_str == *search_str) && compare(main_str, search_str))
			return (main_str);

		main_str++;
	}

	return (NULL);
}

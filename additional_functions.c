#include "shell.h"
#include <errno.h>

/**
 * _realloc - reallocates a memory block
 * @old_ad: pointer to the memory previously allocated using malloc
 * @new_size: size, in bytes, of the new memory block
 * @old_size: size, in byes, of the allocated space for old_ad
 *
 * Return: pointer to newly allocated memory
 */
void *_realloc(void *old_ad, size_t old_size, size_t new_size)
{
	void *new_ad = NULL;
	char *src, *dest;
	size_t i, min_size;

	if (new_size == 0)
	{
		/* equivalent to freeing the memory and returning */
		free(old_ad);
		return (NULL);
	}

	if (old_ad == NULL)
	{
		/* equivalent to malloc(new_size) - old memory doesn't exit */
		return (malloc(new_size));
	}

	/* allocate new block of memory with the new size */
	new_ad = malloc(new_size);
	if (new_ad == NULL)
	{
		return (NULL);
	}

	/* Copy the data from old to new block, up to the min of old and new sizes */
	min_size = (old_size < new_size) ? old_size : new_size;
	src = old_ad;
	dest = new_ad;

	for (i = 0; i < min_size; i++)
		dest[i] = src[i];

	/* free old memory block */
	free(old_ad);

	return (new_ad);
}

/**
 * _getline - reads user input
 * @buffer: stores the user's input
 *
 * Return: number of characters read
 */

int _getline(char **lineptr, size_t *n, FILE *stream)
{
static char line[256];
char *ptr;
unsigned int len;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}

	if (ferror (stream))
		return (-1);

	if (feof(stream))
		return (-1);
     
	fgets(line, 256, stream);

	ptr = strchr(line, '\n');   
	if (ptr)
		*ptr = '\0';

	len = strlen(line);
   
	if ((len+1) < 256)
	{
		ptr = realloc(*lineptr, 256);
		if (ptr == NULL)
			return( -1);
		*lineptr = ptr;
		*n = 256;
	}

   strcpy(*lineptr, line); 
   return (len);
}

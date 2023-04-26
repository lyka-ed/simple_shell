#include "main.h"

/**
 * aux_free - Function that will free a pointer and ineffect address.
 * @pt: address to access pointer to free.
 *
 * Return: 1 if free or Nothing 0.
 */
int aux_free(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}

	return (0);
}



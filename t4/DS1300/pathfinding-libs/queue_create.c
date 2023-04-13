#include <stdlib.h>
#include "queues.h"

/**
 * queue_create - Initializes a queue structure
 *
 * Return: A pointer to the allocated structure, NULL on failure
 */
queue_t *queue_create(void)
{
	queue_t *q = NULL;

	q = calloc(1, sizeof(queue_t));

	if (!q)
		return (NULL);
	
	return q;
}

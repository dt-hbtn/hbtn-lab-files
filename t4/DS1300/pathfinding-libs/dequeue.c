#include <stdlib.h>
#include "queues.h"

/**
 * dequeue - Pops out the front node of a queue
 *
 * @queue: Pointer to the queue
 *
 * Return: A pointer to the data of the poped node, NULL on failure
 */
void *dequeue(queue_t *queue)
{
	void *item = NULL;
	queue_node_t *front = NULL;

	if (!queue)
		return (NULL);
	
	if (!queue->front)
		return (NULL);
	
	front = queue->front;
	item = front->ptr;
	queue->front = front->next;

	if (!queue->front)
	{
		queue->back = NULL;
	}
	else
	{
		queue->front->prev = NULL;

		if (!queue->front->next)
			queue->back = queue->front;
	}

	free(front);
	return (item);
}

#include <stdlib.h>
#include "queues.h"

/**
 * queue_delete - Deallocates a queue
 *
 * @queue: Pointer to the queue to be deleted
 */
void queue_delete(queue_t *queue)
{
	queue_node_t *iterator = NULL, *tmp = NULL;

	if (!queue)
		return;
	
	iterator = queue->front;

	while (iterator)
	{
		tmp = iterator->next;
		free(iterator->ptr);
		free(iterator);
		iterator = tmp;
	}

	queue->front = queue->back = NULL;
	free(queue);
}

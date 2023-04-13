#include <stdlib.h>
#include "queues.h"

/**
 * queue_delete - Deallocates a queue
 *
 * @queue: Pointer to the queue to be deleted
 */
void queue_delete(queue_t *queue)
{
	free(queue);
}

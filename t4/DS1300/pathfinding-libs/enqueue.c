#include <stdlib.h>
#include "queues.h"

/**
 * queue_push_back - Pushes an element at the back of a queue
 *
 * @queue: Pointer to the queue
 * @ptr: Data to store in the new node
 *
 * Return: A pointer to the created node, NULL on failure
 */
queue_node_t *queue_push_back(queue_t *queue, void *ptr)
{
	queue_node_t *node = NULL;

	if (!queue)
		return (NULL);

	node = calloc(1, sizeof(queue_node_t));

	if (!node)
		return (NULL);

	node->ptr = ptr;

	if (!queue->front)
	{
		queue->front = queue->back = node;
	}
	else
	{
		queue->back->next = node;
		node->prev = queue->back;
		queue->back = node;
	}

	return (node);
}

/**
 * queue_push_front - Pushes an element at the front of a queue
 *
 * @queue: Pointer to the queue
 * @ptr: Data to store in the new node
 *
 * Return: A pointer to the created node, NULL on failure
 */
queue_node_t *queue_push_front(queue_t *queue, void *ptr)
{
	queue_node_t *node = NULL;

	if (!queue)
		return (NULL);

	node = calloc(1, sizeof(queue_node_t));

	if (!node)
		return (NULL);

	node->ptr = ptr;

	if (!queue->front)
	{
		queue->front = queue->back = node;
	}
	else
	{
		queue->front->prev = node;
		node->next = queue->front;
		queue->front = node;
	}

	return (node);
}

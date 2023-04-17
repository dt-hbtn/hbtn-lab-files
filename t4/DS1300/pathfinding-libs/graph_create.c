#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - Initializes a graph structure
 *
 * Return: A pointer to the allocated structure, NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph = NULL;

	graph = calloc(1, sizeof(graph_t));

	if (!graph)
		return (NULL);
	
	return (graph);
}

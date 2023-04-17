#include <stdlib.h>
#include "graphs.h"

static inline void
vertex_delete(graph_t *graph, vertex_t *vertex);

/**
 * graph_delete - Deallocates a graph
 *
 * @graph: Pointer to the graph to be deleted
 */
void graph_delete(graph_t *graph)
{
	vertex_t *iterator = NULL, *tmp = NULL;

	if (!graph || !graph->vertices)
		return;
	
	iterator = graph->vertices;

	while (iterator)
	{
		tmp = iterator->next;
		vertex_delete(graph, iterator);
		iterator = tmp;
	}

	free(graph);
}

static inline void
vertex_delete(graph_t *graph, vertex_t *vertex)
{
	edge_t *iterator = NULL, *tmp = NULL;

	if (!graph || !vertex)
		return;
	
	iterator = vertex->edges;

	while (iterator)
	{
		tmp = iterator->next;
		free(iterator);
		iterator = tmp;
	}

	free(vertex->content);
	free(vertex);
	--graph->nb_vertices;
}

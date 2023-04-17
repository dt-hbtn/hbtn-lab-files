#include <stdlib.h>
#include <string.h>
#include "graphs.h"

static inline int
key_in_graph(graph_t *graph, const char *key);

/**
 * graph_add_vertex - Add a vertex in a graph
 *
 * @graph: Pointer to the graph data structure
 * @str: String representing the new vertex
 * @x: X coordinate of the vertex
 * @y: Y coordinate of the vertex
 *
 * Return: A pointer to the created vertex, NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, char const *str, int x, int y)
{
	vertex_t *vertex = NULL, *iterator = NULL;

	if (!graph || !str)
		return (NULL);
	
	if (key_in_graph(graph, str))
		return (NULL);
	
	vertex = calloc(1, sizeof(vertex_t));

	if (!vertex)
		return (NULL);
	
	vertex->index = graph->nb_vertices;
	vertex->x = x;
	vertex->y = y;
	vertex->content = strdup(str);

	if (!vertex->content)
	{
		free(vertex);
		return (NULL);
	}

	++graph->nb_vertices;

	if (!graph->vertices)
	{
		graph->vertices = vertex;
		return (vertex);
	}

	iterator = graph->vertices;

	while (iterator->next)
		iterator = iterator->next;
	
	iterator->next = vertex;
	return (vertex);
}

static inline int
key_in_graph(graph_t *graph, const char *key)
{
	vertex_t *iterator = NULL;

	if (!graph)
		return (0);
	
	if (!graph->vertices)
		return (0);
	
	iterator = graph->vertices;

	while (iterator)
	{
		if (!strcmp(iterator->content, key))
			return (1);
		
		iterator = iterator->next;
	}

	return (0);
}

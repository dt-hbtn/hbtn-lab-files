#include <stdlib.h>
#include <string.h>
#include "graphs.h"

static inline vertex_t
*search_vertex(graph_t *graph, const char *key);

static inline int
connect_vertices(vertex_t *a, vertex_t *b, int weight);

/**
 * graph_add_edge - Add an edge between two vertices
 *
 * @graph: Pointer to the graph data structure
 * @src: String representing the vertex to make the connection from
 * @dest: String representing the vertex to connect to
 * @weight: Weight of the edge
 * @type: Connection type (Unidirectional or bidirectionnal)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(
	graph_t *graph,
	char const *src,
	char const *dest,
	int weight,
	edge_type_t type
)
{
	vertex_t *a = NULL, *b = NULL;

	if (!graph || !src || !dest)
		return (0);

	if (!(a = search_vertex(graph, src)))
		return (0);
	
	if (!(b = search_vertex(graph, dest)))
		return (0);
	
	if (!connect_vertices(a, b, weight))
		return (0);
	
	if (type == BIDIRECTIONAL)
	{
		if (!connect_vertices(b, a, weight))
			return (0);
	}
	
	return (1);
}

static inline vertex_t
*search_vertex(graph_t *graph, const char *key)
{
	vertex_t *iterator = NULL;

	if (!graph || !graph->vertices)
		return (NULL);
	
	iterator = graph->vertices;

	while (iterator)
	{
		if (!strcmp(iterator->content, key))
			return (iterator);
		
		iterator = iterator->next;
	}

	return (NULL);
}

static inline int
connect_vertices(vertex_t *a, vertex_t *b, int weight)
{
	edge_t *edge = NULL, *iterator = NULL;

	if (!a || !b)
		return (0);
	
	edge = calloc(1, sizeof(edge_t));

	if (!edge)
		return (0);
	
	edge->dest = b;
	edge->weight = weight;
	++a->nb_edges;

	if (!a->edges)
	{
		a->edges = edge;
		return (1);
	}
	
	iterator = a->edges;

	while (iterator->next)
		iterator = iterator->next;
	
	iterator->next = edge;
	return (1);
}

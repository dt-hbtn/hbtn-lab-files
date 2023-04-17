CFLAGS = -Wall -Werror -Wextra -pedantic

libqueues.a: dequeue.o enqueue.o queue_delete.o queue_create.o
	ar rcs $@ $^

libgraphs.a: graph_add_edge.o graph_add_vertex.o graph_display.o graph_delete.o graph_create.o
	ar rcs $@ $^

graph_add_edge.o: graph_add_edge.c
	gcc -c graph_add_edge.c $(CFLAGS)

graph_add_vertex.o: graph_add_vertex.c
	gcc -c graph_add_vertex.c $(CFLAGS)

graph_display.o: graph_display.c
	gcc -c graph_display.c $(CFLAGS)

graph_delete.o: graph_delete.c
	gcc -c graph_delete.c $(CFLAGS)

graph_create.o: graph_create.c
	gcc -c graph_create.c $(CFLAGS)

dequeue.o: dequeue.c
	gcc -c dequeue.c $(CFLAGS)

enqueue.o: enqueue.c
	gcc -c enqueue.c $(CFLAGS)

queue_delete.o: queue_delete.c
	gcc -c queue_delete.c $(CFLAGS)

queue_create.o: queue_create.c
	gcc -c queue_create.c $(CFLAGS)

clean:
	rm -f *queue*.o graph*.o libqueues.a libgraphs.a

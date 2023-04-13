libqueues.a: dequeue.o enqueue.o queue_delete.o queue_create.o
	ar rcs $@ $^

dequeue.o: dequeue.c
	gcc -c dequeue.c

enqueue.o: enqueue.c
	gcc -c enqueue.c

queue_delete.o: queue_delete.c
	gcc -c queue_delete.c

queue_create.o: queue_create.c
	gcc -c queue_create.c

clean:
	rm -f *queue*.o libqueues.a

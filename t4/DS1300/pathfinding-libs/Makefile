CC := gcc
AR := ar
CFLAGS := -Wall -Werror -Wextra -pedantic
ARFLAGS := rcs
QUEUE_SRC := $(wildcard *queue*.c)
GRAPH_SRC := $(wildcard graph*.c)
QUEUE_OBJ := $(QUEUE_SRC:.c=.o)
GRAPH_OBJ := $(GRAPH_SRC:.c=.o)

.PHONY: all clean

all: libqueues.a libgraphs.a

libqueues.a: $(QUEUE_OBJ)
	@$(AR) $(ARFLAGS) $@ $^

libgraphs.a: $(GRAPH_OBJ)
	@$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm *.o *.a

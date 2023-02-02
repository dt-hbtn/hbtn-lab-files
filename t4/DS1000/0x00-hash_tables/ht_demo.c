#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ll_node_s
{
    char *key;
    char *value;
    struct ll_node_s *next;
} ll_node_t;

typedef struct ht_s
{
    size_t size;
    ll_node_t **array;
} ht_t;

/*
[0] node1 -> node2
[1] NULL
[2] node1 -> node2 -> node3
*/

ll_node_t *
init_node(const char *key, const char *value)
{
    ll_node_t *new_node = NULL;

    new_node = malloc(sizeof(ll_node_t));
    new_node->key = calloc(strlen(key) + 1, 1);
    strcpy(new_node->key, key);
    new_node->value = calloc(strlen(value) + 1, 1);
    strcpy(new_node->value, value);
    new_node->next = NULL;

    return (new_node);
}

ht_t *
init_ht(size_t size)
{
    ht_t *ht = NULL;

    ht = malloc(sizeof(ht_t));
    ht->size = size;
    ht->array = calloc(size, sizeof(ll_node_t *));

    return (ht);
}


/**
 * hash_djb2 - hash a string for table lookup
 * @str: Input string
 *
 * Return: hash value
 */
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return (hash);
}

/**
 * key_index - hash_djb2 mod size
 * @key: Key string
 * @size: Hash-table size
 *
 * Return: Appropriate index in hash table
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}

void
ht_set(ht_t *ht, const char *key, const char *value)
{
    unsigned long index;
    ll_node_t *ll_ptr = NULL, *new_node = NULL, *pos = NULL;

    index = key_index((const unsigned char *)key, ht->size);

    ll_ptr = ht->array[index];

    if (!ll_ptr)
    {
        new_node = init_node(key, value);
        ht->array[index] = new_node;
    }
    else
    {
        /* check if key already present */
        pos = ll_ptr;

        while (pos)
        {
            if (strcmp(pos->key, key) == 0)
            {
                if (strcmp(pos->value, value) == 0)
                    return;
                
                pos->value = realloc(pos->value, strlen(value) + 1);
                strcpy(pos->value, value);
                return;
            }

            pos = pos->next;
        }

        /* key is not present, insert at start of linked list */
        new_node = init_node(key, value);
        new_node->next = ll_ptr;
        ht->array[index] = new_node;
    }
}

const char *
ht_get(ht_t *ht, const char *key)
{
    unsigned long index;
    ll_node_t *ll_ptr = NULL, *pos = NULL;

    index = key_index((const unsigned char *)key, ht->size);

    ll_ptr = ht->array[index];

    if (!ll_ptr)
        return (NULL);
    
    pos = ll_ptr;

    while (pos)
    {
        if (strcmp(pos->key, key) == 0)
        {
            return pos->value;
        }

        pos = pos->next;
    }

    return (NULL);
}

int main(void)
{
    ht_t *ht = init_ht(42);

    ht_set(ht, "Key1", "Value1");
    ht_set(ht, "Key2", "Value2");
    ht_set(ht, "Key3", "Value3");


    printf("ht[\"Key1\"] = \"%s\"\n", ht_get(ht, "Key1"));
    printf("ht[\"Key2\"] = \"%s\"\n", ht_get(ht, "Key2"));
    printf("ht[\"Key3\"] = \"%s\"\n", ht_get(ht, "Key3"));

    return (0);
}


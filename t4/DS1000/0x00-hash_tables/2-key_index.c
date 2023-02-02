#include "hash_tables.h"

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

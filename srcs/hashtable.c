//
// Created by dbreton on 2/27/17.
//

#include "hashtable.h"
t_hashtable     *create_hash_table(size_t size)
{
    t_hashtable *table;
    size_t      i;

    i = 0;
    if (size == 0)
        return NULL;
    if (!(table = (t_hashtable *)malloc(sizeof(t_hashtable))))
        return (NULL);
    if (!(table->table = (t_entry *)malloc(sizeof(t_entry) * size)))
        return (NULL);
    while (i < size)
    {
        table->table[i] = NULL;
        ++i;
    }
    table->size = size;
    return (table);

}
static size_t          hash(t_hashtable *table, char *key)
{
    size_t              hashval;
    int                 i;

    i = 0;
    while (hashval <ULONG_MAX && key[i] != '\0')
    {
        hashval = hashval << 8;
        hashval += key[i];
        ++i;
    }
    return (hashval % table->size);
}
static t_entry         *create_pair(char *key, void *value)
{
    t_entry             *new_pair;

    if (!(new_pair = (t_entry *)malloc(sizeof(t_entry))))
        return (NULL);
    if (!(new_pair->key = ft_strdup(key)))
        return (NULL);
    new_pair->value = value;
    return (new_pair);
}
void            ht_set(t_hashtable *table, char *key, void *value)
{
    size_t      bin;
    t_entry     *new_pair;

    bin = hash(table, key);
    new_pair = create_pair(key, value);
    if (new_pair)
        table->table[bin] = new_pair;
}
void            *ht_get(t_hashtable *table, char *key)
{
    size_t      bin;
    t_entry     *pair;

    bin = hash(table, key);
    if (!pair || !pair->key)
        return (NULL);
    else
        return (pair->value);
}
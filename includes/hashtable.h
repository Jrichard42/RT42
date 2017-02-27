//
// Created by dbreton on 2/27/17.
//

#ifndef RT42_HASHTABLE_H
#define RT42_HASHTABLE_H

# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <limits.h>

typedef struct  s_entry
{
    char        *key;
    void        *value;
}               t_entry;
typedef struct  s_hashtable
{
    int         size;
    t_entry     **table;
}               t_hashtable;
t_hashtable     *create_hash_table(size_t size);
void            ht_set(t_hashtable *table, char *key, void *value);
void            *ht_get(t_hashtable *table, char *key);

#endif

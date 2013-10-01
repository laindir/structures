/*

Copyright 2012 Carl D Hamann

This file is part of structures.

structures is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

structures is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with structures.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <hash.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _hash
{
	size_t size;
	hashitem *overflow;
	hashitem *data;
};

hash *
hash_create(hashitem *data, size_t size)
{
	hash *hash;

	if(data)
	{
		hash = malloc(sizeof(*hash));
	}
	else
	{
		hash = calloc(1, sizeof(*hash) + sizeof(*data) * size);
	}

	if(hash)
	{
		hash->data = data ? data : (hashitem *)(hash + 1);
		hash->size = size;
		hash->overflow = data;
	}

	return hash;
}

void
hash_destroy(hash *hash)
{
	free(hash);
}

/*
TODO: replace with a real hash function
this is simply a demo designed to help me learn what makes a good hash
this probably a bad selection less for distribution reasons as
that it is easily reversible and therefore easy to select colliding keys
*/
static size_t
hash_defaulthf(const char *key, size_t initial)
{
	size_t h = initial;
	const char *c = key;

	while(*c != 0)
	{
		h ^= *c++;
		/* largest prime p such that p * 255 < 2^32 */
		h *= 16842961;
	}

	return h;
}

enum hash_traverse_result
{
	AVAILABLE,
	FOUND,
	COLLISION,
	FULL
};

static enum hash_traverse_result
hash_traverse(hash *hash, const char *key, hashitem **target, hashitem **parent)
{
	hashitem *desired = &hash->data[hash_defaulthf(key, 0) % hash->size];
	hashitem *pp = desired;
	hashitem *p = desired;
	int differs;

	while(p->key != NULL && (differs = strcmp(p->key, key)) && p->next != NULL && p->next != desired)
	{
		pp = p;
		p = p->next;
	}

	if(target)
	{
		*target = p;
	}

	if(parent)
	{
		*parent = pp;
	}

	if(p->key == NULL)
	{
		return AVAILABLE;
	}
	else if(!differs)
	{
		return FOUND;
	}
	else if(p->next == NULL && hash->overflow->key == NULL)
	{
		return COLLISION;
	}
	else
	{
		return FULL;
	}
}

int
hash_insert(hash *hash, const char *key, void *item)
{
	hashitem *p;
	size_t i;

	switch(hash_traverse(hash, key, &p, NULL))
	{
	case AVAILABLE:
		p->key = key;
		p->data = item;
		break;
	case FOUND:
		p->data = item;
		break;
	case COLLISION:
		hash->overflow->key = key;
		hash->overflow->data = item;
		p->next = hash->overflow;
		for(i = 0; i < hash->size && hash->data[i].key; i++);
		if(i < hash->size)
		{
			hash->overflow = &hash->data[i];
		}
		break;
	default:
		return -1;
	}

	return 0;
}

void *
hash_search(hash *hash, const char *key)
{
	hashitem *p;

	if(hash_traverse(hash, key, &p, NULL) == FOUND)
	{
		return p->data;
	}

	return NULL;
}

void
hash_delete(hash *hash, const char *key)
{
	hashitem *p, *pp;

	if(hash_traverse(hash, key, &p, &pp) == FOUND)
	{
		pp->next = p->next;
		p->key = NULL;
		p->data = NULL;
		p->next = NULL;
		hash->overflow = p;
	}
}

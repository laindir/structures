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

#include <binaryheap.h>
#include <sys/types.h>
#include <stdlib.h>

struct _binaryheap
{
	size_t size;
	size_t count;
	int (*heap_condition)(void *a, void *b);
	void **data;
};

binaryheap *
binaryheap_create(void **data, size_t size, size_t count, int (*heap_condition)(void *a, void *b))
{
	binaryheap *heap;

	if(data)
	{
		heap = malloc(sizeof(*heap));
	}
	else
	{
		heap = calloc(1, sizeof(*heap) + sizeof(*data) * size);
	}

	if(heap)
	{
		heap->data = data ? data : (void **)(heap + 1);
		heap->size = size;
		heap->count = count;
		heap->heap_condition = heap_condition;

		if(count != 0)
		{
			binaryheap_heapify(heap);
		}
	}

	return heap;
}

void
binaryheap_destroy(binaryheap *heap)
{
	free(heap);
}

static size_t
binaryheap_left(size_t i)
{
	return (i << 1) + 1;
}

static size_t
binaryheap_right(size_t i)
{
	return (i << 1) + 2;
}

static size_t
binaryheap_parent(size_t i)
{
	return i == 0 ? 0 : (i - 1) >> 1;
}

int
binaryheap_insert(binaryheap *heap, void *item)
{
	size_t dest;
	size_t par;
	void *temp;



	if(heap->count < heap->size)
	{
		heap->data[heap->count] = item;
		dest = heap->count;
		par = binaryheap_parent(dest);
		while(dest != 0 && heap->heap_condition(heap->data[dest], heap->data[par]) < 0)
		{
			temp = heap->data[dest];
			heap->data[dest] = heap->data[par];
			heap->data[par] = temp;
			dest = par;
			par = binaryheap_parent(dest);
		}
		heap->count++;
		return 0;
	}
	else
	{
		return -1;
	}
}

void *
binaryheap_delete(binaryheap *heap)
{
	void *result;
	void *temp;
	size_t dest;
	size_t l;
	size_t r;
	size_t swap;



	if(heap->count != 0)
	{
		result = heap->data[0];
		heap->data[0] = heap->data[--heap->count];
		dest = 0;
		l = binaryheap_left(dest);
		r = binaryheap_right(dest);

		if(l >= heap->count)
		{
			return result;
		}
		else if(r >= heap->count)
		{
			swap = l;
		}
		else
		{
			swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;
		}

		while(heap->heap_condition(heap->data[swap], heap->data[dest]) < 0)
		{
			temp = heap->data[dest];
			heap->data[dest] = heap->data[swap];
			heap->data[swap] = temp;
			dest = swap;
			l = binaryheap_left(dest);
			r = binaryheap_right(dest);

			if(l >= heap->count)
			{
				return result;
			}
			else if(r >= heap->count)
			{
				swap = l;
			}
			else
			{
				swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;
			}
		}

		return result;
	}
	else
	{
		return NULL;
	}
}

void
binaryheap_heapify(binaryheap *heap)
{
	void *temp;
	size_t i;
	size_t dest;
	size_t l;
	size_t r;
	size_t swap;



/*heap condition always satisfied for leaf nodes*/
/*start with parent of last*/
	i = binaryheap_parent(heap->count - 1);
	do
	{
		dest = i;
		l = binaryheap_left(dest);
		r = binaryheap_right(dest);

		if(l >= heap->count)
		{
			break;
		}
		else if(r >= heap->count)
		{
			swap = l;
		}
		else
		{
			swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;
		}

		while(heap->heap_condition(heap->data[swap], heap->data[dest]) < 0)
		{
			temp = heap->data[dest];
			heap->data[dest] = heap->data[swap];
			heap->data[swap] = temp;
			dest = swap;
			l = binaryheap_left(dest);
			r = binaryheap_right(dest);

			if(l >= heap->count)
			{
				break;
			}
			else if(r >= heap->count)
			{
				swap = l;
			}
			else
			{
				swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;
			}
		}
	} while(i-- > 0);
}

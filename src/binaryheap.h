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

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <sys/types.h>

typedef struct _binaryheap binaryheap;

binaryheap *
binaryheap_create(void **data, size_t size, size_t count, int (*heap_condition)(void *a, void *b));

void
binaryheap_destroy(binaryheap *heap);

int
binaryheap_insert(binaryheap *heap, void *item);

void *
binaryheap_delete(binaryheap *heap);

void
binaryheap_heapify(binaryheap *heap);

#endif

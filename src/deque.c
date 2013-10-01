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

#include <deque.h>
#include <sys/types.h>
#include <stdlib.h>

struct _deque
{
	size_t size;
	size_t back;
	size_t front;
	void **data;
};

deque *
deque_create(void **data, size_t size)
{
	deque *deque;

	if(data)
	{
		deque = malloc(sizeof(*deque));
	}
	else
	{
		deque = calloc(1, sizeof(*deque) + sizeof(*data) * size);
	}

	if(deque)
	{
		deque->size = size;
		deque->back = 0;
		deque->front = 0;
		deque->data = data ? data : (void **)(deque + 1);
	}

	return deque;
}

void
deque_destroy(deque *deque)
{
	free(deque);
}

int
deque_push(deque *deque, void *item)
{
	if((deque->back - deque->front) >= deque->size)
	{
		return -1;
	}

	deque->data[deque->back % deque->size] = item;
	deque->back++;
	return 0;
}

void *
deque_pop(deque *deque)
{
	void *result;

	if((deque->back - deque->front) <= 0)
	{
		return NULL;
	}

	deque->back--;
	result = deque->data[deque->back % deque->size];
	return result;
}

int
deque_unshift(deque *deque, void *item)
{
	if((deque->back - deque->front) >= deque->size)
	{
		return -1;
	}

	deque->front--;
	deque->data[deque->front % deque->size] = item;
	return 0;
}

void *
deque_shift(deque *deque)
{
	void *result;

	if((deque->back - deque->front) <= 0)
	{
		return NULL;
	}

	result = deque->data[deque->front % deque->size];
	deque->front++;
	return result;
}

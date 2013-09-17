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

#ifndef DEQUE_H
#define DEQUE_H

#include <sys/types.h>

typedef struct _deque deque;

deque *
deque_create(void **data, size_t size);

void
deque_destroy(deque *deque);

int
deque_push(deque *deque, void *item);

void *
deque_pop(deque *deque);

int
deque_unshift(deque *deque, void *item);

void *
deque_shift(deque *deque);

#endif

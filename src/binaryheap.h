#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <sys/types.h>

#define DECLARE_BINARYHEAP(type)\
struct type ## _binaryheap\
{\
	size_t size;\
	size_t count;\
	type invalid;\
	type *data;\
	int (*heap_condition)(type a, type b);\
};\
\
struct type ## _binaryheap type ## _binaryheap(type *data, size_t size, size_t count, type invalid, int (*heap_condition)(type a, type b));\
int type ## _value_min_heap_condition(type a, type b);\
int type ## _value_max_heap_condition(type a, type b);\
size_t type ## _binaryheap_left(size_t i);\
size_t type ## _binaryheap_right(size_t i);\
size_t type ## _binaryheap_parent(size_t i);\
int type ## _binaryheap_insert(struct type ## _binaryheap *heap, type item);\
type type ## _binaryheap_delete(struct type ## _binaryheap *heap);\
void type ## _binaryheap_heapify(struct type ## _binaryheap *heap);\

#define DEFINE_BINARYHEAP(type)\
struct type ## _binaryheap type ## _binaryheap(type *data, size_t size, size_t count, type invalid, int (*heap_condition)(type a, type b))\
{\
	struct type ## _binaryheap result;\
\
	result.size = size;\
	result.count = count;\
	result.data = data;\
	result.invalid = invalid;\
	result.heap_condition = heap_condition == 0 ? type ## _value_min_heap_condition : heap_condition;\
\
	if(count != 0)\
	{\
		type ## _binaryheap_heapify(&result);\
	}\
\
	return result;\
}\
\
int type ## _value_min_heap_condition(type a, type b)\
{\
	if(a < b)\
	{\
		return -1;\
	}\
	else if(a > b)\
	{\
		return 1;\
	}\
	else\
	{\
		return 0;\
	}\
}\
\
int type ## _value_max_heap_condition(type a, type b)\
{\
	if(a < b)\
	{\
		return 1;\
	}\
	else if(a > b)\
	{\
		return -1;\
	}\
	else\
	{\
		return 0;\
	}\
}\
\
size_t type ## _binaryheap_left(size_t i)\
{\
	return (i << 1) + 1;\
}\
\
size_t type ## _binaryheap_right(size_t i)\
{\
	return (i << 1) + 2;\
}\
\
size_t type ## _binaryheap_parent(size_t i)\
{\
	return i == 0 ? 0 : (i - 1) >> 1;\
}\
\
int type ## _binaryheap_insert(struct type ## _binaryheap *heap, type item)\
{\
	size_t dest;\
	size_t par;\
	type temp;\
\
\
\
	if(heap->count < heap->size)\
	{\
		heap->data[heap->count] = item;\
		dest = heap->count;\
		par = type ## _binaryheap_parent(dest);\
		while(dest != 0 && heap->heap_condition(heap->data[dest], heap->data[par]) < 0)\
		{\
			temp = heap->data[dest];\
			heap->data[dest] = heap->data[par];\
			heap->data[par] = temp;\
			dest = par;\
			par = type ## _binaryheap_parent(dest);\
		}\
		heap->count++;\
		return 0;\
	}\
	else\
	{\
		return -1;\
	}\
}\
\
type type ## _binaryheap_delete(struct type ## _binaryheap *heap)\
{\
	type result;\
	type temp;\
	size_t dest;\
	size_t l;\
	size_t r;\
	size_t swap;\
\
\
\
	if(heap->count != 0)\
	{\
		result = heap->data[0];\
		heap->data[0] = heap->data[--heap->count];\
		dest = 0;\
		l = type ## _binaryheap_left(dest);\
		r = type ## _binaryheap_right(dest);\
\
		if(l >= heap->count)\
		{\
			return result;\
		}\
		else if(r >= heap->count)\
		{\
			swap = l;\
		}\
		else\
		{\
			swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;\
		}\
\
		while(heap->heap_condition(heap->data[swap], heap->data[dest]) < 0)\
		{\
			temp = heap->data[dest];\
			heap->data[dest] = heap->data[swap];\
			heap->data[swap] = temp;\
			dest = swap;\
			l = type ## _binaryheap_left(dest);\
			r = type ## _binaryheap_right(dest);\
\
			if(l >= heap->count)\
			{\
				return result;\
			}\
			else if(r >= heap->count)\
			{\
				swap = l;\
			}\
			else\
			{\
				swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;\
			}\
		}\
\
		return result;\
	}\
	else\
	{\
		return heap->invalid;\
	}\
}\
\
void type ## _binaryheap_heapify(struct type ## _binaryheap *heap)\
{\
	type temp;\
	size_t i;\
	size_t dest;\
	size_t l;\
	size_t r;\
	size_t swap;\
\
\
\
/*heap condition always satisfied for leaf nodes*/\
/*start with parent of last*/\
	i = type ## _binaryheap_parent(heap->count - 1);\
	do\
	{\
		dest = i;\
		l = type ## _binaryheap_left(dest);\
		r = type ## _binaryheap_right(dest);\
\
		if(l >= heap->count)\
		{\
			break;\
		}\
		else if(r >= heap->count)\
		{\
			swap = l;\
		}\
		else\
		{\
			swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;\
		}\
\
		while(heap->heap_condition(heap->data[swap], heap->data[dest]) < 0)\
		{\
			temp = heap->data[dest];\
			heap->data[dest] = heap->data[swap];\
			heap->data[swap] = temp;\
			dest = swap;\
			l = type ## _binaryheap_left(dest);\
			r = type ## _binaryheap_right(dest);\
\
			if(l >= heap->count)\
			{\
				break;\
			}\
			else if(r >= heap->count)\
			{\
				swap = l;\
			}\
			else\
			{\
				swap = heap->heap_condition(heap->data[l], heap->data[r]) < 0 ? l : r;\
			}\
		}\
	} while(i-- > 0);\
}\

#endif

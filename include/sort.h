#ifndef GUARD_SORT_H
#define GUARD_SORT_H

typedef int (*cmpfun)(const void *, const void *);
int MergeSort(void *data, size_t count, size_t size, cmpfun cmp);

#endif // GUARD_SORT_H

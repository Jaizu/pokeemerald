#include "global.h"
#include "malloc.h"
#include "sort.h"

// Shamelessly ripped from tools/gbagfx/huff.c :P
static int MergeSort_(void *data, size_t count, size_t size, cmpfun cmp, void *buffer)
{
    /*
     * Out-of-place mergesort (stable sort)
     * Returns 1 on success, 0 on failure
     */
    void * leftPtr;
    void * rightPtr;
    void * leftEnd;
    void * rightEnd;
    int i;

    switch (count) {
    case 0:
        // Should never be here
        return 0;

    case 1:
        // Nothing to do here
        break;

    case 2:
        // Swap the two entries if the right one compares higher.
        if (cmp(data, data + size) > 0) {
            memcpy(buffer, data, size);
            memcpy(data, data + size, size);
            memcpy(data + size, buffer, size);
        }
        break;
    default:
        // Merge sort out-of-place.
        leftPtr = data;
        leftEnd = rightPtr = data + count / 2 * size;
        rightEnd = data + count * size;

        // Sort the left half
        if (!MergeSort_(leftPtr, count / 2, size, cmp, buffer))
            return 0;

        // Sort the right half
        if (!MergeSort_(rightPtr, count / 2 + (count & 1), size, cmp, buffer))
            return 0;

        // Merge the sorted halves out of place
        i = 0;
        do {
            if (cmp(leftPtr, rightPtr) <= 0) {
                memcpy(buffer + i * size, leftPtr, size);
                leftPtr += size;
            } else {
                memcpy(buffer + i * size, rightPtr, size);
                rightPtr += size;
            }

        } while (++i < count && leftPtr < leftEnd && rightPtr < rightEnd);

        // Copy the remainder
        if (i < count) {
            if (leftPtr < leftEnd) {
                memcpy(buffer + i * size, leftPtr, leftEnd - leftPtr);
            }
            else {
                memcpy(buffer + i * size, rightPtr, rightEnd - rightPtr);
            }
        }

        // Copy the merged data back
        memcpy(data, buffer, count * size);
        break;
    }

    return 1;
}

int MergeSort(void *data, size_t count, size_t size, cmpfun cmp)
{
    void *buffer = AllocZeroed(count * size);
    
    int result = MergeSort_(data, count, size, cmp, buffer);
    
    FREE_AND_SET_NULL(buffer);
    
    return result;
}

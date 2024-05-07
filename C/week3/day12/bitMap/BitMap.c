#include <stdlib.h>
#include <string.h>
#include "BitMap.h"

BitMap* bitmap_create(size_t bits) {
    BitMap* bm = (BitMap*)malloc(sizeof(BitMap));
    if (!bm)
        return NULL;

	// 计算需要多少个Word
    size_t size = (bits + 31) / 32;
    bm->array = (Word*)malloc(size * sizeof(Word));
    if (!bm->array) {
        free(bm);
        return NULL;
    }

	// 初始化所有位为0
    memset(bm->array, 0, size * sizeof(Word));
    bm->bits = bits;
    return bm;
}

void bitmap_destroy(BitMap* bm) {
    if (bm) {
        free(bm->array);
        free(bm);
    }
}

void bitmap_set(BitMap* bm, size_t n) {
    if (n < bm->bits)
        bm->array[n / 32] |= (1 << (n % 32));
}

void bitmap_unset(BitMap* bm, size_t n) {
    if (n < bm->bits)
        bm->array[n / 32] &= ~(1 << (n % 32));
}

bool bitmap_isset(BitMap* bm, size_t n) {
    if (n < bm->bits)
        return (bm->array[n / 32] & (1 << (n % 32))) != 0;

    return false;
}

void bitmap_clear(BitMap* bm) {
    size_t size = (bm->bits + 31) / 32;
    memset(bm->array, 0, size * sizeof(Word));
}
#include "Map.h"
#include "Vector/Vector.h"

#include <stdlib.h>

struct map_t {
    Vector keys;
    Vector values;
    int (*comparator)(void* key1, void* key2);
    int (*defaultComparator)(void* key1, void* key2, size_t keyTypeSize);
    size_t size;
    size_t keyTypeSize;
    size_t valueTypeSize;
};

int KeyEquals(void* key1, void* key2, size_t keyTypeSize) {
    for (char* k1 = key1, *k2 = key2; keyTypeSize > 0; k1++, k2++) {
        if (*k1 != *k2)
            return 0;

        keyTypeSize--;
    }
    return 1;
}

Map Map_Init(size_t keyTypeSize, size_t valueTypeSize) {
    Map map = malloc(sizeof(struct map_t));
    map->keys = Vec_Init(keyTypeSize);
    map->values = Vec_Init(valueTypeSize);
    map->size = 0;
    map->keyTypeSize = keyTypeSize;
    map->valueTypeSize = valueTypeSize;
    map->comparator = NULL;
    map->defaultComparator = KeyEquals;
    return map;
}

void Map_SetComparator(Map map, int(*comparator)(void *key1, void *key2)) {
    map->comparator = comparator;
}

void Map_Insert(Map map, void* key, void* value) {
    if (Map_ContainsKey(map, key)) return;

    Vec_Append(map->keys, key);
    Vec_Append(map->values, value);
    map->size++;
}

void* Map_Get(Map map, void* key) {
    if (map->comparator == NULL) {
        for (int i = 0; i < map->size; i++) {
            if (map->defaultComparator(key, Vec_Get(map->keys, i), map->keyTypeSize)) {
                return Vec_Get(map->values, i);
            }
        }
    } else {
        for (int i = 0; i < map->size; i++) {
            if (map->comparator(key, Vec_Get(map->keys, i))) {
                return Vec_Get(map->values, i);
            }
        }
    }

    return NULL;
}

void Map_Remove(Map map, void *key) {
    if (map->comparator == NULL) {
        for (int i = 0; i < map->size; i++) {
            if (map->defaultComparator(key, Vec_Get(map->keys, i), map->keyTypeSize)) {
                Vec_Remove(map->values, i);
                Vec_Remove(map->keys, i);
                map->size--;
                return;
            }
        }
    } else {
        for (int i = 0; i < map->size; i++) {
            if (map->comparator(key, Vec_Get(map->keys, i))) {
                Vec_Remove(map->values, i);
                Vec_Remove(map->keys, i);
                map->size--;
                return;
            }
        }
    }
}

size_t Map_Size(Map map) {
    return map->size;
}

int Map_ContainsKey(Map map, void *key) {
    if (map->comparator == NULL) {
        for (int i = 0; i < map->size; i++) {
            if (map->defaultComparator(key, Vec_Get(map->keys, i), map->keyTypeSize)) {
                return 1;
            }
        }
    } else {
        for (int i = 0; i < map->size; i++) {
            if (map->comparator(key, Vec_Get(map->keys, i))) {
                return 1;
            }
        }
    }
    return 0;
}

void Map_Free(Map map) {
    Vec_Free(map->keys);
    Vec_Free(map->values);
    free(map);
}

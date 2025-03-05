#ifndef MAP_H
#define MAP_H

#include <stddef.h>

typedef struct map_t* Map;

Map Map_Init(size_t keySize, size_t valueSize);

void Map_SetComparator(Map map, int (*comparator)(void* key1, void* key2));
void Map_Insert(Map map, void* key, void* value);
void Map_Remove(Map map, void* key);
void* Map_Get(Map map, void* key);
size_t Map_Size(Map map);
int Map_ContainsKey(Map map, void* key);

void Map_Free(Map map);

#endif

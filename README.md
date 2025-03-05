# CMap
A simple, crosss platform, thread unsafe map in C

## Implementation
The implementation uses 2 [Vectors](github.com/TheRealCheeseEnjoyer/CVector), one for the keys, and one for the values, granting the ability to use any key type and any value type.
This implementation gives a default comparator, but can use any custom comparator

## Installation
1. Drop CMap.h, Cmap.c, Vector.h and Vector.c into your project
2. ????
3. profit

## Usage
* Map_Init() to create a new map
* Map_SetComparator() to set a custom comparator. The function passed must return an int, and accept 2 void*.
* Map_Insert() inserts a new item with a specified key, if the key is not yet used. (NOTE: this creates a shallow copy (memcpy) of both the key and the item)
* Map_Get() returns a pointer to the item mapped by key, or NULL if the key is not in the map. (NOTE: this is not an hashmap, Map_Get is O(n) time).
* Map_Remove() removes both the key and the item mapped by key.
* Map_ContainsKey() checks if a given key is present in the map.
* Map_Free() to free the map

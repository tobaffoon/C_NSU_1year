#include <stdint.h>
#include "dll_export.h"
//pointer to key or value (untyped)
typedef const void *cpvoid;
//returns 1 if and only if two keys pointed by [a] and [b] are equal
//returns 0 otherwise
typedef int (*EqualFunc)(cpvoid a, cpvoid b);
//returns 32-bit hash of a key pointed by [key]
typedef uint32_t (*HashFunc)(cpvoid key);

typedef struct HashList {
    cpvoid key,
            value;
    struct HashList *next;
} HashList;
typedef HashList *HashTable;
typedef struct HashMap {
    EqualFunc equalFunc;
    HashFunc hashFunc;
    HashTable hashTable;
    int hashSize;
} HashMap;
//creates and returns new hash table with:
// [ef] –- function which compares keys for equality
// [hf] –- function which produces a hash for a key
// [size] –- prescribed size/capacity of the hash table (number of cells)
MYDLL_API HashMap HM_Init(EqualFunc ef, HashFunc hf, int size);
//frees memory of hash map [self]
//note: called exactly once for every hash map created by HM_Init
MYDLL_API void HM_Destroy(HashMap *self);

//returns value corresponding to the specified key [key] in hash map [self]
//if [key] is not present in the map, then returns NULL
MYDLL_API cpvoid HM_Get(const HashMap *self, cpvoid key);
//sets value [value] for the key [key] in hash map [self]
//if [self] already has some value for [key], it is overwritten
MYDLL_API void HM_Set(HashMap *self, cpvoid key, cpvoid value);
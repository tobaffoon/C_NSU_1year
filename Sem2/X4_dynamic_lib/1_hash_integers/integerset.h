#include "hash_table.h"
#include "dll_export.h"

typedef Hash_table IntegerSet;

MYDLL_API IntegerSet *CreateSet(int* src, int size);

MYDLL_API char IsInSet(IntegerSet *set, int x);
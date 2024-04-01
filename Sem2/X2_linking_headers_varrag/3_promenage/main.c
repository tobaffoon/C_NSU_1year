#include <stdio.h>
#include <limits.h>

#ifdef __clang__
#define COMPILER "clang"
#elif  __TINYC__
#define COMPILER "TCC"
#elif _MSC_VER
#define COMPILER "MSVC"
#elif  __GNUC__
#define COMPILER "GCC"
#endif

#ifdef  _WIN64
#define BITNESS 64
#elif _WIN32
#define BITNESS 32
#endif

#ifdef NDEBUG
#define ASSERTS_ON "disabled"
#else
#define ASSERTS_ON "enabled"
#endif

int main() {
    printf("Compiler: %s", COMPILER);
    printf("\nBitness: %d", BITNESS);
    printf("\nAsserts: %s", ASSERTS_ON);
    return 0;
}
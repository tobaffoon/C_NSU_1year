#ifdef _WIN32
    #ifdef HASHMAP_EXPORTS
        #define MYDLL_API __declspec(dllexport)
    #else
        #define MYDLL_API __declspec(dllimport)
    #endif
#else
    #define MYDLL_API __attribute__((visibility("default")))
#endif
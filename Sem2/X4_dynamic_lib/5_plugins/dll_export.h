#ifdef _WIN32
    #define MYDLL_API __declspec(dllexport)
#else
    #define MYDLL_API __attribute__((visibility("default")))
#endif
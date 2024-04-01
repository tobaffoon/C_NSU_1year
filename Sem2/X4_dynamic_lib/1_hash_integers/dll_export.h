#ifdef _WIN32
    #ifdef EXPORT_DLL
        #define MYDLL_API __declspec(dllexport)
    #else
    #define MYDLL_API __declspec(dllimport)
#endif
#else
    #define MYDLL_API __attribute__((visibility("default")))
#endif
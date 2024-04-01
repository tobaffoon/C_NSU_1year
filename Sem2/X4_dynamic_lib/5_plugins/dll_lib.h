#ifdef _WIN32
    #include <windows.h>
#define DLL_EXTENSION ".dll"
#define LIBRARY_TYPE HMODULE
#define LOAD_FUNCTION(lib, func) GetProcAddress((lib), (func))
#define OPEN_LIBRARY(lib) LoadLibrary((lib))
#define CLOSE_LIBRARY(lib) FreeLibrary((lib))

#else
    #include <dlfcn.h>
#define DLL_EXTENSION ".so"
#define LIBRARY_TYPE void *
#define LOAD_FUNCTION(lib, func) dlsym((lib), (func))
#define OPEN_LIBRARY(lib) dlopen((lib), RTLD_LAZY)
#define CLOSE_LIBRARY(lib) dlclose((lib))
#endif
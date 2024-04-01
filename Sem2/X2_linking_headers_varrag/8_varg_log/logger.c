#include "logger.h"
#include <stdarg.h>

//current log file
FILE *logFile = 0;
//number of successful logPrintf calls
int logCalls = 0;

void logSetFile(FILE *file){
    logFile = file;
}

void logPrintf(const char *format, ...){
    if(logFile == 0)
        return;

    va_list as;
    va_start(as, format);

    vfprintf_s(logFile, format, as);

    va_end(as);

    logCalls++;
}

int getLogCallsCount(){
    return logCalls;
}
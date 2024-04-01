#include "pack.h"
#include <stdarg.h>
#include <string.h>

int pack(char *buffer, const char *format, ...){
    int bytes_read = 0;

    va_list as;
    va_start(as, format);

    if(buffer != 0) {
        while (*format != 0) {
            format++;
            switch (*format) {
                case 'd': {
                    int i = va_arg(as, int);
                    memcpy(buffer, &i, sizeof(int));
                    buffer += sizeof(int);
                    bytes_read += sizeof(int);
                    break;
                }
                case 'l': {
                    double d = va_arg(as, double);
                    memcpy(buffer, &d, sizeof(double));
                    buffer += sizeof(double);
                    bytes_read += sizeof(double);
                    format++;
                    break;
                }
                case 's':{
                    const char *s = va_arg(as, char*);
                    unsigned long long len = strlen(s) + 1;
                    memcpy(buffer, s, len);
                    buffer += len;
                    bytes_read += len;
                    break;
                }
            }
        }
    }

    else{
        while (*format != 0) {
            format++;
            switch (*format) {
                case 'd':
                    va_arg(as, int);
                    bytes_read += sizeof(int);
                    break;
                case 'l':
                    va_arg(as, double);
                    bytes_read += sizeof(double);
                    format++;
                    break;
                case 's':{
                    const char *s = va_arg(as, char*);
                    bytes_read += strlen(s) + 1;    //+1 due to '\0'
                    break;
                }
            }
        }
    }

    va_end(as);

    return bytes_read;
}
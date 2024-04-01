#include <stdio.h>
#include <stddef.h>
#include <wchar.h>
#include <locale.h>
#include <windows.h>

// #pragma execution_character_set( "utf-8" )

int main()
{
    SetConsoleOutputCP( 65001 );
    printf(L"%C", L'\x7825');
	return 0;
}
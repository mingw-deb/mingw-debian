#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include "native-func.h" /* Part of the Wine header files */



int __cdecl NATIVE_FUNC_DLL call_command(char ** argv)
{
	printf ("Windows dll simuliert\n");
	return 0;
}


char * __cdecl NATIVE_FUNC_DLL convert_filename(LPWSTR input)
{
	LPSTR retval;
	int length, result;
	if (!input) return NULL;

	length = WideCharToMultiByte(CP_UTF8,
				     0,
				     input,
				     -1,
				     NULL,
				     0,
				     NULL,
				     NULL);
	
	retval = malloc (length);
	if (!retval) return NULL;
	result = WideCharToMultiByte(CP_UTF8,
				     0,
				     input,
				     -1,
				     retval,
				     length,
				     NULL,
				     NULL);
	return retval;
}

#ifndef UNICODE
#define UNICODE
#endif
#define _UNICODE

#include <stdio.h>
#include <windows.h>
#include "native-func.h"

LPSTR convert_string(LPWSTR input)
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


int wmain2(int argc, WCHAR ** argv) {
	char ** newlist;
	int retval;
	/* we use +1 so that we get an additional null pointer,
	   in order to allow the array to be used directly with
	   the exec family */
	newlist = (char **) calloc(argc+1,sizeof(char*));
	{
		WCHAR ** old = argv+argc;
		CHAR **new = newlist +argc;
		while (old > argv) 
			*(new--) = convert_string(*(old--));
	}
	newlist[0] = convert_filename(argv[0]);
	
	for (int i = 0 ; i < argc ; i++) {
		wprintf(L"%s\n",argv[i]);
	}
	wprintf(L"Running the DLL\n");
	wprintf(L"return value: %d\n",retval = call_command(newlist));
	wprintf(L"still alive\n");
	return retval;
}

int wmain(int argc, WCHAR ** argv) {
	int retval = wmain2(argc,argv);
	wprintf(L"Rücksprung ok: %:",retval);
	return retval;
}

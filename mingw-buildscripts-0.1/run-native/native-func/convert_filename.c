/*#include <stdio.h>
#include <stdlib.h>
#include <linux/unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>*/
#include <stdarg.h>
#include <windef.h> /* Part of the Wine header files */
#include <winbase.h>


char * __cdecl convert_filename_linux(LPWSTR input)
{
	return wine_get_unix_file_name(input);
}

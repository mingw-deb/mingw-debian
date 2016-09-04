#ifndef NATIVE_FUNC_DLL_H
#define NATIVE_FUNC_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_NATIVE_FUNC_DLL
#define NATIVE_FUNC_DLL __declspec(dllexport)
#else
#define NATIVE_FUNC_DLL __declspec(dllimport)
#endif

	int __cdecl NATIVE_FUNC_DLL call_command(char ** argv);
	char * __cdecl NATIVE_FUNC_DLL convert_filename(LPWSTR input);
	
#ifdef __cplusplus
}
#endif

#endif

#ifndef __RTOSDef_H
#define __RTOSDef_H

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
//#include <iostream>
#include <io.h>
#include <direct.h>
#else
#include <libgen.h>
#include <unistd.h>
#include <ctype.h>
#endif

#include <stdio.h>
#include <fcntl.h>
#include <assert.h> 

// portable macros
#ifdef _WIN32
#define RTGI_FASTCALL			__fastcall
#define __DECLSPEC(param)	__declspec(param)

#define makedir 	_mkdir
#define truncate 	_chsize

#else

#define RTGI_FASTCALL
#define __DECLSPEC(param)

// defined in Win32 but we should define them in Linux
#define __min(a, b)	( ((a) < (b)) ? (a) : (b) )
#define __max(a, b)	( ((a) > (b)) ? (a) : (b) )

// special "flag" for #ifdef: there are no naked functions in Linux
#define NO_NAKED

#ifndef PATH_MAX
#define PATH_MAX 160
#endif

// using POSIX names instead of MS specific
#define _MAX_FNAME	PATH_MAX
#define _MAX_DRIVE	PATH_MAX
#define _MAX_DIR	    PATH_MAX
#define _MAX_PATH	PATH_MAX
#define _MAX_EXT		PATH_MAX

#define _getcwd		getcwd
#define _chdir		chdir
#define _fileno		fileno
#define _sleep		sleep
#define _strdup 	strdup
#define _isnan 		isnan
#define truncate    ftruncate
#define _stricmp    strcasecmp
#define CloseHandle close

// implementation non-standard functions
// TODO: move to Linux specific .cpp file
inline int makedir(const char* n) {
	int f = mkdir(n, 0);
	chmod(n, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP);
	return f;
}

inline off_t _filelength(int f)
{
	struct stat fs;
	fstat(f, &fs);
	return fs.st_size;
}

inline char *_fullpath(char *fn_abs, const char *fn_rel, int)
{
	if(fn_abs == NULL) {
		char* name = (char*)malloc(PATH_MAX);
		name = getcwd(name, PATH_MAX); 
		realpath(fn_rel, name);
		return name;
	} 
	realpath(fn_rel, fn_abs);
	return fn_abs;
}

inline void _splitpath(const char *fn_abs, char *dev, char *dir, char *fname, char *fext)
{
	char tdir[_MAX_PATH];
	char tname[_MAX_PATH];
	strcpy(tdir , fn_abs);
	strcpy(tname, fn_abs);
	if (dir)   strcpy(dir, dirname(tdir));
	if (fname) strcpy(fname, basename(tname));
	if (fext) {
		char* ext = strrchr(fn_abs, '.');
		if (ext) {
			strcpy(fext, ext);
			if (fext[strlen(fext)-1] == '\n') fext[strlen(fext)-1] = 0;
		}
	}
	if (dev) *dev = 0;
}

inline char *_makepath(char *path, const char *drv, const char *dir, const char *file, const char *ext)
{
	char* sep = "/";
	path[0] = 0;
	if (drv) {
		strcat(path, drv);	
		strcat(path, sep);
	}
	if (dir) {
		strcat(path, dir);	
		strcat(path, sep);
	}
	if (file) strcat(path, file);
	if (ext) strcat(path, ext);
	return path; 
}

inline int GetPrivateProfileString(const char* const section, const char* const key, const char* const defvalue, char* value, int sz, const char* szFileName)
{
	char szModel[_MAX_FNAME];

	value[0] = 0;

	FILE* file = fopen(szFileName, "r");
	if (!file)
		goto not_found;

	assert(section);
	sprintf(szModel, "[%s]", section);

	char line[160];
	while (fgets(line, sizeof(line), file)) {
		if (!strncmp(line, szModel, strlen(szModel)))
			goto find_parameter;
	}
	
	goto not_found;

 find_parameter:
	int nentities = 0;
	if (key) {
		while (fgets(line, sizeof(line), file) && line[0] != '[') {
			char* pkey = line + strspn(line, " \t");
			if (!strncmp(pkey, key, strlen(key)) && !isalnum(pkey[strlen(key)])) {
				char* pv = strrchr(pkey, '=') + 1;
				pv += strspn(pv, " \t");
				int l = __min(sz, strlen(pv));
				strncpy(value, pv, l-1);
				value[l-1] = 0; // \n
				break;
			}
		}
		nentities = strlen(value);
	} else {
		char* pv = value;
		while (fgets(line, sizeof(line), file) && line[0] != '[') {
			if (!strchr(line, '=')) 
				continue;
			char* pkey = line + strspn(line, " \t\n");
			char* pend = pkey + strcspn(pkey, " \t=");
			*pend = 0;
			if (pv-value + strlen(pkey) >= sz-1) break;
			strcpy(pv, pkey);
			pv += strlen(pv) + 1;
			*pv = 0;
			nentities++;
		}
	}
	fclose(file);
	printf("%s/%s/%s = %s\n", szFileName, section, key, value);
	return nentities;

 not_found:
	if (defvalue) strncpy(value, defvalue, sz);
	printf("%s/%s/%s = %s\n", szFileName, section, key, value);
	return 0;
}

inline bool WritePrivateProfileString(const char* sectionsName, const char* valueName, const char* value, const char* fileName)
{
	printf("WritePrivateProfileString is not implemented in Linux");
	exit(1);
	return 0;
}



#endif


#endif	// __RTOSDef_H


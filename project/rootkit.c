#include <stdio.h>
#include <dlfcn.h>
#include <sys/types.h>

uid_t geteuid(void) { return 0; }
uid_t getuid(void) { return 0; }
uid_t getgid(void) { return 0; }


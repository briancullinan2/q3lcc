/* quake3 bytecode target */

#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#define BINEXT ".exe"
#define PATH_SEP '\\'
#else
#define BINEXT ""
#define PATH_SEP '/'
#endif

char *suffixes[] = { ".c", ".i", ".asm", ".o", ".out", NULL };
char inputs[256] = "";
char *cpp[] = { "q3cpp" BINEXT,
	"-D__STDC__=1", "-D__STRICT_ANSI__", "-D__signed__=signed", "-DQ3_VM",
	"$1", "$2", "$3", NULL };
char *include[] = { NULL };
char *com[] = { "q3rcc" BINEXT, "-target=bytecode", "$1", "$2", "$3", NULL };

extern char *concat( char *, char * );

int option( char *arg ) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat( &arg[8], "/q3cpp" BINEXT );
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat( &arg[8], "/q3rcc" BINEXT );
	} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-pg") == 0) {
		fprintf( stderr, "no profiling supported, %s ignored.\n", arg);
	} else if (strcmp(arg, "-b") == 0)
		;
	else if (strcmp(arg, "-g") == 0)
		fprintf( stderr, "no debugging supported, %s ignored.\n", arg);
	else if (strncmp(arg, "-ld=", 4) == 0 || strcmp(arg, "-static") == 0) {
		fprintf( stderr, "no linking supported, %s ignored.\n", arg);
	} else
		return 0;
	return 1;
}
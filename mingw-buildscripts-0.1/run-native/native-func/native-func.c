#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <windef.h>

int __cdecl call_command_linux(char ** argv) {
	char * lastdot,*lastslash;
	int execute_direct = 0;
	int retval;
	pid_t pid;
	fprintf(stderr, "in der dll\n");
	if (!argv || !*argv) {
		fprintf(stderr,"Internal error: passing too view parameters to call_command");
		exit(127);
	}

	
	lastslash = strrchr(argv[0],'/');
	if (!lastslash || !(*lastslash))
		lastslash = argv[0];
	else lastslash++;
	lastdot = strrchr(lastslash,'.');
	if (lastdot) {
		struct stat sb;
		if (!*lastdot)
			lastdot = NULL;
		else if (!strcasecmp(lastdot,".exe")) {
			execute_direct = 1;
			*lastdot = 0;
		} else lastdot = NULL;
		printf("looking for %s\n",argv[0]);
		if (stat(argv[0], &sb) == -1) {
			switch(errno) {
			case EBADF:
				printf("EBADF\n");
			case EFAULT:
				printf("EFAULT\n");
#if 0
			case ENOENT: /* the file does not exist */
				printf("NOENT\n");
#endif
			case ENOMEM:
				printf("ENOMEM\n");
			case ENOTDIR: /* reported if the file does not exist */
				printf("ENOTDIR\n");
				perror(lastslash);
				exit(EXIT_FAILURE);
			}
			execute_direct = 0;
		} else if (sb.st_mode & S_IXUSR) {
			execute_direct = 1;
		}
		if (lastdot) *lastdot = '.';
	}

	pid = fork();
	if (!pid) {
		if (lastdot)
			*lastdot = 0;
		if (execute_direct) {
			printf("Executing %s (absolute)\n",argv[0]);
			retval = execv(argv[0],argv);
		} else {
			char * savearg = argv[0];
			argv[0]=lastslash;
			printf("Executing %s (relative)\n",argv[0]);
			retval = execvp(argv[0],argv);
			argv[0]=savearg;
		}
		printf("Error while executing %s (relative)\n",argv[0]);
		perror(lastslash);
		if (lastdot)
			*lastdot = '.';
		printf("Still running hehe...\n");
		exit(-1);
	} else if (pid == -1) {
		printf("Execution failed.\n");
		perror(lastslash);
		return -1;
	}
	waitpid(pid,&retval,0);
	printf("Returning %d\n",retval);
	return retval;
}


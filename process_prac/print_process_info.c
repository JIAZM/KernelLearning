#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid_p, pid_o, pid_c;
	int status;
	pid_t pid_r;

	pid_o = getpid();
	printf("In Ori process: pid from getpid()= %d \r\n", pid_o);

	if(!fork()){
		pid_c = getpid();
		printf("In Chi process: pid from getpid()= %d \r\n", pid_c);
		pid_p = getppid();
		printf("In Chi process: ppid from getppid()= %d \r\n", pid_p);
		exit(3);
	}

	pid_r = wait(&status);
	printf("return value of Chi is: %d \r\n", WEXITSTATUS(status));
	printf("return pid of wait is: %d \r\n", pid_r);

	exit(0);
}

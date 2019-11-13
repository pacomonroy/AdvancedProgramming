/*----------------------------------------------------------------

*

* Programación avanzada: Creación de procesos.

* Fecha: 1-Mar-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>


void child_process(int nlevel, int level) {
	int pid,i,j;

	if (level==0){
		printf("\nPPID = %d  PID = %d  NIVEL = %d\n", getppid(), getpid(), level);
		level++;
	}

	if (level>nlevel){
		sleep(1);
		exit(0);
	}


for(i=1; i<=level;i++){
				if ( (pid = fork()) < 0 ) {
							perror("Error");
							exit(-1);
						}else if (pid == 0){

      for (j=0; j<level; j++){
				printf("\t");
			}

      printf("PPID = %d  PID = %d  NIVEL = %d\n", getppid(), getpid(), level);
			level++;
			child_process(nlevel, level);
      return;
        }
        else {
            wait(NULL);
        }



}}

int main(int argc, char* argv[]) {
	int i, num, pid;
	const char *p = ".";

	if (argc != 2) {
		printf("usage: %s \n", argv[0]);
		return -1;
	}


	num = atof(argv[1]);
	if (num < 1 ||strstr(argv[1],p)!= NULL) {
		printf("%s: the parameter must be a positive integer number greater than zero\n", argv[0]);
		return -1;
	}
child_process(num,0);
	return 0;
}

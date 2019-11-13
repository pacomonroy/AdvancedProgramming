
/*----------------------------------------------------------------

*

* Programación avanzada: Cifrado de un archivo

* Fecha: 1-Feb-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 128

void rot(int n,int fd_in,int fd_out){
  char bloque[SIZE];
  int i;
  ssize_t nsize;
  char aux[SIZE];
  while( (nsize = read(fd_in, bloque, sizeof(bloque))) != 0 ) {
    if(nsize == SIZE){
      for(i=0;i<SIZE;i++){
        if((i-n)>-1){
          aux[i-n]=bloque[i];
        }else{
          aux[i-n+SIZE]=bloque[i];
        }
      }
      memcpy(bloque, aux, SIZE);
      write(fd_out,bloque,nsize);
    }else{
      write(fd_out,bloque,nsize);
    }
  }
  close(fd_in);
  close(fd_out);


}

int main(int argc, char* argv[]){
  int fd_in, fd_out;

  if (argc != 4) {
		printf("usage: %s origin destination\n", argv[0]);
		return -1;
	}
  if(atoi(argv[1])<1){
    printf("encryption: the first parameter must be a positive integer number \n");
    return -1;
  }

  if ( (fd_in = open(argv[2], O_RDONLY)) < 0 ) {
    perror(argv[0]);
    return -1;
  }

  if((fd_out=open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666))<0){
      printf("encryption: Can't create destination file");
      return -1;

  }
  int n = atoi(argv[2]);
  rot(n,fd_in,fd_out);
  return 0;
  }

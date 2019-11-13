/*----------------------------------------------------------------

*

* Programación avanzada: Archivos y directorios

* Fecha: 10-Mayo-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#define SIZE 1024
//#define PATH_MAX  255
#define NAME_MAX  255


void list(char *directory, char* program,int n) {
  FILE *fp;
  DIR* dir;
	struct dirent* direntry;
	struct stat info;
  int i;
  char permits[] = {'x', 'w', 'r'};

	char filename[PATH_MAX + NAME_MAX + 1];
  char path[PATH_MAX + NAME_MAX + 1];

  //La recursión se detiene cuando se ha llegado al nivel máximo
  if (n>0){
	if ( (dir = opendir(directory)) == NULL ) {
		perror(program);
		exit(-1);
	}
  printf("\nWorking in %s:\n", directory);

	while ( (direntry = readdir(dir)) != NULL ) {
		if (strcmp(direntry->d_name, ".") != 0 &&
			strcmp(direntry->d_name, "..") != 0) {
      sprintf(path, "%s/%s", directory, direntry->d_name);
      //printf("PATH: %s\n",path);
      for (i = 0; i < 9; i++) {
      		if (info.st_mode & (0400 >> i)) {
      			printf("%c", permits[(8 - i) % 3]);
      		} else {
      			printf("-");
      		}
      	}
      fp = fopen(path, "r");
      if(fp == NULL){
        printf("%s - cannot be read\n",direntry->d_name);
      }else{
        printf("Merging - %s\n", direntry->d_name);
      }

			sprintf(filename, "%s/%s", directory, direntry->d_name);
			lstat(filename, &info);
			if (S_ISDIR(info.st_mode)) {

        //Recorre recursivamente los directorios y subdirectorios
				list(filename, program,n-1);
			}
		}
	}
}
}



int main(int argc, char* argv[]) {
	int i, level, pid;
	const char *p = ".";
  DIR* dir;
  char *directory;
  char *word= "chapter1.txt";
  int fd;

  //Verifica que el programa recibe la cantidad correcta de parámetros
  if(argc !=4)
  {
    printf("usage: %s directory merge_file max_level\n",argv[0]);
  }else{

  directory = argv[1];

  //Verifica que directory existe y sea un directorio
  if((dir = opendir(directory)) == NULL){
    perror("Error");
    exit(-1);
  }

  //Verifica que level sea un numero entero positivo mayor a 1
  if(atoi(argv[3])<=1){
    printf("%s must be a positive integer greater than 1.\n",argv[3]);
    exit(-1);
  }
  level = atoi(argv[3]);

  //Verifica que mergefile se pueda crear
  if((fd=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666))<0){
      printf("Can't create destination file");
      return -1;
  }

  list(directory,argv[0],level);


}
return 0;
}

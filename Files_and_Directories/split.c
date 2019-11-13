
/*----------------------------------------------------------------

*

* Programación avanzada: Ex1

* Fecha: 15-Feb-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <math.h>
#include <dirent.h>
#include <string.h>
#define PATH_MAX 255
#define NAME_MAX 255

void get_size(char *name, char *dir_base, char* program) {
	int i;
	struct stat info;
	struct passwd *pw;
	struct group *gr;
	int size;
	char date[13];
	char permits[] = {'x', 'w', 'r'};
	char filename[PATH_MAX + NAME_MAX + 1];

	sprintf(filename, "%s/%s", dir_base, name);
	if (lstat(filename, &info) < 0) {
		perror(program);
		exit(-1);
	}

  size = info.st_size;

	printf("Size: %d",size);



}

void moveLess(char *dir_base, char *dir_less, char* filename, char *program){
  char filename_1[NAME_MAX + 1], filename_2[NAME_MAX + 1];
  struct stat info;
  sprintf(filename_1, "%s/%s", dir_base, filename);
  sprintf(filename_2, "%s/%s", dir_less, filename);

  if(lstat(filename_1, &info) == -1){
    perror(program);
    exit(-1);
  }
  if((info.st_mode & S_IFMT) == S_IFREG){
    insert(filename_1, filename_2, program);
  }


}

void moveGt(char *dir_base, char *dir_gt, char* filename, char *program){
  char filename_1[NAME_MAX + 1], filename_2[NAME_MAX + 1];
  struct stat info;
  sprintf(filename_1, "%s/%s", dir_base, filename);
  sprintf(filename_2, "%s/%s", dir_gt, filename);

  if(lstat(filename_1, &info) == -1){
    perror(program);
    exit(-1);
  }
  if((info.st_mode & S_IFMT) == S_IFREG){
    insert(filename_1, filename_2, program);
  }


}

void split(char *dir_base, char *dir_less, char *dir_gt, int n, int recursive, char* program) {
	DIR* dir;
	struct dirent* direntry;
	struct stat info;
  int size =0;
	char filename[PATH_MAX + NAME_MAX + 1];
  char filename2[PATH_MAX + NAME_MAX + 1];



	if ( (dir = opendir(dir_base)) == NULL ) {
		perror(program);
		exit(-1);
	}

  while ( (direntry = readdir(dir)) != NULL ) {

      sprintf(filename, "%s/%s", dir_base, direntry->d_name);
      get_size(direntry->d_name, dir_base, program);


  }

  if (recursive) {
    rewinddir(dir);
    while ( (direntry = readdir(dir)) != NULL ) {
      if (strcmp(direntry->d_name, ".") != 0 &&
              strcmp(direntry->d_name, "..") != 0) {

        sprintf(filename, "%s/%s", dir_base, direntry->d_name);
        lstat(filename, &info);
        size = info.st_size;
        if(size <= n){
        moveLess(dir_base, dir_less, direntry->d_name,program);
      }else if(size> n){
        moveLess(dir_base, dir_gt, direntry->d_name,program);
      }
        if (S_ISDIR(info.st_mode)) {
          split(dir_base, dir_less, dir_gt, n, recursive, program);
        }
      }
    }
  }
  printf("\n");
}

int main(int argc, char* argv[]){
  char *dir_base;
  char *dir_less;
  char *dir_gt;
  int recursive =1;
  int n;

	if(argc != 4){
		fprintf(stderr, "usage: %s base lesser greater N ", argv[0]);
		return -1;
	}
	if(argv[2] < 0){
		printf("Solo positivos \n");
		return -1;
	}


	dir_base = argv[1];
	dir_less = argv[2];
  dir_less = argv[3];
  dir_less = argv[4];
	split(dir_base, dir_less, dir_gt, n,recursive,argv[0]);
	return 0;
}

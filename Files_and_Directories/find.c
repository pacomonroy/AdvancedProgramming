/*----------------------------------------------------------------

*

* Programación avanzada: Archivos y directorios

* Fecha: 12-Feb-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/

//This program finds the files within a given directory

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#define PATH_MAX 255
#define NAME_MAX 255

void get_info(char *name, char *directory, char* program) {
	int i;
	struct stat info;
	struct passwd *pw;
	struct group *gr;
	time_t rawtime;
	int size;
	struct tm* timeinfo;
	char date[13];
	char permits[] = {'x', 'w', 'r'};
	char filename[PATH_MAX + NAME_MAX + 1];

	sprintf(filename, "%s/%s", directory, name);
	if (lstat(filename, &info) < 0) {
		perror(program);
		exit(-1);
	}

  printf("\nName: %s \n", name);
  printf("Path: %s \n", directory);
  rawtime = info.st_atime;
  timeinfo = localtime(&rawtime);
	size = info.st_size;

	printf("Size: %d",size);

  printf("Last access: %s", asctime(timeinfo));
  rawtime = info.st_mtime;

  timeinfo = localtime(&rawtime);
  printf("Last modification: %s", asctime(timeinfo));


}

void find(char *directory, char *name, int recursive, char* program) {
	DIR* dir;
	struct dirent* direntry;
	struct stat info;
	char filename[PATH_MAX + NAME_MAX + 1];



	//printf("DIRECTORY %s:\n", directory);
  while ( (direntry = readdir(dir)) != NULL ) {
    if (strstr(direntry->d_name, name) != NULL) {
      sprintf(filename, "%s/%s", directory, direntry->d_name);
      get_info(direntry->d_name, directory, program);
    }
  }

  if (recursive) {
    rewinddir(dir);
    while ( (direntry = readdir(dir)) != NULL ) {
      if (strcmp(direntry->d_name, ".") != 0 &&
              strcmp(direntry->d_name, "..") != 0) {

        sprintf(filename, "%s/%s", directory, direntry->d_name);
        lstat(filename, &info);
        if (S_ISDIR(info.st_mode)) {
          find(filename, name, recursive, program);
        }
      }
    }
  }
  printf("\n");
}



int main(int argc, char* argv[]) {
  char dir_name[PATH_MAX + 1];
  char *directory;
  char *name;
  int recursive;

  if (argc < 3) {
		printf("usage: %s str directory [-r]\n", argv[0]);
		return -1;
	}

  recursive = 0;
  if (argc == 3){
    name = argv[1];
    directory = argv[2];
  } else if (argc == 4){
      if (strcmp(argv[3], "-r") == 0){
        recursive = 1;
        name = argv[1];
        directory = argv[2];

      }
  }

  find(directory, name, recursive, argv[0]);
  return 0;
}

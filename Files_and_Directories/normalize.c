/*----------------------------------------------------------------

*

* Programación avanzada: Normalización de archivos

* Fecha: 22-Feb-2019

* Autor: A01360926 Francisco Monroy

*

*--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <float.h>


float getMin(float a, float b) {
  if(a < b){
    return a;
  }else{
    return b;
  }
}

float getMax(float a, float b) {
  if(a > b){
    return a;
  }else{
    return b;
  }
}

void minMax(char* fileNameIn, char* fileNameOut, char *program){
  int i = 0;
  int aux;
  float a , b, num;
	float minN, maxN;
	float texts[625];
	FILE *fileIn, *fileOut;
	fileIn = fopen(fileNameIn, "r");
	fileOut = fopen(fileNameOut, "w");

	if(fileIn == NULL){
		perror(program);
		exit(-1);
	}
	if(fileOut == NULL){
		perror(program);
		exit(-1);
	}

	for(aux=0; aux <61; aux++){
		fscanf(fileIn, "%f,%f,", &a,&b);
		for(i=0; i<625;i++){
				fscanf(fileIn, "%f,", &texts[i]);
		}

		fscanf(fileIn, "\n");
		maxN = FLT_TRUE_MIN;
		minN = FLT_MAX;
		for(i=0; i<625;i++){
      minN= getMin(texts[i],minN);
			maxN = getMax(texts[i],maxN);
        /*
        if(texts[i] < minN){
          minN = minN;
        }else if (texts[i] >= minN){
          minN = texts[i];
        }
        if(texts[i] < maxN){
          maxN = maxN;
        }else if (texts[i] > minN){
          maxN = texts[i];
        }
        */
		}
		for(i=0; i<625;i++){
			texts[i]= (texts[i]- minN) / (maxN - minN);
		}
		for(i=0; i<624;i++){
			fprintf(fileOut, "%f,", texts[i]);
		}
		fprintf(fileOut, "%f\n", texts[624]);
	}
	fclose(fileIn);
	fclose(fileOut);
}



void normalize(char *input_directory, char *output_directory, char *program){
	DIR *dirIn, *dirOut;
  char fileNameIn[NAME_MAX + 1], fileNameOut[NAME_MAX + 1];
	struct dirent *dir_entry;
	struct stat infoIn, infoOut,infoNorm;


  if (lstat(input_directory, &infoIn) < 0) {
		perror(program);
    exit(-1);
  }
	if (lstat(output_directory, &infoOut) < 0) {
		perror(program);
    exit(-1);
  }
	if (!S_ISDIR(infoIn.st_mode)){
		fprintf(stderr, "%s: Not a directory\n",program );
		exit(-1);
  }
  if (!S_ISDIR(infoOut.st_mode)){
		fprintf(stderr, "%s: Not a directory\n",program );
		exit(-1);
  }

  if((dirIn = opendir(input_directory)) == NULL){
    fprintf(stderr, "%s: No such file or directory\n", program);
    exit(-1);
  }

  if((dirOut = opendir(output_directory)) == NULL){
      fprintf(stderr, "%s: No such file or directory\n", program);
      exit(-1);
    }



  while ((dir_entry = readdir(dirIn)) != NULL) {

    if (strcmp(dir_entry->d_name, ".") != 0 &&
      strcmp(dir_entry->d_name, "..")  != 0) {


        sprintf(fileNameIn, "%s/%s", input_directory, dir_entry->d_name);
      	sprintf(fileNameOut, "%s/%s", output_directory, dir_entry->d_name);

        if(lstat(fileNameIn, &infoNorm) == -1){
          perror(program);
          exit(-1);
        }
        if((infoNorm.st_mode & S_IFMT) == S_IFREG){
          minMax(fileNameIn, fileNameOut, program);
        }
    }

  }
  printf("DONE\n");

}




int main(int argc, char* argv[]){
	char *input_directory;
  char *output_directory;

	if(argc != 3){
		fprintf(stderr, "usage: %s input_directory output_directory\n", argv[0]);
		return -1;
	}

  input_directory = argv[1];
  output_directory = argv[2];

	normalize(input_directory, output_directory, argv[0]);
	return 0;
}

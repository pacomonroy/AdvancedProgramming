/*----------------------------------------------------------------

*

* Programación avanzada: Manejando señales

* Fecha: 12-Mar-2019

* Autor: 1360926 Francisco Monroy

*

*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <math.h>

void pr1(){
  int i;
  int n1;
  printf("\nPunto de retorno 1: \n");
  printf("Tabla de cuadrados\n");
  printf("Número Cuadrado\n");

  for(i=1;i<6;i++){
    n1 = pow(i,2);
    printf("\n %i",i);
    printf("\t %i\n",n1);

  }
}

void pr2(){
  int j;
  float n2;
  printf("\nPunto de retorno 2: \n");
  printf("Tabla de raíces cuadradas\n");
  printf("Número Raíz cuadrada\n");
  for(j=1;j<6;j++){
    n2 = sqrt(j);
    printf("\n %i",j);
    printf("\t %f\n",n2);
  }

}

void pr3(){
  int k;
  double n3;
  printf("\nPunto de retorno 3: \n");
  printf("Tabla de logaritmos\n");
  printf("Número Logaritmo\n");
  for(k=1;k<6;k++){
    n3 = log(k);
    printf("\n %i",k);
    printf("\t %f\n",n3);
  }

}

void jumpHandler(int signal) {
    switch(signal) {
        case SIGHUP :
          pr1();
          pr2();
          pr3();
          break;
        case SIGINT :
            pr2();
            pr3();
          break;
        case SIGQUIT :
            pr3();
          break;
        default:
          break;
}}



int main(int argc, char* argv[]) {

int n =1;
signal(SIGHUP, jumpHandler);
signal(SIGINT, jumpHandler);
signal(SIGQUIT, jumpHandler);


if(argc != n){
  printf("usage: %s [n]\n", argv[0]);
  return -1;
}
else{
  pr1();
  pr2();
  pr3();
  printf("pid= %i\n", getpid());

}
while(1){
  sleep(5);
}
return 0;
//pr1();
//pr2();
//pr3();



}

#include "minimal.h"
#include <stdio.h>
#include <math.h> 

int main(int argc, char* argv[]){
    //Pedir al usuario que ingrese dos numeros y calcule el menor de ellos
    int a, b;
    int potencia;
    printf("Ingrese el valor del numero 1 (a)\n"); 
    scanf("%i",&a);
      printf("Ingrese el valor del numero 2 (b)\n"); 
    scanf("%i",&b);
    printf("the min value is: %d\n",minimal(a,b));
    //Usar la funcion pow() para elevar el primer numero al segundo
    potencia = pow (a,b);
    printf ("el valor de %i elevado a %i es igual a %i\n", a, b, potencia);
    return 0;
}
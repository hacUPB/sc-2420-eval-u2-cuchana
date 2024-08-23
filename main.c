#include <stdio.h>
#include <math.h>  
float calcula_imc (float,float);

int main(int argc, char const *argv[])
{
    float estatura, peso, imc; 
    char Nombre[30];
    printf ("Ingrese su nombre\n"); 
    fgets(Nombre, 30, stdin);

    printf("Ingrese su peso\n");
    scanf("%f",&peso);

    printf("Ingrese su estatura\n");
    scanf("%f",&estatura);
    imc=calcula_imc(peso,estatura);//llama a la funcion 
    
    printf("%s su IMC=%f\n",Nombre,imc);

    printf ("Sistemas Computacionales 2024 ♥\n");
    return 0;
}
float calcula_imc (float peso ,float estatura )
{
    float IMC; 
    //IMC= peso/estatura2
    IMC = peso / pow(estatura,2);
    return IMC; 

}
#include <stdio.h>
#include <conio.h>

#define N 10

typedef struct
{
    int numerador[N];
    int denominador[N];
}Fracciones;

void leeFracciones(FILE *arch, Fracciones *f, int *j);
int realizaSuma(Fracciones *f, int *j, int *mcm);
void imprimeSuma(int suma, int *mcm);

    
int main()
{
    FILE *archivo;
    int i = 0;
    Fracciones f;
    int suma, mcm;

    archivo = fopen("Fracciones.txt", "r");
    leeFracciones(archivo, &f, &i);
    
    suma = realizaSuma(&f, &i, &mcm);

    imprimeSuma(suma, &mcm);

    getch();
    return 0;
}

void leeFracciones(FILE *arch, Fracciones *f, int *j)
{
    int pudoLeer, cerrado;
    int i = 0;

    //Obtenemos las fracciones del archivo;
    do
    {
        fscanf(arch, "%d", &f->numerador[i]);

        pudoLeer = fscanf(arch, "%d", &f->denominador[i]);

        printf("%d/%d\n", f->numerador[i], f->denominador[i]);

        i++;

    }while (pudoLeer != EOF);

    //Guardamos la cantidad de fracciones leidas
    *j = i;

    cerrado = fclose(arch);

    if(cerrado == EOF) //fclose regresa EOF cuando no se puede cerrar correctamente    
    {
        printf("El archivo no se cerro bien");
    }
}

int realizaSuma(Fracciones *f, int *j, int *mcm)
{
    int a, b, r, mcd, aux;
    int nume, suma = 0;

    a = f->denominador[0];
    b = f ->denominador[1];

    mcd = a;
    aux = b;
     
     //obtenemos el MCD
    do
    {
        r = mcd % aux;
        mcd = aux;
        aux = r;

    }while(r != 0);

    //Obtenemos el MCM
    *mcm = a*b / mcd; //mcm *mcd = a * b
    

    //Realizamos la suma de la fracciones
    for (int i = 0; i < *j-1; i++)
    {
        nume = *mcm / f->denominador[i];
        nume = nume * f->numerador[i];
        suma = suma + nume;
    }
    
    return suma;
}

void imprimeSuma(int suma, int *mcm)
{
    //Simplificamos la suma
    if(suma % 2 == 0 && *mcm % 2 == 0)
    {
        suma = suma / 2;
        *mcm = *mcm / 2;
    } 
    else if( suma % 3 == 0 && *mcm % 3 == 0)
    {
        suma = suma / 3;
        *mcm = *mcm / 3;
    }
    else if( suma % 5 == 0 && *mcm % 5 == 0)
    {
        suma = suma / 5;
        *mcm = *mcm / 5;
    }
    else if( suma % 7 == 0 && *mcm % 7 == 0)
    {
        suma = suma / 7;
        *mcm = *mcm / 7;
    }

    printf("La suma es: %d/%d", suma, *mcm);
}

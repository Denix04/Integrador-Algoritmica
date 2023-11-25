#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

int opcion;
Tfuerza fuerza; 
Logico salir;
Tveteranos veteranos;
char apellido[20];
int dni, mes;

void main()
{
    cargarArreglo(&veteranos);
    recalcularEdades(veteranos);

    do {
        menu(&opcion);
        switch (opcion){
            case INSERTAR:
                Tpersona nuevo;
                cargarDatos(veteranos, &nuevo);
                insertar(veteranos, &nuevo);
                break;
            case ELIMINAR:
                printf("Ingrese DNI: ");
                scanf("%d", &dni);
                fgetc(stdin);
                suprimir(veteranos, dni);
                break;
            case MODIFICAR:
                printf("Ingrese DNI: ");
                scanf("%d", &dni);
                fgetc(stdin);
                modificar(veteranos, dni);
                break;
            case LISTODO:
                mostrar(veteranos);
                break;
            case LISAPELLIDO:
                printf("Ingrese el apellido: ");
                fgets(apellido, 20, stdin);
                apellido[strlen(apellido)-1] = '\0';
                mostrarPorApellido(veteranos, apellido);
                break;
            case LISFALLECIDOS:
                mostrarFallecidos(veteranos);
                break;
            case LISFUERZA:
                pedirFuerza(&fuerza);
                mostrarPorFuerza(veteranos, fuerza);
                break;
            case LISPORMES:
                printf("Ingrese un mes: ");
                do{
                    scanf("%d", &mes);
                } while(mes < 1 || mes > 12);
                ordenarPorMes(veteranos, mes);
                break;
            case SALIR:
                cargarArchivo(veteranos); 
                break;
        }
    } while (opcion !=SALIR);

}

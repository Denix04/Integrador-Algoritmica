// AUTORES
// ASTRADA, CAMILA DNI: 43.132.086
// DEBERNARDI, ALVARO DNI: 42.890.685

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
                printf("-------------------------------------------------\n");
                printf("            SUPRIMIR USUARIO.\n");
                printf("-------------------------------------------------\n");
                printf("Ingrese DNI: ");
                numeroValido(&dni);
                suprimir(veteranos, dni);
                break;
            case MODIFICAR:
                printf("-------------------------------------------------\n");
                printf("          MODIFICAR USUARIO.\n");
                printf("-------------------------------------------------\n");
                printf("Ingrese DNI: ");
                numeroValido(&dni);
                modificar(veteranos, dni);
                break;
            case LISTODO:
                mostrar(veteranos);
                break;
            case LISAPELLIDO:
                printf("-------------------------------------------------\n");
                printf("      LISTADO DE PERSONAS POR APELLIDO.\n");
                printf("-------------------------------------------------\n");
                printf("Ingrese el apellido: ");
                fgets(apellido, 20, stdin);
                apellido[strlen(apellido)-1] = '\0';
                mostrarPorApellido(veteranos, apellido);
                break;
            case LISFALLECIDOS:
                mostrarFallecidos(veteranos);
                break;
            case LISFUERZA:
                printf("-------------------------------------------------\n");
                printf("    LISTADO DE PERSONAS POR FUERZA.\n");
                printf("-------------------------------------------------\n");
                pedirFuerza(&fuerza);
                mostrarPorFuerza(veteranos, fuerza);
                break;
            case LISPORMES:
                printf("-------------------------------------------------\n");
                printf("      LISTADO DE PERSONAS POR MES.\n");
                printf("-------------------------------------------------\n");
                printf("Ingrese un mes: ");
                numeroValido(&mes);
                while(mes < 1 || mes > 12){
                    printf("Ingrese un mes valido: ");
                    numeroValido(&mes);
                }
                ordenarPorMes(veteranos, mes);
                break;
            case SALIR:
                cargarArchivo(veteranos); 
                break;
        }
    } while (opcion !=SALIR);

}

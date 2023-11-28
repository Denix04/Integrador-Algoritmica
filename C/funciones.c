// AUTORES
// ASTRADA, CAMILA DNI: 43.132.086
// DEBERNARDI, ALVARO DNI: 42.890.685

#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include <string.h>
#include <time.h>
#include <ctype.h>

void menu(int *opcion){

    printf("-------------------------------------------------\n");
    printf("                  MENÚ\n");
    printf("-------------------------------------------------\n");
    printf("1. Insertar persona.\n");
    printf("2. Suprimir persona.\n");
    printf("3. Modificar datos de una persona.\n");
    printf("4. Listar todas las personas.\n");
    printf("5. Listar personas por apellido.\n");
    printf("6. Listar personas fallecidas.\n");
    printf("7. Listar personas según la fuerza a la que perteneció.\n");
    printf("8. Listar personas según su mes de cumpleaños.\n");
    printf("9. Salir.\n");
    printf("\n  Ingrese una opción: ");
    do {
        numeroValido(opcion);
        if (*opcion < 1 || *opcion > 9) 
            printf("\n  Opcion invalida, ingresela nuevamente: ");
    } while (*opcion < 1 || *opcion > 9);
}

void cargarArreglo(Tveteranos *veteranos){
    FILE *f;
    Tpersona aux;
    *veteranos = (Tveteranos)malloc(sizeof(struct Tveteranos_));
    (*veteranos)->cant = 0;
    if ((f = fopen("malvinas.dat", "r")) == NULL)
        f = popen("malvinas.dat", "w");

    while (fread(&aux, sizeof(Tpersona), 1,f)) {
        (*veteranos)->personas[(*veteranos)->cant] = aux;
        (*veteranos)->cant++;
    }
    fclose(f);
}

void cargarArchivo(const Tveteranos veteranos){
    FILE *f;
    Tpersona aux;
    int pos;

    f = fopen("malvinas.dat", "w");
    for (pos = 0; pos < veteranos->cant; pos++){
        aux = veteranos->personas[pos];
        fwrite(&aux, sizeof(Tpersona), 1, f);
    }

    fclose(f);
}

Logico vacia(const Tveteranos veteranos){
    if (veteranos->cant == 0)
        return VERDADERO;
    else
        return FALSO;
}

Logico llena(const Tveteranos veteranos){
    if (veteranos->cant == NMAX)
        return VERDADERO;
    else
        return FALSO;
}

Logico validacionFecha(Tfecha fecha){

    if (fecha.mes < 1 || fecha.mes >12 || fecha.dia < 1 || fecha.dia>31)
        return FALSO;
    if ((fecha.mes != 1 && fecha.mes != 3 && fecha.mes != 5 && fecha.mes != 7 && fecha.mes != 8 && fecha.mes != 10 && fecha.mes != 12) && fecha.dia==31)
        return FALSO;
    if (fecha.mes == 2 && ((fecha.anio%4 == 0 && !(fecha.anio%100 == 0)) || (fecha.anio%100 == 0 && fecha.anio%400 == 0)) && fecha.dia > 29)
        return FALSO;
    if (fecha.mes == 2 && !((fecha.anio%4 == 0 && !(fecha.anio%100 == 0)) || (fecha.anio%100 == 0 && fecha.anio%400 == 0)) && fecha.dia > 28)
        return FALSO;
    
    return VERDADERO;
}

Logico isNumeric(char *cadena){
    
    int i = 0;
    if (cadena[i] == '-' || cadena[i] == '+')
        i++;

    while(cadena[i] != '\0'){
        if(!isdigit(cadena[i]))
            return FALSO;
        i++;
    }
    return VERDADERO;
}

void numeroValido(int *numero){
    char cadena[20];
    scanf("%s", cadena);
    fgetc(stdin);
    
    while(!isNumeric(cadena)){
        printf("Número inválido. Ingrese nuevamente: ");
        scanf("%s",cadena);
        fgetc(stdin);
    }
    *numero = atoi(cadena);
}

int buscarPosicion(const Tveteranos veteranos, const Tpersona *persona){
    int pos = 0;
    Logico posEncontrada = FALSO;

    while (strcmp(persona->apellido, veteranos->personas[pos].apellido) > 0 && pos < veteranos->cant)
        pos++;

    if (strcmp(persona->apellido, veteranos->personas[pos].apellido) == 0){
        do {
            printf("hola %s-%d\n", veteranos->personas[pos].apellido, pos);
            printf("%s\n", veteranos->personas[pos].nombre);
            printf("%d\n\n", veteranos->cant);
            if (strcmp(persona->apellido, veteranos->personas[pos].apellido) != 0)
                break;
            if (strcmp(persona->nombre, veteranos->personas[pos].nombre) < 0)
                posEncontrada = VERDADERO;
            else if (strcmp(persona->nombre, veteranos->personas[pos].nombre) > 0)
                pos++;
            else {
                if (persona->DNI < veteranos->personas[pos].DNI)
                    posEncontrada = VERDADERO;
                if (persona->DNI > veteranos->personas[pos].DNI)
                    pos++;
                if (persona->DNI == veteranos->personas[pos].DNI)
                    pos++;
            }
        } while (pos < veteranos->cant && posEncontrada == FALSO);
    }
    return pos;
}

int calcularEdad(Tfecha nacimiento){
    time_t segundos = time(NULL);
    struct tm* fechaActual = localtime(&segundos);

    int edad = fechaActual->tm_year+1900 - nacimiento.anio;

    if (fechaActual->tm_mon+1 < nacimiento.mes || (nacimiento.mes == fechaActual->tm_mon+1 && fechaActual->tm_mday+1 < nacimiento.mes))
        edad--;
    return edad;
}

void recalcularEdades(Tveteranos veteranos){
    for(int pos = 0; pos < veteranos->cant; pos++)
        veteranos->personas[pos].edad = calcularEdad(veteranos->personas[pos].nacimiento);
}

Logico dniRepetido(const Tveteranos veteranos, int dni){
    int pos = 0;
    while (pos < veteranos->cant){
        if (dni == veteranos->personas[pos].DNI)
            return VERDADERO;
        pos++;
    }
    return FALSO;
}

void pedirFuerza(Tfuerza *fuerza){
    int opcion;
    do{
        printf("Ingrese la fuerza a la que pertenecio:\n");
        printf("  1) Marina\n");
        printf("  2) Gendarmeria\n");
        printf("  3) Ejército\n");
        printf("  4) Aeronáutica\n");
        printf("  Fuerza: ");
        numeroValido(&opcion);
        switch (opcion){
            case MARINA:
                *fuerza = MARINA;
                break;
            case GENDARMERIA:
                *fuerza = GENDARMERIA;
                break;
            case EJERCITO:
                *fuerza = EJERCITO;
                break;
            case AERONAUTICA:
                *fuerza = AERONAUTICA;
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion < 1 || opcion > 4);
}

void cargarDatos(const Tveteranos veteranos, Tpersona* nuevo){
    int opcion;

    printf("-------------------------------------------------\n");
    printf("              CARGANDO USUARIO.\n");
    printf("-------------------------------------------------\n");

    printf("Ingrese el nombre: ");
    fgets(nuevo->nombre, 20, stdin);
    nuevo->nombre[strlen(nuevo->nombre)-1] = '\0';

    printf("Ingrese el apellido: ");
    fgets(nuevo->apellido, 20, stdin);
    nuevo->apellido[strlen(nuevo->apellido)-1] = '\0';

    printf("Ingrese el DNI: ");
    numeroValido(&nuevo->DNI);
    while (dniRepetido(veteranos, nuevo->DNI)){
        printf("Ya existe una persona con ese DNI, ingrese nuevamente: ");
        numeroValido(&nuevo->DNI);
    }

    do {
        printf("Ingrese el dia de nacimiento: ");
        numeroValido(&nuevo->nacimiento.dia);

        printf("Ingrese el mes de nacimiento: ");
        numeroValido(&nuevo->nacimiento.mes);

        printf("Ingrese el año de nacimiento: ");
        numeroValido(&nuevo->nacimiento.anio);
    } while (!validacionFecha(nuevo->nacimiento));

    nuevo->edad = calcularEdad(nuevo->nacimiento);

    printf("Ingrese la ciudad: ");
    fgets(nuevo->ciudad, 20, stdin);
    nuevo->ciudad[strlen(nuevo->ciudad)-1] = '\0';

    printf("Ingrese la ciudad antes de la guerra: ");
    fgets(nuevo->ciudadAntes, 20, stdin);
    nuevo->ciudadAntes[strlen(nuevo->ciudadAntes)-1] = '\0';

    printf("Ingrese la dirección postal: ");
    fgets(nuevo->DP, 30, stdin);
    nuevo->DP[strlen(nuevo->DP)-1] = '\0';

    printf("Ingrese el correo electrónico: ");
    fgets(nuevo->CE, 20, stdin);
    nuevo->CE[strlen(nuevo->CE)-1] = '\0';

    printf("Ingrese el teléfono: ");
    fgets(nuevo->tel, 15, stdin);
    nuevo->tel[strlen(nuevo->tel)-1] = '\0';

    do{
        printf("Fallecio (0), Vive (1): ");
        numeroValido(&opcion);
        switch (opcion){
            case 0:
                nuevo->VF = FALSO;
                break;
            case 1:
                nuevo->VF = VERDADERO;
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != 0 && opcion != 1);

    if (!nuevo->VF){
        do {
            printf("Ingrese el dia de fallecimiento: ");
            numeroValido(&nuevo->fallecimiento.dia);

            printf("Ingrese el mes de fallecimiento: ");
            numeroValido(&nuevo->fallecimiento.mes);

            printf("Ingrese el año de fallecimiento: ");
            numeroValido(&nuevo->fallecimiento.anio);
        } while (!validacionFecha(nuevo->fallecimiento));
    }

    printf("Ingrese el beneficio: ");
    fgets(nuevo->beneficio, 20, stdin);
    nuevo->beneficio[strlen(nuevo->beneficio)-1] = '\0';

    printf("Ingrese el codigo postal: ");
    fgets(nuevo->CP, 10, stdin);
    nuevo->CP[strlen(nuevo->CP)-1] = '\0';

    printf("Ingrese la provincia: ");
    fgets(nuevo->provincia, 50, stdin);
    nuevo->provincia[strlen(nuevo->provincia)-1] = '\0';

    pedirFuerza(&nuevo->fuerza);

    printf("Ingrese el destino en malvinas: ");
    fgets(nuevo->destino, 50, stdin);
    nuevo->destino[strlen(nuevo->destino)-1] = '\0';

    printf("Ingrese la funcion malvinas: ");
    fgets(nuevo->funcion, 100, stdin);
    nuevo->funcion[strlen(nuevo->funcion)-1] = '\0';

    printf("Ingrese el grado: ");
    fgets(nuevo->grado, 20, stdin);
    nuevo->grado[strlen(nuevo->grado)-1] = '\0';

    printf("Ingrese las secuelas: ");
    fgets(nuevo->secuelas, 200, stdin);
    nuevo->secuelas[strlen(nuevo->secuelas)-1] = '\0';
}

void insertar(Tveteranos veteranos, Tpersona* nuevo){
    int pos, aux;

    if (llena(veteranos))
        printf("No es posible agregar miembros, lista llena.");
    else {
        pos = buscarPosicion(veteranos, nuevo);
        for (aux = veteranos->cant -1; pos <= aux; aux--)
            veteranos->personas[aux+1] = veteranos->personas[aux];
        veteranos->personas[pos] = *nuevo;
        veteranos->cant++;
    }
}

void suprimir(Tveteranos veteranos, int dni){
    int pos = -1;
    Logico encontrado = FALSO;

    while (pos < veteranos->cant && encontrado == FALSO){
        pos = pos + 1;
        if (veteranos->personas[pos].DNI == dni)
            encontrado = VERDADERO;
    }

    for (pos; pos < veteranos->cant; pos++)
        veteranos->personas[pos] = veteranos->personas[pos+1];
    if (encontrado){
        veteranos->cant--;
        printf("\nUsuario suprimido\n");
    }
    else printf("Dni no encontrado.\n");
}

void mostrar(const Tveteranos veteranos){
    int pos;

    printf("-------------------------------------------------\n");
    printf("        LISTADO DE TODAS LAS PERSONAS.\n");

    for (pos = 0; pos < veteranos->cant; pos++){
        printf("-------------------------------------------------\n\n");
        printf("Nombre: %s\n", veteranos->personas[pos].nombre);
        printf("Apellido: %s\n", veteranos->personas[pos].apellido);
        printf("Dni: %d\n", veteranos->personas[pos].DNI);
        printf("Fecha de Nacimiento: %d / %d / %d\n", veteranos->personas[pos].nacimiento.dia, veteranos->personas[pos].nacimiento.mes, veteranos->personas[pos].nacimiento.anio);
        printf("Edad: %d\n", veteranos->personas[pos].edad);
        printf("Ciudad De residencia: %s\n", veteranos->personas[pos].ciudad);
        printf("Ciudad De Nacimiento: %s\n", veteranos->personas[pos].ciudadAntes);
        printf("Dirección Postal: %s\n", veteranos->personas[pos].DP);
        printf("Correo Electronico: %s\n", veteranos->personas[pos].CE);
        printf("Telefono: %s\n", veteranos->personas[pos].tel);
        if (veteranos->personas[pos].VF == FALSO)
        {
            printf("Fallecido\n");
            printf("Fecha de Fallecimiento: %d / %d / %d\n", veteranos->personas[pos].fallecimiento.dia, veteranos->personas[pos].fallecimiento.mes, veteranos->personas[pos].fallecimiento.anio);
        }
        else {
            printf("Vivo\n");
        }

        printf("Número de Beneficio Nacional: %s\n", veteranos->personas[pos].beneficio);
        printf("Provincia: %s\n", veteranos->personas[pos].provincia);
        printf("Fuerza: %d\n", veteranos->personas[pos].fuerza);
        printf("Destino: %s\n", veteranos->personas[pos].destino);
        printf("Función en Malvinas: %s\n", veteranos->personas[pos].funcion);
        printf("Grado: %s\n", veteranos->personas[pos].grado);
        printf("Secuelas: %s\n", veteranos->personas[pos].secuelas);
    }
}

void mostrarPorApellido(const Tveteranos veteranos, char *apellido){
    int pos = 0, cant = 0;

    while (pos < veteranos->cant && strcmp(veteranos->personas[pos].apellido, apellido)<=0){
            
        if (strcmp(veteranos->personas[pos].apellido, apellido) == 0){
            printf("-------------------------------------------------\n");
            printf("Nombre: %s\n", veteranos->personas[pos].nombre);
            printf("Apellido: %s\n", veteranos->personas[pos].apellido);
            printf("Dni: %d\n", veteranos->personas[pos].DNI);
            printf("Fecha de Nacimiento: %d / %d / %d\n", veteranos->personas[pos].nacimiento.dia, veteranos->personas[pos].nacimiento.mes, veteranos->personas[pos].nacimiento.anio);
            printf("edad: %d\n", veteranos->personas[pos].edad);
            printf("Ciudad De residencia: %s\n", veteranos->personas[pos].ciudad);
            printf("Ciudad De Nacimiento: %s\n", veteranos->personas[pos].ciudadAntes);
            printf("Dirección Postal: %s\n", veteranos->personas[pos].DP);
            printf("Correo Electronico: %s\n", veteranos->personas[pos].CE);
            printf("Telefono: %s\n", veteranos->personas[pos].tel);

            if (veteranos->personas[pos].VF == FALSO) {
                printf("Fallecido\n");
                printf("Fecha de Fallecimiento: %d / %d / %d\n", veteranos->personas[pos].fallecimiento.dia, veteranos->personas[pos].fallecimiento.mes, veteranos->personas[pos].fallecimiento.anio);
            } else 
                printf("Vivo\n");

            printf("Número de Beneficio Nacional: %s\n", veteranos->personas[pos].beneficio);
            printf("Provincia: %s\n", veteranos->personas[pos].provincia);
            printf("Fuerza: %d\n", veteranos->personas[pos].fuerza);
            printf("Destino: %s\n", veteranos->personas[pos].destino);
            printf("Función en Malvinas: %s\n", veteranos->personas[pos].funcion);
            printf("Grado: %s\n", veteranos->personas[pos].grado);
            printf("Secuelas: %s\n", veteranos->personas[pos].secuelas);
            cant++;
        }
        pos++;
    }
    if (cant == 0)
        printf("No hay personas con ese apellido.\n");
}

void modificar(Tveteranos veteranos, int dni){
    int pos, nuevaPos, opcion;
    Tpersona* modificado = (Tpersona*)malloc(sizeof(Tpersona));

    for (pos = 0; pos < veteranos->cant && veteranos->personas[pos].DNI != dni; pos++)
        ;

    *modificado = veteranos->personas[pos];

    if (pos < veteranos->cant){
        suprimir(veteranos, veteranos->personas[pos].DNI);
        do {
            printf("Que informacion desea cambiar:\n");
            printf("1. Nombre\n");
            printf("2. Apellido\n");
            printf("3. Fecha de nacimiento\n");
            printf("4. Ciudad de residencia\n");
            printf("5. Ciudad de residencia antes de la guerra\n");
            printf("6. Provincia donde nació\n");
            printf("7. Dirección postal\n");
            printf("8. Correo electrónico\n");
            printf("9. Teléfono\n");
            printf("10. Vive/Fecha de fallecimiento\n");
            printf("11. Número de beneficio de social\n");
            printf("12. Codigo postal\n");
            printf("13. Fuerza a la que perteneció\n");
            printf("14. Grado militar\n");
            printf("15. Destino en Malvinas\n");
            printf("16. Función en Malvinas\n");
            printf("17. Secuelas de la guerra\n");
            numeroValido(&opcion);
        } while (opcion < 1 || opcion > 18);

        switch (opcion){
            case 1:
                printf("Ingrese el nombre: ");
                fgets(modificado->nombre, 20, stdin);
                modificado->nombre[strlen(modificado->nombre)-1] = '\0';
                break;
            case 2:
                printf("Ingrese el apellido: ");
                fgets(modificado->apellido, 20, stdin);
                modificado->apellido[strlen(modificado->apellido)-1] = '\0';
                break;
            case 3:
                do {
                    printf("Ingrese el dia de nacimiento: ");
                    numeroValido(&modificado->nacimiento.dia);

                    printf("Ingrese el mes de nacimiento: ");
                    numeroValido(&modificado->nacimiento.mes);

                    printf("Ingrese el año de nacimiento: ");
                    numeroValido(&modificado->nacimiento.anio);
                } while (!validacionFecha(modificado->nacimiento));
                modificado->edad = calcularEdad(modificado->nacimiento);
                break;
            case 4:
                printf("Ingrese el ciudad: ");
                fgets(modificado->ciudad, 20, stdin);
                modificado->ciudad[strlen(modificado->ciudad)-1] = '\0';
                break;
            case 5:
                printf("Ingrese el ciudad antes de la guerra: ");
                fgets(modificado->ciudadAntes, 20, stdin);
                modificado->ciudadAntes[strlen(modificado->ciudadAntes)-1] = '\0';
                break;
            case 6:
                printf("Ingrese la provincia: ");
                fgets(modificado->provincia, 50, stdin);
                modificado->provincia[strlen(modificado->provincia)-1] = '\0';
                break;
            case 7:
                printf("Ingrese el dirección postal: ");
                fgets(modificado->DP, 30, stdin);
                modificado->DP[strlen(modificado->DP)-1] = '\0';
                break;
            case 8:
                printf("Ingrese el correo electrónico: ");
                fgets(modificado->CE, 20, stdin);
                modificado->CE[strlen(modificado->CE)-1] = '\0';
                break;
            case 9:
                printf("Ingrese el teléfono: ");
                fgets(modificado->tel, 15, stdin);
                modificado->tel[strlen(modificado->tel)-1] = '\0';
                break;
            case 10:
                do{
                    printf("Fallecido (0), vivo (1): ");
                    numeroValido(&opcion);
                    switch (opcion){
                        case 0:
                            modificado->VF = FALSO;
                            break;
                        case 1:
                            modificado->VF = VERDADERO;
                            break;
                        default:
                            printf("Opcion incorrecta\n");
                            break;
                    }
                } while (opcion != 0 && opcion != 1);

                if (!modificado->VF){
                    do {
                        printf("Ingrese el dia de fallecimiento: ");
                        numeroValido(&modificado->fallecimiento.dia);

                        printf("Ingrese el mes de fallecimiento: ");
                        numeroValido(&modificado->fallecimiento.mes);

                        printf("Ingrese el año de fallecimiento: ");
                        numeroValido(&modificado->fallecimiento.anio);
                    } while (!validacionFecha(modificado->fallecimiento));
                }
                break;
            case 11:
                printf("Ingrese el beneficio: ");
                fgets(modificado->beneficio, 20, stdin);
                modificado->beneficio[strlen(modificado->beneficio)-1] = '\0';
                break;
            case 12:
                printf("Ingrese el codigo postal: ");
                fgets(modificado->CP, 10, stdin);
                modificado->CP[strlen(modificado->CP)-1] = '\0';
                break;
            case 13:
                pedirFuerza(&modificado->fuerza);
                break;
            case 14:
                printf("Ingrese el grado: ");
                fgets(modificado->grado, 20, stdin);
                modificado->grado[strlen(modificado->grado)-1] = '\0';
                break;
            case 15:
                printf("Ingrese el destino malvinas: ");
                fgets(modificado->destino, 50, stdin);
                modificado->destino[strlen(modificado->destino)-1] = '\0';
                break;
            case 16:
                printf("Ingrese el funcion malvinas: ");
                fgets(modificado->funcion, 100, stdin);
                modificado->funcion[strlen(modificado->funcion)-1] = '\0';
                break;
            case 17:
                printf("Ingrese las secuelas: ");
                fgets(modificado->secuelas, 200, stdin);
                modificado->secuelas[strlen(modificado->secuelas)-1] = '\0';
                break;
        }

        insertar(veteranos, modificado);
    } else 
        printf("No hay una persona con ese DNI\n");
}

void liberarLSE(Tfallecidos **fallecidos){
    Tfallecidos *aux, *aux2;  
    aux = *fallecidos;
    while(*fallecidos!=NULL){
        aux= *fallecidos;
        *fallecidos = aux->next;
        free(aux);
    }
}

void liberarLDE(TlistaFuerza **fuerza){
    TlistaFuerza *aux;  
    aux = *fuerza;
    while(*fuerza!=NULL){
        aux = *fuerza; 
        *fuerza = aux->next;
        free(aux);
    }
}

void mostrarFallecidos(const Tveteranos veteranos){
    Tfallecidos *fallecidos, *aux, *nuevo;
    int pos = 0;

    printf("-------------------------------------------------\n");
    printf("              VETERANOS FALLECIDOS.\n");

    fallecidos = (Tfallecidos*)malloc(sizeof(Tfallecidos));
    fallecidos->next = NULL;

    aux = fallecidos;
    while (pos < veteranos->cant) {
        if (veteranos->personas[pos].VF == FALSO) {
            nuevo = (Tfallecidos*)malloc(sizeof(Tfallecidos));
            nuevo->info = veteranos->personas[pos];
            nuevo->next = NULL;
            aux->next = nuevo;
            aux = aux->next;
        }
        pos++;
    }
    aux = fallecidos->next;
    if (aux == NULL){
        printf("-------------------------------------------------\n");
        printf("No hay fallecidos\n");
    }
    else {
        while (aux != NULL) {
            printf("-------------------------------------------------\n");
            printf("Nombre: %s\n", aux->info.nombre);
            printf("Apellido: %s\n", aux->info.apellido);
            printf("DNI: %d\n", aux->info.DNI);
            printf("Fecha de Nacimiento: %d / %d / %d\n", aux->info.nacimiento.dia, aux->info.nacimiento.mes, aux->info.nacimiento.anio);
            printf("Ciudad: %s\n", aux->info.ciudad);
            aux = aux->next;
        }
    }
    liberarLSE(&fallecidos);
}

void mostrarPorFuerza(const Tveteranos veteranos, Tfuerza fuerza){
    TlistaFuerza *cabeza, *cola, *nuevo, *aux;
    int pos;

    cabeza = (TlistaFuerza*)malloc(sizeof(TlistaFuerza));
    cabeza->back = NULL;
    cola = (TlistaFuerza*)malloc(sizeof(TlistaFuerza));
    cola->next = NULL;
    cabeza->next = cola;
    cola->back = cabeza;
    aux = cabeza;

    for (pos = 1; pos <= veteranos->cant; pos++) {
        if (veteranos->personas[pos].fuerza == fuerza) {
            nuevo = (TlistaFuerza*)malloc(sizeof(TlistaFuerza));
            nuevo->persona = veteranos->personas[pos];
            nuevo->back = aux;
            nuevo->next = cola;
            aux->next = nuevo;
            cola->back = nuevo;
            aux = nuevo;
        }
    }
    aux = cabeza->next;
    if (aux->next == NULL){
        printf("-------------------------------------------------\n");
        printf("No se encuentran personas pertenecientes a esa fuerza\n");
    }
    while (aux->next != NULL) {
        printf("-------------------------------------------------\n");
        printf("Nombre: %s\n", aux->persona.nombre);
        printf("Apellido: %s\n", aux->persona.apellido);
        printf("Dni: %d", aux->persona.DNI);
        printf("Fecha de Nacimiento: %d / %d / %d\n", aux->persona.nacimiento.dia, aux->persona.nacimiento.mes, aux->persona.nacimiento.anio);
        printf("edad: %d\n", aux->persona.edad);
        printf("Ciudad De residencia: %s\n", aux->persona.ciudad);
        printf("Ciudad De Nacimiento: %s\n", aux->persona.ciudadAntes);
        printf("Dirección Postal: %s\n", aux->persona.DP);
        printf("Correo Electronico: %s\n", aux->persona.CE);
        printf("Telefono: %s\n", aux->persona.tel);

        if (veteranos->personas[pos].VF == FALSO){
            printf("Fallecido\n");
            printf("Fecha de Fallecimiento: %d / %d / %d\n", veteranos->personas[pos].fallecimiento.dia, veteranos->personas[pos].fallecimiento.mes, veteranos->personas[pos].fallecimiento.anio);
        } else {
            printf("Vivo\n");
        }

        printf("Número de Beneficio Nacional: %s\n", aux->persona.beneficio);
        printf("Provincia: %s\n", aux->persona.provincia);
        printf("Fuerza: %d\n", aux->persona.fuerza);
        printf("Destino: %s\n", aux->persona.destino);
        printf("Función en Malvinas: %s\n", aux->persona.funcion);
        printf("Grado: %s\n", aux->persona.grado);
        printf("Secuelas: %s\n", aux->persona.secuelas);
        aux = aux->next;
    }
    liberarLDE(&cabeza);
    cola = NULL;
}

void ordenarPorMes(const Tveteranos veteranos, int mes) {
    Tveteranos veteranosMes;
    veteranosMes = (struct Tveteranos_*)malloc(sizeof(struct Tveteranos_));
    veteranosMes->cant = 0;
    Tpersona aux;

    for (int pos = 0; pos<veteranos->cant; pos++){
        if (veteranos->personas[pos].nacimiento.mes == mes) {
            veteranosMes->personas[veteranosMes->cant] = veteranos->personas[pos];
            veteranosMes->cant++;
        }
    }

    for (int i = veteranosMes->cant -1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (veteranosMes->personas[j].nacimiento.dia > veteranosMes->personas[j + 1].nacimiento.dia){
                aux = veteranosMes->personas[j];
                veteranosMes->personas[j] = veteranosMes->personas[j + 1];
                veteranosMes->personas[j + 1] = aux;
            }
        }
    }

    if (veteranosMes->cant == 0)
        printf("No hay personas que cumplan años ese mes.\n");

    for (int pos = 0; pos < veteranosMes->cant; pos++) {
        printf("-------------------------------------------------\n");
        printf("Nombre: %s\n", veteranosMes->personas[pos].nombre);
        printf("Apellido: %s\n", veteranosMes->personas[pos].apellido);
        printf("Fecha de Nacimiento: %d / %d / %d\n", veteranosMes->personas[pos].nacimiento.dia, veteranosMes->personas[pos].nacimiento.mes, veteranosMes->personas[pos].nacimiento.anio);
        printf("Edad: %d\n", veteranosMes->personas[pos].edad);
        printf("Ciudad De residencia: %s\n", veteranosMes->personas[pos].ciudad);
        printf("Dirección Postal: %s\n", veteranosMes->personas[pos].DP);
        printf("Correo Electronico: %s\n", veteranosMes->personas[pos].CE);
        if (veteranosMes->personas[pos].VF)
            printf("Vivo\n");
        else
            printf("Fallecido el: %d / %d / %d\n", veteranosMes->personas[pos].fallecimiento.dia,veteranosMes->personas[pos].fallecimiento.mes,veteranosMes->personas[pos].fallecimiento.anio); 
    }
}

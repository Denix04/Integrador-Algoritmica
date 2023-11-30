// AUTORES
// ASTRADA, CAMILA DNI: 43.132.086
// DEBERNARDI, ALVARO DNI: 42.890.685

#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define NMAX 250

typedef enum {FALSO, VERDADERO} Logico;
typedef enum {INSERTAR = 1, ELIMINAR, MODIFICAR, LISTODO, LISAPELLIDO, LISFALLECIDOS, LISFUERZA, LISPORMES, SALIR} TopMenu;
typedef enum {MARINA = 1, GENDARMERIA, EJERCITO, AERONAUTICA} Tfuerza;

typedef struct Tfecha_{
    int dia;
    int mes;
    int anio;
} Tfecha;


typedef struct Tpersona_{
    int DNI;
    char nombre[20];
    char apellido[20];
    Tfecha nacimiento;
    int edad;
    char ciudad[20];
    char ciudadAntes[20];
    char DP[30];
    char CE[20];
    char tel[15];
    Logico VF;
    Tfecha fallecimiento;
    char beneficio[20];
    char CP[10];
    char provincia[50];
    Tfuerza fuerza;
    char destino[50];
    char funcion[100];
    char grado[20];
    char secuelas[200];
} Tpersona;

struct Tveteranos_{
    Tpersona personas[NMAX];
    int cant;
};

typedef struct Tveteranos_* Tveteranos;

typedef struct Tfallecidos_{
    Tpersona info;
    struct Tfallecidos_* next;
} Tfallecidos;

typedef struct TlistaFuerza_{
    Tpersona persona;
    struct TlistaFuerza_* back;
    struct TlistaFuerza_* next;
} TlistaFuerza;

// Declaracion de funciones:

void menu(int*);        // muestra y da la opcion          

void cargarArreglo(Tveteranos*);      // carga el arreglo con lo que haya en el registro

void cargarArchivo(const Tveteranos);   // carga el archivo con lo que alla en al arreglo

Logico vacia(const Tveteranos);    // dice si el arreglo esta vacio

Logico llena(const Tveteranos);    // dice si el arreglo esta lleno

Logico isNumeric(char*);     // devuelve verdadero si todos los caracteres de una cadena son digitos

void numeroValido(int *numero);   // es para pedir numeros al usuario y filtrar letras  

Logico validacionFecha(Tfecha);   // valida una fecha

int calcularEdad(Tfecha);    // calcula le edad de una persona

void recalcularEdades(Tveteranos);    // recalcula la edad de las personas (para que las edades esten actualizadas)

int buscarPosicion(const Tveteranos, const Tpersona*);    // busca la posicion en la que deberia ser insertado una persona

Logico dniRepetido(const Tveteranos, int dni);   // dice si un dni esta repetido

void pedirFuerza(Tfuerza*);  // pide al usuario una fuerza

void pedirFecha(Tfecha*, char*);   // pide al usuario una fecha y la asigna

void cargarDatos(const Tveteranos, Tpersona*);   // carga los datos de una persona

void insertar(Tveteranos, Tpersona*);  // inserta a una persona en el arreglo

void suprimir(Tveteranos, int dni);    // suprime a la persona con ese dni

void mostrar(const Tveteranos);    // muestra todas las personas

void mostrarPorApellido(const Tveteranos, char* apellido);    // muestra todas las personas 

void modificar(Tveteranos, int dni);   // modifica los datos de una persona

void mostrarFallecidos(const Tveteranos);   //muestra las personas fallecidas del arreglo

void mostrarPorFuerza(const Tveteranos, Tfuerza fuerza);    // muestra todas las personas que coincidan con una fuerza

void liberarLSE(Tfallecidos**);   // libera la lista de los fallecidos

void liberarLDE(TlistaFuerza**);;   // libera la lista de la fuerza

void ordenarPorMes(const Tveteranos, int mes);   // devuelve todos los que cumplan años en ese mes

#endif

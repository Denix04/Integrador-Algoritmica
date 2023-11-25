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

void menu(int*);
void cargarArreglo(Tveteranos*);
void cargarArchivo(const Tveteranos);
Logico vacia(const Tveteranos);
Logico llena(const Tveteranos);
Logico validacionFecha(Tfecha);
int calcularEdad(Tfecha);
void recalcularEdades(Tveteranos);
int buscarPosicion(const Tveteranos, const Tpersona*);
Logico dniRepetido(const Tveteranos, int dni);
void pedirFuerza(Tfuerza*);
void cargarDatos(const Tveteranos, Tpersona*);
void insertar(Tveteranos, Tpersona*);
void suprimir(Tveteranos, int dni);
void mostrar(const Tveteranos);
void mostrarPorApellido(const Tveteranos, char* apellido);
void modificar(Tveteranos, int dni);
void mostrarFallecidos(const Tveteranos);
void mostrarPorFuerza(const Tveteranos, Tfuerza fuerza);
void ordenarPorMes(const Tveteranos, int mes);

#endif

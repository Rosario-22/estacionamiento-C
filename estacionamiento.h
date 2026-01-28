#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H

#define N 8
#define M 100

/* Estructuras */
typedef struct {
	float horaIngreso;
	char patente[N];
	int ubicacion;
} Auto;

typedef struct Nodo {
	Auto data;
	struct Nodo* sgte;
} Nodo;

typedef struct {
	int longitud;
	int capacidad;
	Nodo* autoInicio;
	Nodo* autoFinal;
} tEstacionamiento;

/* PROTOTIPOS */
void menu(int* op);
void crearEstacionamiento(tEstacionamiento* E, int capacidad);
Nodo* crearNodo(Auto dato);
void insertarAuto(tEstacionamiento* E, Auto dato);
Nodo* buscarPorPatente(Nodo* inicio, char patente[N]);
int retirarAuto(tEstacionamiento* E, char patente[N]);
void mostrarAutos(tEstacionamiento* E);

#endif

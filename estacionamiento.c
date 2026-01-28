#include "estacionamiento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*FUNCIÓN PRINCIPAL */

int main() {
	tEstacionamiento E;
	int op;
	char patente[N];
	Auto a;
	crearEstacionamiento(&E, M);
	do {
		menu(&op);
		
		switch (op) {
		case 1:
			printf("Hora de ingreso: ");
			scanf(" %f", &a.horaIngreso);
			getchar();/*limpia el buffer*/
			printf("Patente: ");
			scanf(" %s", a.patente);
			getchar();
			printf("Ubicacion: ");
			scanf(" %d", &a.ubicacion);
			insertarAuto(&E, a);
			break;
			
		case 2:
			printf("Patente a retirar: ");
			scanf("%s", patente);
			if (retirarAuto(&E, patente))
				printf("Auto retirado correctamente.\n");
			else
				printf("No se encontro el auto.\n");
			break;
			
		case 3:
			mostrarAutos(&E);
			break;
		}
		
	} while (op != 4);
	
	return 0;
}


/*IMPLEMENTACIONES*/

/**
* Muestra el menú principal.
*/
void menu(int* op) {
	printf("\n--- MENU ESTACIONAMIENTO ---\n");
	printf("1. Ingresar auto\n");
	printf("2. Retirar auto\n");
	printf("3. Mostrar autos\n");
	printf("4. Salir\n");
	printf("Opcion: ");
	scanf("%d", op);
}

/**
* Inicializa un estacionamiento vacío.
*/
void crearEstacionamiento(tEstacionamiento* E, int capacidad) {
	E->longitud = 0;
	E->capacidad = capacidad;
	E->autoInicio = NULL;
	E->autoFinal = NULL;
}

/**
* Crea un nodo dinámico con un auto.
*/
Nodo* crearNodo(Auto dato) {
	Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
	if (nuevo != NULL) {
		nuevo->data = dato;
		nuevo->sgte = NULL;
	}
	return nuevo;
}

/**
* Inserta un auto al final de la lista.
*/
void insertarAuto(tEstacionamiento* E, Auto dato) {
	if (E->longitud >= E->capacidad) {
		printf("Estacionamiento lleno.\n");
		return;
	}
	
	Nodo* nuevo = crearNodo(dato);
	if (nuevo == NULL) {
		printf("Error de memoria.\n");
		return;
	}
	
	if (E->autoInicio == NULL) {
		E->autoInicio = nuevo;
		E->autoFinal = nuevo;
	} else {
		E->autoFinal->sgte = nuevo;
		E->autoFinal = nuevo;
	}
	
	E->longitud++;
}

/**
* Busca un auto por patente.
* @return puntero al nodo si lo encuentra, NULL si no.
*/
Nodo* buscarPorPatente(Nodo* inicio, char patente[N]) {
	while (inicio != NULL) {
		if (strcmp(inicio->data.patente, patente) == 0)
			return inicio;
		inicio = inicio->sgte;
	}
	return NULL;
}

/**
* Elimina un auto por patente.
* @return 1 si se eliminó, 0 si no se encontró.
*/
int retirarAuto(tEstacionamiento* E, char patente[N]) {
	Nodo* actual = E->autoInicio;
	Nodo* ant = NULL;
	
	while (actual != NULL) {
		if (strcmp(actual->data.patente, patente) == 0) {
			
			if (ant == NULL) { // era el primero
				E->autoInicio = actual->sgte;
			} else {
				ant->sgte = actual->sgte;
			}
			
			if (actual == E->autoFinal) {
				E->autoFinal = ant;
			}
			
			free(actual);
			E->longitud--;
			return 1;
		}
		ant = actual;
		actual = actual->sgte;
	}
	return 0;
}

/**
* Muestra todos los autos en el estacionamiento.
*/
void mostrarAutos(tEstacionamiento* E) {
	Nodo* aux = E->autoInicio;
	printf("\n--- AUTOS EN ESTACIONAMIENTO ---\n");
	while (aux != NULL) {
		printf("Patente: %s | Hora: %f | Ubicacion: %d\n",
			   aux->data.patente,
			   aux->data.horaIngreso,
			   aux->data.ubicacion);
		aux = aux->sgte;
	}
}

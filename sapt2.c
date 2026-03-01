#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


typedef struct Produs {
	unsigned int id;
	float pret;
	char* numeProdus;
	unsigned char serie;//1
	int nrIngredi;
	int* cantinateIngredi;
}Produs;


Produs creareProdus(unsigned int id, float pret, const char* numeProdus, int nrIngredi, int* cantinateIngredi) {
	Produs p;
	p.id = id;
	p.pret = pret;
	p.numeProdus = (char*)malloc(sizeof(char) * strlen(numeProdus) + 1);
	strcpy(p.numeProdus, numeProdus);
	p.nrIngredi = nrIngredi; 
	p.cantinateIngredi = (int*)malloc(sizeof(int) * nrIngredi);
	for (int i = 0; i < nrIngredi; i++) {
		p.cantinateIngredi[i] = cantinateIngredi[i];
	}

	return p;

}

typedef struct nod {
	Produs info;
	struct nod* next;
	struct nod* prev;
}nod;


typedef struct LD {
	nod* prim;
	nod* ultim;
}LD;

LD inserareInceputLD(LD lista, Produs p) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareProdus(p.id, p.pret, p.numeProdus, p.serie, p.nrIngredi, p.cantinateIngredi);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.prim) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
	}

	return lista;

}

LD inserareFinalLD(LD lista, Produs p) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareProdus(p.id, p.pret, p.numeProdus, p.serie, p.nrIngredi, p.cantinateIngredi);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.ultim) {

		lista.ultim->next = nou;
		nou->prev = lista.ultim;
		lista.ultim = nou;
	}
	else {
		lista.prim = nou;
		lista.ultim = nou;
	}

	return lista;

}


void afisareInceput(LD lista) {
	nod* aux = lista.prim;
	if (aux != NULL) {
		while (aux) {
			printf("%u, 5.2%, %s, %d, %d \n ", aux->info.id, aux->info.pret, aux->info.numeProdus, aux->info.serie, aux->info.nrIngredi);
			for (int i = 0; i < aux->info.nrIngredi; i++) {
				printf("%d ", aux->info.cantinateIngredi[i]);
			}

			aux = aux->next;

		}
	}
	else {
		printf("Lista este goala!");
	}
}

void afisareFinal(LD lista) {
	nod* aux = lista.ultim;
	while (aux) {
		printf("%u, %5.2f, %s, %u, %d \n ", aux->info.id, aux->info.pret, aux->info.numeProdus, aux->info.serie, aux->info.nrIngredi);
		/*for (int i = 0; i < aux->info.nrIngredi; i++) {
			printf("%d ", aux->info.cantinateIngredi[i]);
		}*/

		aux = aux->prev;

	}
}



void main() {

	int* vect = (int*)malloc(sizeof(int) * 2);
	vect[0] = 12;
	vect[1] = 120;

	Produs p = creareProdus(11, 11.99, "Prajityr", 123, 2, vect);
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	lista = inserareFinalLD(lista, p);
	afisareInceput(lista);
}





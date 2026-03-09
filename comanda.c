#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct StructuraComanda Comanda;
typedef struct nod nod;
typedef struct LD LD;

struct StructuraComanda {
	unsigned int idComanda;
	char* dataLansareComanda;
	char* dataLivrareProgramata;
	char* numeClient;
	float valoareComanda;
};

Comanda creareObiect(unsigned int idComanda, char* dataLansareComanda, char* dataLivrareProgramata,
char* numeClient, float valoareComanda) {
	Comanda c;
	c.idComanda = idComanda;
	c.dataLansareComanda = (char*)malloc(strlen(dataLansareComanda) + 1);
	strcpy(c.dataLansareComanda, dataLansareComanda);
	c.dataLivrareProgramata = (char*)malloc(strlen(dataLivrareProgramata) + 1);
	strcpy(c.dataLivrareProgramata, dataLivrareProgramata);
	c.numeClient = (char*)malloc(strlen(numeClient) + 1);
	strcpy(c.numeClient, numeClient);
	c.valoareComanda = valoareComanda;
	return c;
}

struct nod {
	Comanda info;
	struct nod* next;
	struct nod* prev;

};

struct LD {
	nod* prim;
	nod* ultim;
};

LD inserareInceput(LD lista, Comanda c) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareObiect(c.idComanda, c.dataLansareComanda, c.dataLivrareProgramata,
		c.numeClient, c.valoareComanda);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.prim != NULL) {
		nou->next = lista.prim;
		lista.prim->prev = nou;
		lista.prim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
	}
	return lista;
}

LD inserareFinal(LD lista, Comanda c) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareObiect(c.idComanda, c.dataLansareComanda, c.dataLivrareProgramata,
		c.numeClient, c.valoareComanda);
	nou->next = NULL;
	nou->prev = NULL;

	if (lista.prim != NULL) {
		nou->prev = lista.ultim;
		lista.ultim->next = nou;
		lista.ultim = nou;
	}
	else {
		lista.prim = lista.ultim = nou;
	}
	return lista;
}

void afisareInceput(LD lista) {
	if (lista.prim != NULL) 
	{
		nod* aux = lista.prim;
		while (aux != NULL) {
			printf("%u %s %s %s %5.2f", aux->info.idComanda, aux->info.dataLansareComanda,
				aux->info.dataLivrareProgramata, aux->info.numeClient, aux->info.valoareComanda);
			aux = aux->next;
		}
		}
	else {
		printf("lista este goala");
	}
	}

void afisareFinal(LD lista) {
	if (lista.ultim != NULL)
	{
		nod* aux = lista.ultim;
		while (aux != NULL) {
			printf("%u %s %s %s %5.2f \n", aux->info.idComanda, aux->info.dataLansareComanda,
				aux->info.dataLivrareProgramata, aux->info.numeClient, aux->info.valoareComanda);
			aux = aux->prev;
		}
	}
	else {
		printf("lista este goala");
	}
}

void dezalocare(LD lista) {
	nod* aux = lista.prim;
	while (aux) {
		free(aux->info.dataLansareComanda);
		free(aux->info.dataLivrareProgramata);
		free(aux->info.numeClient);
		free(aux);
		nod* copie = aux->next;
		aux = copie;
	}
}

void main() {
	Comanda c = creareObiect(1, "01.03.2026", "02.03.2026", "Roxana", 100.99);
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;
	lista = inserareInceput(lista, c);
	afisareInceput(lista);

	return 0;

}
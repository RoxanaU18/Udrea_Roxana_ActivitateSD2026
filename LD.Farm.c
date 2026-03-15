#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Farmacist Farmacist;
typedef struct Nod Nod;
typedef struct LD LD;

struct Farmacist {
	int codAngajat;
	char* numeFarmacist;
	float salariu;
};

struct Nod {
	Farmacist info;
	Nod* next;
	Nod* prev;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

Farmacist creareObiect(int codAngajat, char* numeFarmacist, float salariu) {
	Farmacist f;
	f.codAngajat = codAngajat;
	f.numeFarmacist = (char*)malloc(strlen(numeFarmacist) + 1);
	strcpy(f.numeFarmacist, numeFarmacist);
	f.salariu = salariu;
	return f;
}

LD inserareInceput(LD lista, Farmacist f) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareObiect(f.codAngajat, f.numeFarmacist, f.salariu);
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

void afisareInceput(LD lista) {
	if (lista.prim != NULL) {
		Nod* aux = lista.prim;
		while (aux) {
			printf("\n%d %s %5.2f", aux->info.codAngajat, aux->info.numeFarmacist, aux->info.salariu);
			aux = aux->next;
		}
	}
}

float maxSalariu(LD lista) {
	Nod* aux = lista.prim;
	float max = aux->info.salariu;
	while (aux) {
		if (aux->info.salariu > max) {
			max = aux->info.salariu;
		}
		aux = aux->next;

	}
	return max;
}

void dezalocare(LD lista) {
	Nod* aux = lista.prim;
	while (aux) {
		free(aux->info.numeFarmacist);
		Nod* copie = aux;
		free(aux);
		aux = copie;
	}
}

int main() {
	Farmacist f1;
	LD lista1;
	lista1.prim = NULL;
	lista1.ultim = NULL;

	FILE* f = fopen("Farm.txt", "r");
	char buffer[128];
	char sep[] = ",\n";
	char* token;

	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		f1.codAngajat = atoi(token);

		token = strtok(NULL, sep);
		f1.numeFarmacist = (char*)malloc(strlen(token) + 1);
		strcpy(f1.numeFarmacist, token);

		token = strtok(NULL, sep);
		f1.salariu = atof(token);

		lista1 = inserareInceput(lista1, f1);


	}

	afisareInceput(lista1);

	printf("\nSalariul max este: %5.2f", maxSalariu(lista1));

	free(f1.numeFarmacist);


	return 0;
}




#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct eveniment eveniment;
typedef struct nod nod;

struct eveniment {
	int id;
	char* descriere;
	int zi;
	float suma;
};

eveniment creareEven(int id,char* descriere,int zi, float suma) {
	eveniment e;
	e.id = id;
	e.descriere = (char*)malloc(strlen(descriere) + 1);
	strcpy(e.descriere, descriere);
	e.zi = zi;
	e.suma = suma;
	return e;
}

struct nod {
	eveniment info;
	nod* st;
	nod* dr;
};

nod* crearenod(eveniment e, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareEven(e.id, e.descriere, e.zi, e.suma);
	nou->st = st;
	nou->dr = dr;
	return nou;
}

nod* inserare(eveniment e, nod* rad) {
	if (rad) {
		if (e.id < rad->info.id) {
			rad->st = inserare(e, rad->st);
			return rad;
		}
		else if (e.id > rad->info.id) {
			rad->dr = inserare(e, rad->dr);
			return rad;
		}
		else return rad;
	}
	else {
		return crearenod(e, NULL, NULL);
	}
}

void afisare_preordine(nod* rad) {
	if (rad) {
		printf("%d, %s, %d, %5.2f\n", rad->info.id, rad->info.descriere, rad->info.zi, rad->info.suma);
		afisare_preordine(rad->st);
		afisare_preordine(rad->dr);
	}
}

int maxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else return b;
}

int nrNiveluri(nod* rad) {
	if (rad) {
		return 1 + maxim(nrNiveluri(rad->st), nrNiveluri(rad->dr));

	}
	else return 0;

}

int sumaFrunze(nod* rad, int* suma) {
	if (rad == NULL) {
		return 0;
	}
	if (rad->st == NULL && rad->dr == NULL) {
		(*suma) += rad->info.suma;
	}
	sumaFrunze(rad->st, suma);
	sumaFrunze(rad->dr, suma);
	
}

int nrNoduri(nod* rad) {
	if (rad) {
		return 1 + nrNoduri(rad->st) + nrNoduri(rad->dr);
	}
	else return 0;
}

void dezalocare(nod* rad) {
	if (rad) {
		dezalocare(rad->st);
		dezalocare(rad->dr);
		free(rad->info.descriere);
		free(rad);
	}
}


int main() {
	eveniment e1;
	nod* rad = NULL;
	FILE* f = fopen("even.txt", "r");
	char* token;
	char buffer[128];
	char sep[3] = ",\n";

	while (fgets(buffer, 128, f)) {
	
		token = strtok(buffer, sep);
		e1.id = atoi(token);

		token = strtok(NULL, sep);
		e1.descriere = (char*)malloc(strlen(token) + 1);
		strcpy(e1.descriere, token);

		token = strtok(NULL, sep);
		e1.zi = atoi(token);

		token = strtok(NULL, sep);
		e1.suma = atof(token);

		rad=inserare(e1, rad);
	}

	afisare_preordine(rad);

	printf("nr niveluri: %d\n", nrNiveluri(rad));
	int suma = 0;
	sumaFrunze(rad, &suma);
	printf("suma frunze: %d", suma);
	printf("\nnr noduri: %d\n", nrNoduri(rad));
	
}


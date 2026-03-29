#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct serial serial;
typedef struct nod nod;
typedef struct hashTable hashTable;

struct serial {
	unsigned int cod;//cheie
	char* nume;
	char* gen;
	float durata;
};

serial creareSerial(unsigned int cod, char* nume, char* gen, float durata) {
	serial s;
	s.cod = cod;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.gen = (char*)malloc(sizeof(char) + strlen(gen) + 1);
	strcpy(s.gen, gen);
	s.durata = durata;
	return s;
}

struct nod {
	serial info;
	nod* next;
};

struct hashTable {
	int dim;
	nod** vector;
};

int functieHash2(hashTable t, const char* nume) {
	return nume[0] % t.dim;
}

int inserareHash(hashTable t, serial s) {
	int poz = 0;
	if (t.vector) {
		poz = functieHash2(t, s.nume);
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = creareSerial(s.cod, s.nume, s.gen, s.durata);
		nou->next = NULL;
		if (t.vector[poz] == NULL) {
			t.vector[poz] = nou;
		}
		else {
			nod* aux = t.vector[poz];
			while(aux->next) {
				aux = aux->next;
			}
			aux->next = nou;
		}
	}
	return poz;
}

void afisareHash(hashTable t) {
	if (t.vector) {
		for (int i = 0; i < t.dim; i++) {
			if (t.vector[i]) {
				printf("Pozitie: %d\n\n", i);
				nod* aux = t.vector[i];
				while (aux) {
					printf("%u, %s, %s, %5.2f\n", aux->info.cod, aux->info.nume,
						aux->info.gen, aux->info.durata);
					aux = aux->next;
				}
			}
		}
	}
}

void dezalocareHash(hashTable t) {
	if (t.vector) {
		for (int i = 0; i < t.dim; i++) {
			if (t.vector[i]) {
				nod* aux = t.vector[i];
				while (aux) {
					free(aux->info.nume);
					free(aux->info.gen);
					nod* temp = aux->next;
					free(aux);
					aux = aux->next;
				}
			}
		}
		free(t.vector);
	}
}

void main() {
	hashTable tabela;
	tabela.dim = 10;
	tabela.vector = (nod**)malloc(sizeof(nod*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vector[i] = NULL;
	}

	serial s;
	FILE* file = fopen("Filme.txt", "r");
	char buffer[100];
	char sep[] = ",\n";
	char* token;

	while (fgets(buffer, 100, file)) {
		token = strtok(buffer, sep);
		s.cod = atoi(token);

		token = strtok(NULL, sep);
		s.nume = (char*)malloc(sizeof(char*) * strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, sep);
		s.gen = (char*)malloc(sizeof(char*) * strlen(token) + 1);
		strcpy(s.gen, token);

		token = strtok(NULL, sep);
		s.durata = atof(token);

		inserareHash(tabela, s);
		free(s.nume);
		free(s.gen);

	}
	afisareHash(tabela);



}


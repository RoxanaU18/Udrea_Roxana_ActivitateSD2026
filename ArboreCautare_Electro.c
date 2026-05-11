#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Electro Electro;
typedef struct nod nod;

struct Electro {
	unsigned short int cod;
	char* marca;
	char* model;
	char* tip;
	float pret;
};

Electro creareElectro(unsigned short int cod, const char* marca, 
	const char* model, const char* tip, float pret) {
	Electro e;
	e.cod = cod;
	e.marca = (char*)malloc(strlen(marca) + 1);
	strcpy(e.marca, marca);
	e.model= (char*)malloc(strlen(model) + 1);
	strcpy(e.model, model);
	e.tip= (char*)malloc(strlen(tip) + 1);
	strcpy(e.tip, tip);
	e.pret = pret;
	return e;
}

struct nod {
	Electro info;
	nod* st;
	nod* dr;
};

nod* crearenod(Electro e, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareElectro(e.cod, e.marca,
		e.model, e.tip, e.pret);
	nou->st = st;
	nou->dr = dr;
	return nou;
}

nod* inserare(Electro e, nod* rad) {
	if (rad) {
		if (e.cod < rad->info.cod) {
			rad->st = inserare(e, rad->st);
			return rad;
		}
		else if (e.cod > rad->info.cod) {
			rad->dr = inserare(e, rad->dr);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return crearenod(e, NULL, NULL);
	}
}

	void afisare_preordine(nod* rad) {
		if (rad) {
			printf("%u, %s, %s, %s, %5.2F\n", rad->info.cod, rad->info.marca,
				rad->info.model, rad->info.tip, rad->info.pret);
			afisare_preordine(rad->st);
			afisare_preordine(rad->dr);
		}
	}

	void afisare_postordine(nod* rad) {
		if (rad) {
			afisare_postordine(rad->st);
			afisare_postordine(rad->dr);
			printf("%u, %s, %s, %s, %5.2F\n", rad->info.cod, rad->info.marca,
				rad->info.model, rad->info.tip, rad->info.pret);
		}
	}

	void afisare_inordine(nod* rad) {
		if (rad) {
			afisare_inordine(rad->st);
			printf("%u, %s, %s, %s, %5.2F\n", rad->info.cod, rad->info.marca,
				rad->info.model, rad->info.tip, rad->info.pret);
			afisare_inordine(rad->dr);
			
		}
	}

	//cauta nodul care are codul dat
	nod* cauta(nod* rad, unsigned short int cod) {
		if (rad == NULL) {
			return NULL;
		}

			if (cod == rad->info.cod) {
				return rad;
			}

			if (cod < rad->info.cod) {
				return cauta(rad->st, cod);
			}
			else{
				return cauta(rad->dr, cod);
			}
		}

		//interschimba datele a doua noduri
		void interschimbare(nod * rad, unsigned short int cod1, unsigned short int cod2) {
			nod* n1 = cauta(rad, cod1);
			nod* n2 = cauta(rad, cod2);

			if (n1 == NULL || n2 == NULL)
				return;

			Electro aux = n1->info;
			n1->info = n2->info;
			n2->info = aux;
		}


	void dezalocare(nod* rad) {
		if (rad) {
			dezalocare(rad->st);
			dezalocare(rad->dr);
			free(rad->info.marca);
			free(rad->info.model);
			free(rad->info.tip);
			free(rad);
		}
	}

	void main(){
		Electro e;
		FILE* f = fopen("Electro.txt", "r");
		char* token;
		char buffer[100];
		char sep[3] = ",\n";

		nod* rad = NULL;

		while (fgets(buffer, 100, f)) {
			token = strtok(buffer,sep);
			e.cod = atoi(token);
			
			token = strtok(NULL, sep);
			e.marca= (char*)malloc(strlen(token) + 1);
			strcpy(e.marca, token);

			token = strtok(NULL, sep);
			e.model = (char*)malloc(strlen(token) + 1);
			strcpy(e.model, token);

			token = strtok(NULL, sep);
			e.tip = (char*)malloc(strlen(token) + 1);
			strcpy(e.tip, token);

			token = strtok(NULL, sep);
			e.pret = atof(token);

			rad = inserare(e, rad);

		}
		afisare_preordine(rad);

		printf("\n Arbore inainte de interschimbare: \n");
		afisare_preordine(rad);

		interschimbare(rad, 1002, 1005);

		printf("\n Arbore dupa interschimbare: \n");
		afisare_preordine(rad);
	}





	/*unsigned short int cod;
	char* marca;
	char* model;
	char* tip;
	float pret;*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct StructuraProiect Proiect;
typedef struct Nod Nod;
typedef struct LD LD;

struct StructuraProiect {
	unsigned int codProiect;
	char* titluProiect;
	char* benefeciar;
	unsigned char nrExecutanti;
	float buget;
};

//creare obiect

Proiect creareObiect(unsigned int codProiect,const char* titluProiect, const char* benefeciar,
unsigned char nrExecutanti,float buget) {
	Proiect p;
	p.codProiect = codProiect;
	p.titluProiect = (char*)malloc(strlen(titluProiect) + 1);
	strcpy(p.titluProiect, titluProiect);
	p.benefeciar= (char*)malloc(strlen(benefeciar) + 1);
	strcpy(p.benefeciar, benefeciar);
	p.nrExecutanti = nrExecutanti;
	p.buget = buget;
	return p;
}

struct Nod {
	Proiect info;
	Nod* next;
	Nod* prev;
};

struct LD {
	Nod* prim;
	Nod* ultim;
};

LD inserareInceput(LD lista, Proiect p) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info= creareObiect(p.codProiect, p.titluProiect, p.benefeciar, p.nrExecutanti,
		p.buget);
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
		while (aux != NULL) {
			printf("%u %s %s %u %5.2f\n", aux->info.codProiect, aux->info.titluProiect,
				aux->info.benefeciar, aux->info.nrExecutanti,
				aux->info.buget);
			aux = aux->next;
		}
	}
	else {
		printf("lista este goala");
	}

}

float valoareMedie(LD lista) {
	Nod* aux = lista.prim;
	float suma = 0;
	int nr = 0;
	while (aux) {
		suma += aux->info.buget;
		nr++;
		aux = aux->next;
	}
	return suma / nr;
}


//dezalocare
void dezalocare(LD lista) {
	Nod* aux = lista.prim;
	while (aux) {
		free(aux->info.titluProiect);
		free(aux->info.benefeciar);
		Nod* copie = aux->next;
		free(aux);
		aux = copie;
		}
}

int main() {
	Proiect p;
	LD lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* f = fopen("proiecte.txt", "r");
	char buffer[128];
	char sep[] = ",\n";
	char* token;
	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		p.codProiect = atoi(token);

		token = strtok(NULL, sep);
		p.titluProiect = (char*)malloc(strlen(token) + 1);
		strcpy(p.titluProiect, token);

		token = strtok(NULL, sep);
		p.benefeciar = (char*)malloc(strlen(token) + 1);
		strcpy(p.benefeciar, token);

		token = strtok(NULL, sep);
		p.nrExecutanti = atoi(token);

		token = strtok(NULL, sep);
		p.buget = atof(token);

		lista = inserareInceput(lista, p);
		free(p.titluProiect);
		free(p.benefeciar);

	}
	fclose(f);
	afisareInceput(lista);
	printf("\n\nValoare medie = %.2f\n", valoareMedie(lista));
	dezalocare(lista);

	

	return 0;
	
}




//creareObiect(p.codProiect, p.titluProiect, p.benefeciar, p.nrExecutanti,
//p.buget);

//unsigned int codProiect;
//char* titluProiect;
//char* benefeciar;
//unsigned char nrExecutanti;
//float buget;
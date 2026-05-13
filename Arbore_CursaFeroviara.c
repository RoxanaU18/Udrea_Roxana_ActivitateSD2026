#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct cursaFerov cursaFerov;
typedef struct nod nod;

struct cursaFerov {
	unsigned int nrCursa;
	char* data;
	unsigned char nrVagoane;
	unsigned short int nrbiletecumparate;
	float pret;
};

cursaFerov crearecursaFerov(unsigned int nrCursa, char* data, 
	unsigned char nrVagoane, unsigned short int nrbiletecumparate,
	float pret) {
	cursaFerov cf;
	cf.nrCursa = nrCursa;
	cf.data = (char*)malloc(strlen(data) + 1);
	strcpy(cf.data, data);
	cf.nrVagoane = nrVagoane;
	cf.nrbiletecumparate = nrbiletecumparate;
	cf.pret = pret;
	return cf;
}

struct nod {
	cursaFerov info;
	nod* st;
	nod* dr;
};

nod* crearenod(cursaFerov cf, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearecursaFerov(cf.nrCursa, cf.data, cf.nrVagoane, cf.nrbiletecumparate, cf.pret);
	nou->st = st;
	nou->dr = dr;
	return nou;
}

nod* inserare(cursaFerov cf, nod* rad) {
	if (rad) {
		if (cf.nrCursa < rad->info.nrCursa) {
			rad->st = inserare(cf, rad->st);
			return rad;
		}
		else if (cf.nrCursa > rad->info.nrCursa) {
			rad->dr = inserare(cf, rad->dr);
			return rad;
		}
		else return rad;
	}
	else {
		return crearenod(cf, NULL, NULL);
	}
}

void afisare_preordine(nod* rad) {
	if (rad) {
		printf("%u, %s, %u, %u, %5.2f\n", rad->info.nrCursa, rad->info.data, rad->info.nrVagoane, rad->info.nrbiletecumparate, rad->info.pret);
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

float nrtotalbilete(nod* rad) {
	if (rad == NULL) {
		return 0;
	}
	else  {
		return rad->info.pret + nrtotalbilete(rad->st) + nrtotalbilete(rad->dr);
	}
}

void dezalocare(nod* rad) {
	if (rad) {
		dezalocare(rad->st);
		dezalocare(rad->dr);
		free(rad->info.data);
		free(rad);
	}
}

int main() {
	cursaFerov cf1;
	nod* rad = NULL;

	FILE* f = fopen("Curse.txt", "r");
	char* token;
	char buffer[128];
	char sep[3] = ",\n";

	while (fgets(buffer, 128, f)) {
	
		token = strtok(buffer, sep);
		cf1.nrCursa = atoi(token);

		token = strtok(NULL, sep);
		cf1.data = (char*)malloc(strlen(token) + 1);
		strcpy(cf1.data, token);

		token = strtok(NULL, sep);
		cf1.nrVagoane = atoi(token);

		token = strtok(NULL, sep);
		cf1.nrbiletecumparate = atoi(token);

		token = strtok(NULL, sep);
		cf1.pret = atof(token);

		rad = inserare(cf1, rad);

	}
	afisare_preordine(rad);

	printf("nr totalniv: %d\n", nrNiveluri(rad));
	printf("nr total bilete cumparate: %5.2f\n", nrtotalbilete(rad));

	
}


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>


//structura
//obiectul
//nod
//creare nod
//inserare nod
//afisare nod
//dezalocare
//main
//citire fisier
//afisare

typedef struct rezervare rezervare;
typedef struct nod nod;

struct rezervare {
	unsigned int id; 
	char* denumire;
	unsigned char nrCamereRez;
	char* numeCl;
	float sumaPlata;
};

rezervare crearerezervare(unsigned int id, const char* denumire, 
	unsigned char nrCamereRez, const char* numeCl, float sumaPlata){
	rezervare r;
	r.id = id;
	r.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(r.denumire, denumire);
	r.nrCamereRez = nrCamereRez;
	r.numeCl = (char*)malloc(strlen(numeCl)+ 1);
	strcpy(r.numeCl, numeCl);
	r.sumaPlata = sumaPlata;
	return r;
}

struct nod {
	rezervare info;
	nod* stang;
	nod* drept;
};

nod* crearenod(rezervare r, nod* stang, nod* drept) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearerezervare(r.id, r.denumire, r.nrCamereRez,
		r.numeCl, r.sumaPlata);
	nou->stang = stang;
	nou->drept = drept;
	return nou;
}


nod* inserare(rezervare r, nod* rad) {
	if (rad) {
		if (r.id < rad->info.id) {
			rad->stang = inserare(r, rad->stang);
			return rad;
		}
		else if (r.id > rad->info.id) {
			rad->drept = inserare(r, rad->drept);
			return rad;
		}
		else {
			return rad;
		}
	}
	else return crearenod(r, NULL, NULL);
}

void afisare_preordine(nod* rad) {
	if (rad) {
		printf("%u %s %u %s %5.2f \n", rad->info.id, rad->info.denumire,
			rad->info.nrCamereRez, rad->info.numeCl, rad->info.sumaPlata);
		afisare_preordine(rad->stang);
		afisare_preordine(rad->drept);
	}
}

void dezalocare(nod* rad) {
	if (rad) {
		dezalocare(rad->stang);
		dezalocare(rad->drept);
		free(rad->info.denumire);
		free(rad->info.numeCl);
		free(rad);
	}
}

void main() {

	rezervare r1;
	FILE* f = fopen("rezervare.txt", "r");
	char* token;
	char buffer[100];
	char sep[3] = ",\n";

	nod* rad = NULL;

	while (fgets(buffer, 100, f)) {
		token = strtok(buffer, sep);
		r1.id = atoi(token);

		token = strtok(NULL, sep);
		r1.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(r1.denumire, token);

		token = strtok(NULL, sep);
		r1.nrCamereRez = atoi(token);

		token = strtok(NULL, sep);
		r1.numeCl = (char*)malloc(strlen(token) + 1);
		strcpy(r1.numeCl, token);

		token = strtok(NULL, sep);
		r1.sumaPlata = atof(token);

		rad = inserare(r1, rad);
	}

		afisare_preordine(rad);
		
	


}



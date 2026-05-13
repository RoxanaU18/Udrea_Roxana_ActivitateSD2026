#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct farmacie farmacie;
typedef struct nod nod;

struct farmacie {
	unsigned short int id;
	char* denumire;
	float cifraAfaceri;
	char* numeFarmacist;
	unsigned char nrAngajati;
	char* localitate;
};

farmacie crearefarmacie(unsigned short int id, char* denumire, float cifraAfaceri, char* numeFarmacist,
unsigned char nrAngajati,char* localitate) {
	farmacie f;
	f.id = id;
	f.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(f.denumire, denumire);
	f.cifraAfaceri = cifraAfaceri;
	f.numeFarmacist= (char*)malloc(strlen(numeFarmacist) + 1);
	strcpy(f.numeFarmacist, numeFarmacist);
	f.nrAngajati = nrAngajati;
	f.localitate = (char*)malloc(strlen(localitate) + 1);
	strcpy(f.localitate, localitate);
	return f;
}

struct nod {
	farmacie info;
	nod* st;
	nod* dr;
};

nod* crearenod(farmacie f, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearefarmacie(f.id, f.denumire, f.cifraAfaceri, f.numeFarmacist, f.nrAngajati, f.localitate);
	nou->st = st;
	nou->dr = dr;
	return nou;
}



nod* inserare(farmacie f, nod* rad) {
	if (rad) {
		if (f.id < rad->info.id) {
			rad->st = inserare(f, rad->st);
			return rad;
		}
		else if (f.id > rad->info.id) {
			rad->dr = inserare(f, rad->dr);
			return rad;
		}
		else return rad;

	}
	else {
		return crearenod(f, NULL, NULL);
	}
}

void afisare_preordine(nod* rad) {
	if (rad) {
		printf("%u, %s, %5.2f, %s, %u, %s\n", rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacist,
			rad->info.nrAngajati, rad->info.localitate);
		afisare_preordine(rad->st);
		afisare_preordine(rad->dr);
	}
}
void afisare_postordine(nod* rad) {
	if (rad) {
		afisare_postordine(rad->st);
		afisare_postordine(rad->dr);
		printf("%u, %s, %5.2f, %s, %u, %s\n", rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacist,
			rad->info.nrAngajati, rad->info.localitate);
	}
}
void afisare_inordine(nod* rad) {
	if (rad) {
		afisare_inordine(rad->st);
		printf("%u, %s, %5.2f, %s, %u, %s\n", rad->info.id, rad->info.denumire, rad->info.cifraAfaceri, rad->info.numeFarmacist,
			rad->info.nrAngajati, rad->info.localitate);
		afisare_inordine(rad->dr);
		
	}
}

int nrTotalAng(nod* rad, char* localitate) {
	if (rad == NULL) {
		return 0;
	}
	if (strcmp(rad->info.localitate, localitate) == 0) {
		return rad->info.nrAngajati + nrTotalAng(rad->st, localitate) + nrTotalAng(rad->dr, localitate);

	}
	return nrTotalAng(rad->st, localitate) + nrTotalAng(rad->dr, localitate);
}	

//sau
//int nrTotalAng(char* localitate, nod* rad) {
//	if (rad == NULL)
//		return 0;
//
//	int s = nrTotalAng(localitate, rad->st) +
//		nrTotalAng(localitate, rad->dr);
//
//	if (strcmp(rad->info.localitate, localitate) == 0)
//		s += rad->info.nrAngajati;
//
//	return s;
//}

int nrtotalFrunze(nod* rad) {
	if (rad == NULL) {
		return 0;
	}
	if (rad->st == 0 && rad->dr == 0) {
		return rad->info.nrAngajati;
	}
	return nrtotalFrunze(rad->st) + nrtotalFrunze(rad->dr);
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


void dezalocare(nod* rad) {
	if (rad) {
		dezalocare(rad->st);
		dezalocare(rad->dr);
		free(rad->info.denumire);
		free(rad->info.numeFarmacist);
		free(rad->info.localitate);
		free(rad);
	}
}

int main() {
	farmacie f1;
	nod* rad = NULL;

	FILE* f = fopen("farma.txt", "r");
	char* token;
	char buffer[128];
	char sep[3] = ",\n";

	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		f1.id = atoi(token);

		token = strtok(NULL, sep);
		f1.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(f1.denumire, token);

		token = strtok(NULL, sep);
		f1.cifraAfaceri = atof(token);

		token = strtok(NULL, sep);
		f1.numeFarmacist = (char*)malloc(strlen(token) + 1);
		strcpy(f1.numeFarmacist, token);

		token = strtok(NULL, sep);
		f1.nrAngajati = atoi(token);

		token = strtok(NULL, sep);
		f1.localitate = (char*)malloc(strlen(token) + 1);
		strcpy(f1.localitate, token);

		rad=inserare(f1, rad);
	}

	afisare_preordine(rad);
	printf("\n");
	afisare_postordine(rad);
	printf("\n");
	afisare_inordine(rad);

	printf("nr total angajati bucuresti: %d\n", nrTotalAng(rad, " Bucuresti;"));
	printf("nr angajati frunze: %d\n", nrtotalFrunze(rad));
	printf("Nr total niveluri: %d\n", nrNiveluri(rad));

}




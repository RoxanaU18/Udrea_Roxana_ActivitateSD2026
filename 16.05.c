#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

//inaltime, suma spectatori, suma locuri, nr spectacole, grad ocupare, totalPop

typedef struct spectacol spectacol;
typedef struct nod nod;

struct spectacol {
	int id;
	int nrSpectatori;
	char* titlu;
	int nrLocuri;

};

struct nod {
	spectacol info;
	nod* st;
	nod* dr;
};

spectacol crearespectacol(int id, int nrSpectatori, char* titlu, int nrLocuri) {
	spectacol s;
	s.id = id;
	s.nrSpectatori = nrSpectatori;
	s.titlu = (char*)malloc(strlen(titlu) + 1);
	strcpy(s.titlu, titlu);
	s.nrLocuri = nrLocuri;
	return s;
}

nod* crearenod(spectacol s, nod* st, nod* dr) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearespectacol(s.id, s.nrSpectatori, s.titlu, s.nrLocuri);
	nou->st = st;
	nou->dr = dr;
	return nou;
}

nod* inserare(spectacol s, nod* rad) {
	if (rad) {
		if (s.id < rad->info.id) {
			rad->st = inserare(s, rad->st);
			return rad;
		}
		if (s.id > rad->info.id) {
			rad->dr = inserare(s, rad->dr);
			return rad;
		}
		else return rad;
	}
	else {
		return crearenod(s, NULL, NULL);
	}
}

void afisare_preordine(nod* rad) {
	if (rad) {
		printf("%d, %d, %s, %d\n", rad->info.id, rad->info.nrSpectatori, rad->info.titlu, rad->info.nrLocuri);
		afisare_preordine(rad->st);
		afisare_preordine(rad->dr);
	}
}

void rotireSt(nod** rad) {
	nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	(*rad) = aux;
}

void dezalocare(nod* rad) {
	if (rad) {
		dezalocare(rad->st);
		dezalocare(rad->dr);
		free(rad->info.titlu);
		free(rad);
	}
}

int nrFrunze(nod* rad) {
	if (rad == NULL) {
		return 0;
	}

	if (rad->st == NULL && rad->dr == NULL) {
		return 1;
	}
	return nrFrunze(rad->st) + nrFrunze(rad->dr);
}

//inaltime
int maxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else return b;
}

int inaltime(nod* rad) {
	if (rad) {
		return 1 + maxim(inaltime(rad->st), inaltime(rad->dr));
	}
	return 0;
}

//suma spectatori
int sumaSpect(nod* rad) {
	if (rad) {
		return rad->info.nrSpectatori + sumaSpect(rad->st) + sumaSpect(rad->dr);
	}
	return 0;
}

//suma locuri
int sumaLocuri(nod* rad) {
	if (rad) {
		return rad->info.nrLocuri + sumaLocuri(rad->st) + sumaLocuri(rad->dr);
	}
	return 0;
}

//nrspectacole
int nrspectacole(nod* rad) {
	if (rad) {
		return 1+ (nrspectacole(rad->st) + nrspectacole(rad->dr));
	}
	return 0;
}

float gradocupare(nod* rad) {
	if (rad) {
		int spectatori = sumaSpect(rad);
		int locuri = sumaLocuri(rad);
		return (float)spectatori / locuri * 100;
	}
	return 0;
}

//int spectPop(nod* rad, char* cautatiltu) {
//	if (rad) {
//		if (strcpmp(rad->info.titlu, cautatiltu) == 0) {
//			return rad->info.nrSpectatori +
//				spectPop(rad->st, cautatiltu) +
//				spectPop(rad->dr, cautatiltu);
//		}
//		return spectPop(rad->st, cautatiltu) +
//			spectPop(rad->dr, cautatiltu);
//	}
//	return 0;
//}

int nrnoduri(nod* rad, int* noduri) {
	if (rad) {
		(*noduri)++;
		nrnoduri(rad->st, noduri);
		nrnoduri(rad->dr, noduri);
	}
}

int determinaNduri(nod* rad) {
	if (rad) {
		return determinaNduri(rad->st) + determinaNduri(rad->dr) + 1;
		}
	return 0;
}

void main() {
	spectacol s1;
	nod* rad = NULL;

	FILE* f = fopen("ABC_spect.txt", "r");
	char* token;
	char buffer[128];
	char sep[3] = (",\n");

	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		s1.id = atoi(token);

		token = strtok(NULL, sep);
		s1.nrSpectatori = atoi(token);

		token = strtok(NULL, sep);
		s1.titlu = (char*)malloc(strlen(token) + 1);
		strcpy(s1.titlu, token);

		token = strtok(NULL, sep);
		s1.nrLocuri = atoi(token);

		rad = inserare(s1, rad);
	}
	afisare_preordine(rad);

	printf("Inaltimea este: %d\n", inaltime(rad));
	printf("Suma spect este: %d\n", sumaSpect(rad));
	printf("Suma spect este: %d\n", sumaLocuri(rad));
	printf("Nr spectacole este: %d\n", nrspectacole(rad));
	printf("Grad ocupare este: %5.2f%%\n", gradocupare(rad));
	//printf("Total pop: %d\n", spectPop(rad, "Concert Pop"));
	int noduri = 0;
	nrnoduri(rad, &noduri);
	printf("Numar noduri: %d\n", noduri);
	printf("Determina noduri: %d\n", determinaNduri(rad));
	rotireSt(&rad);
	printf("Nr frunza este: %d\n", nrFrunze(rad));
	
	
}


//int id;
//int nrSpectatori;
//char* titlu;
//int nrLocuri;
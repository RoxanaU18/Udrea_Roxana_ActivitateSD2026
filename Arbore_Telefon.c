#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct telefon telefon;
typedef struct nod nod;


struct telefon {
	unsigned int id;
	char* producator;
	float valoare;
};

telefon crearetelefon(unsigned int id, char* producator, float valoare) {
	telefon t;
	t.id = id;
	t.producator = (char*)malloc(strlen(producator) + 1);
	strcpy(t.producator, producator);
	t.valoare = valoare;
	return t;
}

struct nod {
	telefon info;
	nod* stang;
	nod* drept;
};

nod* creareNod(telefon t, nod* stang, nod* drept) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = crearetelefon(t.id, t.producator, t.valoare);
	nou->stang = stang;
	nou->drept=drept;
	return nou;
}

nod* inserareArbore(nod* rad, telefon t) {
	if (rad) {
		if (t.id < rad->info.id) {
			rad->stang = inserareArbore(rad->stang, t);
			return rad;
		}
		else if (t.id > rad->info.id) {
			rad->drept = inserareArbore(rad->drept, t);
			return rad;
		}
		else {
			return rad;
		}
	}
	else {
		return creareNod(t, NULL, NULL);
	}
}

void preordine(nod* rad) {
	if (rad) {
		printf("%u %s %5.2f \n", rad->info.id, rad->info.producator, rad->info.valoare);
		preordine(rad->stang);
		preordine(rad->drept);
	}
}

void postordine(nod* rad) {
	if (rad) {
		postordine(rad->stang);
		postordine(rad->drept);
		printf("%u %s %5.2f \n", rad->info.id, rad->info.producator, rad->info.valoare);
	}
}

void inordine(nod* rad) {
	if (rad) {
		inordine(rad->stang);
		printf("%u %s %5.2f \n", rad->info.id, rad->info.producator, rad->info.valoare);
		inordine(rad->drept);
	}
}


void main() {
	telefon t1 = crearetelefon(7, "Apple", 7500.5);
	telefon t2 = crearetelefon(4, "Samsung", 5500.5);
	telefon t3 = crearetelefon(3, "Nokia", 1500.5);
	telefon t4 = crearetelefon(9, "Motorola", 2500.5);
	telefon t5 = crearetelefon(5, "Honor", 3500.5);
	telefon t6 = crearetelefon(1, "Allview", 500.5);
	telefon t7 = crearetelefon(8, "Yoxo", 400.5);

	nod* rad = NULL;
	rad = inserareArbore(rad, t1);
	rad = inserareArbore(rad, t2);
	rad = inserareArbore(rad, t3);
	rad = inserareArbore(rad, t4);
	rad = inserareArbore(rad, t5);
	rad = inserareArbore(rad, t6);
	rad = inserareArbore(rad, t7);

	inordine(rad);

	printf("\n\n");

	preordine(rad);

	printf("\n\n");

	postordine(rad);

}

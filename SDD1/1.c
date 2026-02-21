#include<stdio.h>
#include<malloc.h>

typedef struct Aparat Aparat;

struct Aparat {
	int id;
	char* denumire;
	float pret;
	char serie;
};
struct Aparat initializare(int id, char* denumire, float pret, char serie) {
	struct Aparat s;
	s.id = id;
	s.denumire = (char*)malloc(sizeof(char)*(strlen(denumire)+1));
	strcpy(s.denumire, denumire);
	s.pret = pret;
	s.serie = serie;
	return s;
}

Aparat copiaza(Aparat a) {
	return initializare(a.id,a.denumire, a.pret, a.serie);
}

void afisare(struct Aparat s) {
	printf("%d. Aparatul %s cu pretul %5.2f are seria %c.\n",
		s.id, s.denumire, s.pret, s.serie);
}

void afisareVector(struct Aparat* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(*(vector+i));		
	}
}

struct Aparat* copiazaPrimeleNElemente(Aparat* vector, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate < nrElemente) {
		struct Aparat* vectorNou = malloc(sizeof(Aparat) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = copiaza(vector[i]);
		}
		return vectorNou;
	}
	else {
		return NULL;
	}
}

void dezalocare(struct Aparat** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*nrElemente = 0;
	*vector = NULL;
}

void copiazaAnumiteElemente(struct Aparat* vector, char nrElemente, float prag, struct Aparat** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret < prag) {
			(*dimensiune)++;
		}
	}

	*vectorNou = malloc(sizeof(Aparat) * (*dimensiune));
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].pret < prag) {
			(*vectorNou)[*dimensiune] = copiaza(vector[i]);
			(*dimensiune)++;
		}
	}
}

struct Aparat getPrimulElementConditionat(struct Aparat* vector, int nrElemente, const char* numeCautat) {
	Aparat s;
	s.id = -1;
	s.denumire = NULL;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(numeCautat, vector[i].denumire)==0) {
			s = copiaza(vector[i]);
		}
	}
	return s;
}
	


int main() {
	struct Aparat aparat = initializare(1, "Laptop", 2000.99f, 'A');
	afisare(aparat);

	int nrAparate = 5;
	Aparat* vector = (Aparat*)malloc(sizeof(Aparat)*nrAparate);
	vector[0] = initializare(1, "PC", 3000.99f, 'A');
	vector[1] = initializare(2, "Laptop", 2000.99f, 'B');
	vector[2] = initializare(3, "Imprimanta", 1500.99f, 'C');
	vector[3] = initializare(4, "Scanner", 4000.99f, 'A');
	vector[4] = initializare(5, "Fax", 500.99f, 'D');
	
	afisareVector(vector, nrAparate);
	printf("\n\n");


	int nrCopiate=3;
	Aparat* scurt = copiazaPrimeleNElemente(vector, nrAparate, nrCopiate);

	afisareVector(scurt, nrCopiate);
	dezalocare(&scurt, &nrCopiate);
	Aparat* filtrat = NULL;
	int dimensiune = 0;
	copiazaAnumiteElemente(vector, nrAparate, 70, &filtrat, &dimensiune);
	printf("\nVector filtrat:\n");
	afisareVector(filtrat, dimensiune);
	dezalocare(&filtrat, &dimensiune);

	Aparat aparatCautat = getPrimulElementConditionat(vector, nrAparate, "TV");
	printf("\nAparat cautat:\n");
	afisare(aparatCautat);
	if (aparatCautat.id != -1) {
		free(aparatCautat.denumire);
	}
	free(aparat.denumire);
	dezalocare(&vector, &nrAparate);
	return 0;
}
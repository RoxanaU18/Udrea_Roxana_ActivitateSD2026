#include<stdio.h>
#include<malloc.h>

typedef struct Aparat Aparat;

struct Aparat {
	int id;
	char* denumire;
	float pret;
	char serie;
};
struct Aparat initializare(int id, const char* denumire, float pret, char serie) {
	struct Aparat s;
	s.id = id;
	s.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(s.denumire, denumire);
	s.pret = pret;
	s.serie = serie;
	return s;
}

Aparat copiaza(Aparat a) {
	return initializare(a.id, a.denumire, a.pret, a.serie);
}

void afisare(struct Aparat s) {
	printf("% d. Aparatul %s cu pretul %5.2f are seria %c. \n", 
		s.id, s.denumire, s.pret, s.serie);
}

void afisareVector(struct Aparat* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(*(vector + i));
	}
}

struct Aparat* copiazaPrimeleNElemente(struct Aparat* vector, int nrElemente, int nrElementeCopiate) {
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
	struct Aparat *vectorNou=NULL;

	return vectorNou;
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
		if (strcmp(numeCautat, vector[i].denumire) == 0) {
			s = copiaza(vector[i]);
		}
			}
	return s;



}
	


int main() {

	struct Aparat aparat = initializare(1, "Laptop", 200, 'A');
	afisare(aparat);

	int nrAparate = 5;
	Aparat* vector = (Aparat*)malloc(sizeof(Aparat) * nrAparate);
	vector[0] = initializare(2, "PC", 2000.99F, 'A');
	vector[1] = initializare(3, "Imprimanta", 1000.99F, 'B');
	vector[2] = initializare(4, "Fac", 500.30F, 'D');
	vector[3] = initializare(5, "Scanner", 5000.99F, 'A');
	vector[4] = initializare(6, "Unitate", 3000.99F, 'A');

	afisareVector(vector, nrAparate);
	printf("\n\n");

	int nrCopiate = 2;
	Aparat* scurt = copiazaPrimeleNElemente(vector, nrAparate, nrCopiate);

	afisareVector(scurt, nrCopiate);
		dezalocare(&scurt, &nrCopiate);
		Aparat* filtrat = NULL;
		int dimensiune = 0;
		copiazaAnumiteElemente(vector, nrAparate, 50, &filtrat, &dimensiune);
		printf("\nVector filtrat:\n");
		afisareVector(filtrat, dimensiune);
		dezalocare(&filtrat, &dimensiune);
	
		Aparat aparatCautat = getPrimulElementConditionat(vector, nrAparate, "TV");
		printf("\nAparatt cautat:\n");
		afisare(aparatCautat);
		if (aparatCautat.id != -1) {
			free(aparatCautat.denumire);
		}
		free(aparat.denumire);
		dezalocare(&vector, &nrAparate);

	

	return 0;
}
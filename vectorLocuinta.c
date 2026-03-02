#include<stdio.h>
#include<malloc.h>

typedef struct Locuinta Locuinta;

struct Locuinta {
	int id;
	float suprafata;
	char* denumire;
	char tip;
};
struct Locuinta initializare(int id, float suprafata, const char* denumire, char tip) {
	struct Locuinta l;
	l.id = id;
	l.suprafata = suprafata;
	l.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy(l.denumire, denumire);
	l.tip = tip;
	return l;
}

void afisare(struct Locuinta l) {
	printf("%d. Locuinta %s de tipul %c are suprafata de %5.2f mp \n", l.id, l.denumire, l.tip, l.suprafata);
}

void afisareVector(struct Locuinta* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(*(vector + i));

	}
}

//struct Sablon* copiazaPrimeleNElemente(struct Sablon* vector, int nrElemente, int nrElementeCopiate) {
//	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
//	struct Sablon *vectorNou=NULL;
//
//	return vectorNou;
//}
//
//void dezalocare(struct Sablon** vector, int* nrElemente) {
//	//dezalocam elementele din vector si vectorul
//}
//
//void copiazaAnumiteElemente(struct Sablon* vector, char nrElemente, float prag, struct Sablon** vectorNou, int* dimensiune) {
//	//parametrul prag poate fi modificat in functie de 
//	// tipul atributului ales pentru a indeplini o conditie
//	//este creat un nou vector cu elementele care indeplinesc acea conditie
//}
//
//struct Sablon getPrimulElementConditionat(struct Sablon* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Sablon s;
//	s.id = 1;
//
//	return s;
//}
	


int main() {

	struct Locuinta locuinta = initializare(1, 60.5, "Apartament", 'A');
	afisare(locuinta);

	int nrLocuinte = 3;
	Locuinta* vector = (Locuinta*)malloc(sizeof(Locuinta) * nrLocuinte);
	vector[0] = initializare(2, 50, "Casa curte", 'B');
	vector[1] = initializare(3, 100, "Vila curte", 'A');
	vector[2] = initializare(4, 150, "Duplex", 'A+');
	afisareVector(vector, nrLocuinte);
	printf("\n\n");

	return 0;
}
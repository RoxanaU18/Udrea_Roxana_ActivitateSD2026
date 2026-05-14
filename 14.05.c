#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct student student;
typedef struct heap heap;

struct student {
	int id;
	char* nume;
	float medie;
};

student crearestudent(int id, char* nume, float medie) {
	student s;
	s.id = id;
	s.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.medie = medie;
	return s;
}

struct heap {
	int dim;
	student* vector;
};

void filtrare(heap h, int i) {
	int max = i;
	int st = 2 * i + 1;
	int dr = 2 * i + 2;

	if (st<h.dim && h.vector[st].id > h.vector[max].id)
		max = st;
	if (dr<h.dim && h.vector[dr].id > h.vector[max].id)
		max = dr;

	if (max != i) {
		student aux = h.vector[i];
		h.vector[i] = h.vector[max];
		h.vector[max] = aux;
		filtrare(h, max);
	}
}

void afisare(heap h) {
	for (int i = 0; i < h.dim; i++) {
		printf("%d, %s, %5.2f\n\n", h.vector[i].id, h.vector[i].nume, h.vector[i].medie);
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.dim; i++) {
		free(h.vector[i].nume);
	}
	free(h.vector);
}

student extragere(heap* h) {
	student extras = h->vector[0];

	h->vector[0] = h->vector[h->dim - 1];
	h->dim--;

	filtrare(*h, 0);

	return extras;
}

void main() {
	student s1;
	heap heap;
	heap.dim = 5;
	heap.vector = (student*)malloc(sizeof(student) * heap.dim);

	FILE* f = fopen("heap_text.txt", "r");
	char* token;
	char buffer[128];
	char sep[3] = ",\n";

	int nr = 0;

	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		s1.id = atoi(token);

		token = strtok(NULL, sep);
		s1.nume = (char*)malloc(strlen(token) + 1);
		strcpy(s1.nume, token);

		token = strtok(NULL, sep);
		s1.medie = atof(token);

		heap.vector[nr++] = crearestudent(s1.id, s1.nume, s1.medie);


	}

	//afisare(heap);
	filtrare(heap, 0);
	/*for (int i = (heap.dim - 2) / 2; i >= 0; i--) { //sau asa
		filtrare(heap, i);
	}*/
	afisare(heap);
}

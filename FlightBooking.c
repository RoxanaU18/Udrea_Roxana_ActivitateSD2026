#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct FlightBooking FlightBooking;
typedef struct heap heap;

struct FlightBooking {
	unsigned int codRezervare;
	char* companieAeriana;
	unsigned char nrLocuriRez;
	char* numePasager;
	float pretBilet;
};

FlightBooking creareFlightBooking(unsigned int codRezervare, const char* companieAeriana,
unsigned char nrLocuriRez, const char* numePasager, float pretBilet) {
	FlightBooking fb;
	fb.codRezervare = codRezervare;
	fb.companieAeriana = (char*)malloc(strlen(companieAeriana) + 1);
	strcpy(fb.companieAeriana, companieAeriana);
	fb.nrLocuriRez = nrLocuriRez;
	fb.numePasager = (char*)malloc(strlen(numePasager) + 1);
	strcpy(fb.numePasager, numePasager);
	fb.pretBilet = pretBilet;
	return fb;
}

struct heap {
	int dim;
	FlightBooking* vector;
};

void filtrare(heap heap, int pozNod) {
	int poz = pozNod;
	int pozfiuSt = 2 * poz + 1;
	int pozfiuDr = 2 * poz + 2;

	if (pozfiuSt < heap.dim && heap.vector[poz].codRezervare < heap.vector[pozfiuSt].codRezervare) {
		poz = pozfiuSt;
	}
	if (pozfiuDr < heap.dim && heap.vector[poz].codRezervare < heap.vector[pozfiuDr].codRezervare) {
		poz = pozfiuDr;
	}
	if (poz != pozNod) {
		FlightBooking aux = heap.vector[poz];
		heap.vector[poz] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
		if (poz < (heap.dim - 2) / 2) {
			filtrare(heap, poz);
		}
	}
}

void afisare(heap heap) {
	for (int i = 0; i < heap.dim; i++) {
		printf("%u %s %u %s %5.2f\n", heap.vector[i].codRezervare, heap.vector[i].companieAeriana,
			heap.vector[i].nrLocuriRez, heap.vector[i].numePasager,
			heap.vector[i].pretBilet);
	}
}

void dezalocare(heap heap) {
	for (int i = 0; i < heap.dim; i++) {
		free(heap.vector[i].companieAeriana);
		free(heap.vector[i].numePasager);
	}
	free(heap.vector);
}

FlightBooking extragere(heap* heap) {
	FlightBooking aux = heap->vector[0];
	if (heap->dim > 0) {
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dim - 1];
		heap->vector[heap->dim - 1] = aux;
		heap->dim--;
		for (int i = (heap->dim - 2) / 2; i >= 0; i--) {
			filtrare(*heap, i);
		}
	}
	return aux;
}

void main() {
	heap heap;
	heap.dim = 5;
	heap.vector = (FlightBooking*)malloc(sizeof(FlightBooking) * heap.dim);
	FlightBooking fl;

	FILE* f = fopen("Flights.txt", "r");
	char* token;
	char buffer[128];
	char sep[] = ",\n";

	int nr = 0;

	while (fgets(buffer, 128, f)) {
		token = strtok(buffer, sep);
		fl.codRezervare = atoi(token);

		token = strtok(NULL, sep);
		fl.companieAeriana = (char*)malloc(strlen(token) + 1);
		strcpy(fl.companieAeriana, token);

		token = strtok(NULL, sep);
		fl.nrLocuriRez = atoi(token);

		token = strtok(NULL, sep);
		fl.numePasager = (char*)malloc(strlen(token) + 1);
		strcpy(fl.numePasager, token);

		token = strtok(NULL, sep);
		fl.pretBilet = atof(token);
		
		heap.vector[nr++] = creareFlightBooking(fl.codRezervare, fl.companieAeriana,
			fl.nrLocuriRez, fl.numePasager, fl.pretBilet);
	}
	filtrare(heap, 0);
	afisare(heap);
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produs produs;
typedef struct nod nod;

struct produs {
    int cod;
    char* denumire;
    float pret;
};

produs creareProdus(int cod, const char* denumire, float pret) {
    produs p;
    p.cod = cod;
    p.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(p.denumire, denumire);
    p.pret = pret;
    return p;
}

struct nod {
    produs info;
    nod* stanga;
    nod* dreapta;
};

nod* creareNod(produs p, nod* st, nod* dr) {
    nod* nou = (nod*)malloc(sizeof(nod));

    nou->info.cod = p.cod;
    nou->info.denumire = (char*)malloc(strlen(p.denumire) + 1);
    strcpy(nou->info.denumire, p.denumire);
    nou->info.pret = p.pret;

    nou->stanga = st;
    nou->dreapta = dr;

    return nou;
}

nod* inserare(nod* rad, produs p) {
    if (rad) {
        if (p.cod < rad->info.cod) {
            rad->stanga = inserare(rad->stanga, p);
        }
        else if (p.cod > rad->info.cod) {
            rad->dreapta = inserare(rad->dreapta, p);
        }
        return rad;
    }
    else {
        return creareNod(p, NULL, NULL);
    }
}

void afisare(produs p) {
    printf("%d  %s  %.2f lei\n", p.cod, p.denumire, p.pret);
}

void inordine(nod* rad) {
    if (rad) {
        inordine(rad->stanga);
        afisare(rad->info);
        inordine(rad->dreapta);
    }
}

void preordine(nod* rad) {
    if (rad) {
        afisare(rad->info);
        preordine(rad->stanga);
        preordine(rad->dreapta);
    }
}

void postordine(nod* rad) {
    if (rad) {
        postordine(rad->stanga);
        postordine(rad->dreapta);
        afisare(rad->info);
    }
}

void dezalocare(nod* rad) {
    if (rad) {
        dezalocare(rad->stanga);
        dezalocare(rad->dreapta);

        free(rad->info.denumire);
        free(rad);
    }
}

int main() {

    produs p1 = creareProdus(10, "Laptop", 3500);
    produs p2 = creareProdus(5, "Mouse", 80);
    produs p3 = creareProdus(15, "Tastatura", 150);
    produs p4 = creareProdus(3, "USB", 30);
    produs p5 = creareProdus(7, "Monitor", 900);
    produs p6 = creareProdus(12, "Boxe", 200);

    nod* rad = NULL;

    rad = inserare(rad, p1);
    rad = inserare(rad, p2);
    rad = inserare(rad, p3);
    rad = inserare(rad, p4);
    rad = inserare(rad, p5);
    rad = inserare(rad, p6);

    printf("Afisare inordine:\n");
    inordine(rad);

    printf("\nAfisare preordine:\n");
    preordine(rad);

    printf("\nAfisare postordine:\n");
    postordine(rad);

    free(p1.denumire);
    free(p2.denumire);
    free(p3.denumire);
    free(p4.denumire);
    free(p5.denumire);
    free(p6.denumire);

    dezalocare(rad);

    return 0;
}
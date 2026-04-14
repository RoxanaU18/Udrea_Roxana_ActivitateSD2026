#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct filme filme;
typedef struct nodArb nodArb;

struct filme {
    int idFilm;
    char* denumire;
    float pret;
    float nrBilete;
};

struct nodArb {
    int BF;
    filme inf;
    nodArb* stanga;
    nodArb* dreapta;
};

filme creareFilme(int idFilm, const char* denumire, float pret, float nrBilete) {
    filme f;
    f.idFilm = idFilm;
    f.denumire = (char*)malloc(strlen(denumire) + 1);
    if (f.denumire != NULL) {
        strcpy(f.denumire, denumire);
    }
    f.pret = pret;
    f.nrBilete = nrBilete;
    return f;
}

nodArb* creareNod(nodArb* stanga, nodArb* dreapta, filme f) {
    nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
    if (nou == NULL) {
        return NULL;
    }

    nou->inf = creareFilme(f.idFilm, f.denumire, f.pret, f.nrBilete);
    nou->stanga = stanga;
    nou->dreapta = dreapta;
    nou->BF = 0;

    return nou;
}

nodArb* inserare(filme f, nodArb* rad) {
    if (rad != NULL) {
        if (f.idFilm < rad->inf.idFilm) {
            rad->stanga = inserare(f, rad->stanga);
        }
        else if (f.idFilm > rad->inf.idFilm) {
            rad->dreapta = inserare(f, rad->dreapta);
        }
        return rad;
    }
    else {
        return creareNod(NULL, NULL, f);
    }
}

void traversare_preordine(nodArb* rad) {
    if (rad) {
        printf("idFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d\n",
            rad->inf.idFilm, rad->inf.denumire, rad->inf.pret, rad->inf.nrBilete, rad->BF);
        traversare_preordine(rad->stanga);
        traversare_preordine(rad->dreapta);
    }
}

void traversare_inordine(nodArb* root) {
    if (root) {
        traversare_inordine(root->stanga);
        printf("idFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d\n",
            root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
        traversare_inordine(root->dreapta);
    }
}

void traversare_postordine(nodArb* root) {
    if (root) {
        traversare_postordine(root->stanga);
        traversare_postordine(root->dreapta);
        printf("idFilm: %d, denumire: %s, pret: %.2f, nrBilete: %.2f, BF=%d\n",
            root->inf.idFilm, root->inf.denumire, root->inf.pret, root->inf.nrBilete, root->BF);
    }
}

void dezalocare(nodArb* root) {
    if (root) {
        dezalocare(root->stanga);
        dezalocare(root->dreapta);
        free(root->inf.denumire);
        free(root);
    }
}

int main(void) {
    FILE* f = fopen("activitate2.txt", "r");
    char* token;
    char buffer[100];
    char sep[] = ",\n";

    nodArb* root = NULL;

    if (f == NULL) {
        printf("Fisierul nu a putut fi deschis.\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        filme temp;

        token = strtok(buffer, sep);
        if (token == NULL) {
            continue;
        }
        temp.idFilm = atoi(token);

        token = strtok(NULL, sep);
        if (token == NULL) {
            continue;
        }

        temp.denumire = (char*)malloc(strlen(token) + 1);
        if (temp.denumire == NULL) {
            fclose(f);
            dezalocare(root);
            return 1;
        }
        strcpy(temp.denumire, token);

        token = strtok(NULL, sep);
        if (token == NULL) {
            free(temp.denumire);
            continue;
        }
        temp.pret = (float)atof(token);

        token = strtok(NULL, sep);
        if (token == NULL) {
            free(temp.denumire);
            continue;
        }
        temp.nrBilete = (float)atof(token);

        root = inserare(temp, root);

        free(temp.denumire);
    }

    fclose(f);

    printf("\n--- INORDINE ---\n");
    traversare_inordine(root);

    printf("\n--- PREORDINE ---\n");
    traversare_preordine(root);

    printf("\n--- POSTORDINE ---\n");
    traversare_postordine(root);

    dezalocare(root);

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10


typedef struct Node {
    char key[50];
    int value;
    struct Node* next;
} Node;


Node* hashTable[SIZE];


int hashFunction(char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % SIZE;
}


void insert(char* key, int value) {
    int index = hashFunction(key);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;


    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}


void printTable() {
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        Node* current = hashTable[i];

        while (current != NULL) {
            printf("(%s, %d) -> ", current->key, current->value);
            current = current->next;
        }

        printf("NULL\n");
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    insert("ana", 10);
    insert("mere", 20);
    insert("ion", 30);
    insert("are", 40);
    insert("pere", 50);

    printTable();

    return 0;
}
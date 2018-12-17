/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include <stdio.h>


//C Implementation of Hash Table Nakov book Programing ++= algorithms

#define N 211

typedef int data;
typedef long keyType;

#define NOT_EXIST (-1)  /* Vryshta se ot get() kogato elementa lipsva*/

struct list {
    keyType key;
    data info;
    struct list* next;
};

struct list *hashTable[N];

//Vkluchva element v nachaloto na svurzan spisyk
void insertBegin(struct list** L, keyType key, data x) {
    struct list* temp;
    temp = (struct list*) malloc(sizeof(*temp));
    if(temp == NULL) {
        fprintf(stderr, "Nqma dostatuchno pamet za nov element!\n");
        return;
    }
    
    temp->next = *L;
    (*L) = temp;
    (*L)->key = key;
    (*L)->info = x;
}

//Iztriva element ot spisyka
void deleteNode(struct list** L, keyType key) {
    struct list* current = *L;
    struct list* save;
    if((*L)->key == key) {  //Trqbva da se iztrie purviq element
        current = (*L)->next;
        free(*L);
        (*L) = current;
        return;
    }
    
    //Namira elementa koito shte se trie
    while(current->next != NULL && current->next->key != key) {
        current = current->next;
    }
    if(current->next == NULL) {
        fprintf(stderr, "Greshka Elementut za iztrivane ne e nameren!\n");
        return;
    }
    else {
        save = current->next;
        current->next = current->next->next;
        free(save);
    }
}

//Tyrsi po kluch element v zvurzan spisyk
struct list* search(struct list* L, keyType key) {
    while(L != NULL) {
        if(L->key == key) {
            return L;
        }
        L = L->next;
    }
}

//Hash Functions
unsigned hashFunction(keyType key) {
    return (key % N);
}

void initHashTable(void) {
    unsigned i;
    for(i = 0; i < N; i++) {
        hashTable[i] = NULL;
    }
}

void put(keyType key, data x) {
    int place = hashFunction(key);
    insertBegin(&hashTable[place], key, x);
}

data get(keyType key) {
    int place = hashFunction(key);
    struct list* ptr = search(hashTable[place], key);
    return (ptr != NULL) ? ptr->info : NOT_EXIST;
}

void testHashTable() {
    initHashTable();
    put(1234, 100); // v slot 179
    put(1774, 120); // v slot 86
    put(86, 180);   // v slot 86 kolizia
    printf("Otpechatva dannite na elementa s kluch   86: %d \n", get(86));
    printf("Otpechatva dannite na elementa s kluch 1234: %d \n", get(1234));
    printf("Otpechatva dannite na elementa s kluch 1774: %d \n", get(1774));
    printf("Otpechatva dannite na elementa s kluch 1773: %d \n", get(1773));
}
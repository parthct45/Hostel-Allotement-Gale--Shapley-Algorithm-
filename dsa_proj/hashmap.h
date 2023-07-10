#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 100

typedef struct Node {
    int key;
    float cgpa;
    char* name;
    struct Node* next;
} Node;

typedef struct HashMap {
    Node* buckets[HASH_SIZE];
} HashMap;

int hash(int key) {
    return key % HASH_SIZE;
}

Node* createNode(int key, float cgpa,char* name) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->cgpa = cgpa;
    node->name=name;
    node->next = NULL;
    return node;
}

void insert(HashMap* map, int key, float cgpa,char* name) {
    int index = hash(key);
    Node* node = createNode(key, cgpa,name);
    if (map->buckets[index] == NULL) {
        map->buckets[index] = node;
    } else {
        Node* curr = map->buckets[index];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = node;
    }  
}

float getCgpa(HashMap* map, int key) {
    int index = hash(key);
    Node* curr = map->buckets[index];
    while (curr != NULL) {
        if (curr->key == key) {
            return curr->cgpa;
        }
        curr = curr->next;
    }
    return -1;  
}

char* getName(HashMap* map, int key){
    int index=hash(key);
    Node* curr=map->buckets[index];
    while (curr != NULL)
    {
        if (curr->key==key){
            return curr->name;
        }
        curr=curr->next;
    }
    return "Not found";
}
int getKey(HashMap* hashmap, float cgpa) {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashmap->buckets[i]->cgpa == cgpa) {
            return hashmap->buckets[i]->key;
        }
    }
    return -1;
}
//id =0
//name=1
//cgpa=2
//prefRoomate=3
//prefRoom = 4



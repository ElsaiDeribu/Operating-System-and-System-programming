#include <stdio.h>
#include <stdlib.h>

#define BUCKET_COUNT 3
#include "hashtable.h"


typedef struct Binding{
const char* key;
int value;
struct Binding* next;
}Binding;

typedef struct HashTable{
struct Binding* buckets[BUCKET_COUNT];
}HashTable;

HashTable* create(){
    HashTable* hashTable;
    hashTable = (HashTable*) malloc (sizeof(HashTable));
    size_t i;
    for(i = 0; i < BUCKET_COUNT; i++){
        (*hashTable).buckets[i] = NULL;
        };
    return hashTable;
};

unsigned int hash(const char* key){
    enum{HASH_MULT = 65599};
    size_t i;
    size_t h = 0;
    for (i = 0; key[i] != '\0'; i++)
        h = h * HASH_MULT + (size_t)key[i];
    return h % BUCKET_COUNT;
}


bool add(struct HashTable* table, const char* key, int value){

    Binding* node;
    node = (Binding*) malloc(sizeof(Binding));
    node->key = key;
    node->value = value;
    node->next = NULL;
    size_t index = hash(key);

    if (table->buckets[index] == NULL){
            table->buckets[index] = node;
    }
    else{
        Binding* current = table->buckets[index];
        Binding* next = current->next;
        if (next == NULL){
            if (current->key == node->key){
                current->value = node->value;
                return false;
            }
            else{
                current->next = node;
                return true;
            };
        }
        else{
            while(next != NULL){
                if (next -> key == node -> key){
                    next->value = node->value;
                    return false;
                }
                else if(next->next == NULL){
                next -> next = node;
                return true;
                };
        };
        }
    };

};

struct Binding* find(struct HashTable* table, const char* key){
    size_t index = hash(key);
    if (table->buckets[index] ==  NULL){
        printf("Binding with key:\"%s\" could not be found in this hashTable \n", key);
        return NULL;
    }

    Binding* current = table -> buckets[index];
    while(current != NULL && current -> key != key){
        current = current -> next;    
        };
    if (current && current -> key == key){
            return current;
    }
    else{
        printf("Binding with key: \"%s\" could not be found in this hashtable \n", key);
        return NULL;
        };
};


bool removeBinding(struct HashTable* table, const char* key){

    size_t index = hash(key);
    Binding* current = table -> buckets[index];
    Binding* prev = table -> buckets[index];
    if (current == NULL){
        return false;
    };
    if (current->key == key){
        table -> buckets[index] = current->next; 
        free(current);
        return true; 
    };

    while(current && current->key != key){
        prev = current;
        current = current->next;
    };
    if (current){
        prev->next = current->next;
        free(current);
        return true;
    };
    return false;

    };



void delete_table(struct HashTable* table){

    size_t i;
    for (i = 0; i < BUCKET_COUNT; i++){
        Binding* current = table -> buckets[i];
        Binding* next;
        if (current->next){
            next = current -> next;
        }
        else{
            next = NULL;
        };
        while(current != NULL ){
            free(current) ;
            current = next;
            if (next){
                next = next->next;
            }
    }
    };
};

void print_table(struct HashTable* table){
size_t i;
for(i = 0; i < BUCKET_COUNT; i++){
        
        if (table->buckets[i] != NULL){
            Binding* current = table->buckets[i];
            printf("hashtable[%d] ---> ", i);
            while (current){
                printf("(key = %s, value = %d) ---> ", current->key, current->value );
                current = current->next;
            }
            printf("NULL \n");
        }
        };

};



int main() 
{ 

HashTable* table = create();

add(table, "hello world", 1);
add(table,"hello elsai", 2);
add(table, "hello elsi", 3);

Binding* result = find(table, "hello world");




delete_table(table);
if (result){
printf("%s, %d \n", result->key, result->value);
}

print_table(table);

}

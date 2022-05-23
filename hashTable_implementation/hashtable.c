#include <stdio.h>
#include <stdlib.h>

#define BUCKET_COUNT 1024
#include "hashtable.h"
#include <assert.h>


/**************************************************************
 *The struct below helps in forming a binding which is a node
in a linked list. The binding will have a key, value and next 
attribute which points to the next node in the linked list
 *************************************************************/
typedef struct Binding{
const char* key;
int value;
struct Binding* next;
}Binding;



/**************************************************************
 *The struct below helps in forming a hashtable which is an array
of a given length 
 *************************************************************/
typedef struct HashTable{
struct Binding* buckets[BUCKET_COUNT];
}HashTable;



/**************************************************************
 *The function below creates a hashtable in the heap and assignes
each value of the heap to NULL  when called and returns a pointer
to the created hashtable
 *************************************************************/
HashTable* create(){
    HashTable* hashTable;
    hashTable = (HashTable*) malloc (sizeof(HashTable));
    size_t i;
    for(i = 0; i < BUCKET_COUNT; i++){
        (*hashTable).buckets[i] = NULL;
        };
    return hashTable;
};



/**************************************************************
 *The function below takes in a string as an input and then maps
that to a a number which is not greater than the length of the
hastable and then returns the maped number
 *************************************************************/
unsigned int hash(const char* key){
    enum{HASH_MULT = 65599};
    size_t i;
    size_t h = 0;
    for (i = 0; key[i] != '\0'; i++)
        h = h * HASH_MULT + (size_t)key[i];
    return h % BUCKET_COUNT;
}



/**************************************************************
 *The the following function takes in a hashtable and the key and
value of the binding to insert into the hashtable. 
It then makes a binding with the key and value given and then inserts
into the hashtable to the index which is generated using it's key and 
returns "true" if that is done successfully. 
if the key of the node to insert already exists the value of the
existing binding is changed to the new one and then "false" is returned
 *************************************************************/
bool add(struct HashTable* table, const char* key, int value){

    Binding* node;
    node = (Binding*) malloc(sizeof(Binding));
    node->key = key;
    node->value = value;
    node->next = NULL;
    size_t index = hash(key);

    if (table->buckets[index] == NULL){
            table->buckets[index] = node;
            return true;
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




/**************************************************************
 *The function below takes in a hashtable and a key as an input
and looks for a binding with the given key in the given hashtable
and returns the binding if it is found otherwise it returns NULL
 *************************************************************/
struct Binding* find(struct HashTable* table, const char* key){
    size_t index = hash(key);
    if (table->buckets[index] ==  NULL){
        // printf("Binding with key:\"%s\" could not be found in this hashTable \n", key);
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
        // printf("Binding with key: \"%s\" could not be found in this hashtable \n", key);
        return NULL;
        };
};




/**************************************************************
 *The function below takes in a hashtable and a key as an input
and looks for a binding with the given key in the given hashtable.

if the binding was found it removes it from the heap and returns 'true'
otherwise it returns 'false'.
 *************************************************************/
bool remove(struct HashTable* table, const char* key){

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





/**************************************************************
 *The function below iterates through the hashtable and removes
every binding from the hashtable and the heap.
 *************************************************************/
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



/**************************************************************
 *The following function takes in a hashtable and prints it when 
called.
 *************************************************************/
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



#include <stdio.h>
#include "hashtable.c"

int main(int argc, char const *argv[])
{
    struct HashTable* table = create();

    assert( find(table, "Test Key") == NULL);

    assert( add(table, "Test Key", 11) == true);

    assert( add(table, "Test Key", 11) == false);

    struct Binding* binding =  find(table, "Test Key");

    assert( binding != NULL &&  binding->value == 11);

    return 0;
}
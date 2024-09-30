#include "customer.h"

typedef struct Node {
    Customer *customer;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node *buckets[256];
    Customer *head;
    Customer *tail;
} HashTable;

unsigned int hash(const char *str);
void init_table(HashTable *table);
void add_customer(HashTable *table, const char *email, const char *name, int shoe_size, const char *favorite_food);
Customer *lookup_customer(HashTable *table, const char *email);
void delete_customer(HashTable *table, const char *email);
void free_table(HashTable *table);
void load_database(HashTable *table, const char *filename);
void save_database(HashTable *table, const char *filename);
void list_customers(HashTable *table);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % 256;
}

void init_table(HashTable *table) {
    for (int i = 0; i < 256; i++) {
        table->buckets[i] = NULL;
    }
    table->head = NULL;
    table->tail = NULL;
}

void add_customer(HashTable *table, const char *email, const char *name, int shoe_size, const char *favorite_food) {
    unsigned int index = hash(email);
    Node *node = table->buckets[index];
    
    while (node) {
        if (strcmp(node->customer->email, email) == 0) {
            free(node->customer->name);
            free(node->customer->favorite_food);
            node->customer->name = strdup(name);
            node->customer->shoe_size = shoe_size;
            node->customer->favorite_food = strdup(favorite_food);
            return;
        }
        node = node->next;
    }
    
    Customer *new_customer = create_customer(email, name, shoe_size, favorite_food);
    Node *new_node = malloc(sizeof(Node));
    new_node->customer = new_customer;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    
    if (table->tail) {
        table->tail->next = new_customer;
        table->tail = new_customer;
    } 
    else {
        table->head = new_customer;
        table->tail = new_customer;
    }
}

Customer *lookup_customer(HashTable *table, const char *email) {
    unsigned int index = hash(email);
    Node *node = table->buckets[index];
    while (node) {
        if (strcmp(node->customer->email, email) == 0) {
            return node->customer;
        }
        node = node->next;
    }
    return NULL;
}

void delete_customer(HashTable *table, const char *email) {
    unsigned int index = hash(email);
    Node *prev = NULL;
    Node *current = table->buckets[index];

    while (current) {
        if (strcmp(current->customer->email, email) == 0) {
            if (prev) {
                prev->next = current->next;
            } 
	    else {
                table->buckets[index] = current->next;
            }
            if (current->customer == table->head) {
                table->head = current->customer->next;
                if (current->customer == table->tail) {
                    table->tail = NULL;
                }
            } else {
                Customer *prev_customer = table->head;
                while (prev_customer && prev_customer->next != current->customer) {
                    prev_customer = prev_customer->next;
                }
                if (prev_customer) {
                    prev_customer->next = current->customer->next;
                }
                if (current->customer == table->tail) {
                    table->tail = prev_customer;
                }
            }

            free_customer(current->customer);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Customer with email %s not found.\n", email);
}

void list_customers(HashTable *table) {
    Customer *current = table->head;
    while (current) {
        printf("Email: %s, Name: %s, Shoe Size: %d, Favorite Food: %s\n",
               current->email, current->name, current->shoe_size, current->favorite_food);
        current = current->next;
    }
}

void load_database(HashTable *table, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *email = strtok(line, "\t");
        char *name = strtok(NULL, "\t");
        char *shoe_size_str = strtok(NULL, "\t");
        char *favorite_food = strtok(NULL, "\t");

        if (email && name && shoe_size_str && favorite_food) {
            int shoe_size = atoi(shoe_size_str);
            add_customer(table, email, name, shoe_size, favorite_food);
        }
    }
    fclose(file);
}

void save_database(HashTable *table, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        return;
    }
    Customer *current = table->head;
    while (current) {
        fprintf(file, "%s\t%s\t%d\t%s\n", current->email, current->name, current->shoe_size, current->favorite_food);
        current = current->next;
    }
    fclose(file);
}

void free_table(HashTable *table) {
    for (int i = 0; i < 256; i++) {
        Node *node = table->buckets[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free_customer(temp->customer);
            free(temp);
        }
    }
    table->head = NULL;
    table->tail = NULL;
}




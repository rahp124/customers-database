#include <stdlib.h>
#include <string.h>
#include "customer.h"

Customer *create_customer(const char *email, const char *name, int shoe_size, const char *favorite_food) {
    Customer *customer = malloc(sizeof(Customer));
    if (!customer) {
        return NULL;
    }
    customer->email = strdup(email);
    customer->name = strdup(name);
    customer->shoe_size = shoe_size;
    customer->favorite_food = strdup(favorite_food);
    customer->next = NULL;
    return customer;
}

void free_customer(Customer *customer) {
    if (customer) {
        free(customer->email);
        free(customer->name);
        free(customer->favorite_food);
        free(customer);
    }
}


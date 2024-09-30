#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main() {
	HashTable table;
	init_table(&table);
	load_database(&table, "customers.tsv");

	char command[256];
	while (1) {
    	printf("Enter command: ");
    	scanf("%s", command);

    	if (strcmp(command, "add") == 0) {
        	char email[256], name[256], food[256], shoe_size_str[256];
        	int shoe_size;
        	char *endptr;
        	printf("Enter email: ");
        	scanf("%s", email);
        	printf("Enter name: ");
        	scanf("%s", name);
    		while (1) {
       		 printf("Enter shoe size: ");
       		 scanf("%s", shoe_size_str);
   	 	 shoe_size = strtol(shoe_size_str, &endptr, 10);
   	 	 if(*endptr == '\0' && endptr != shoe_size_str){
   		  break;
   		 }
   	 	 else{
   		  printf("Invalid shoe size\n");
   	 	 }
       	       }
               printf("Enter favorite food: ");
               scanf("%s", food);
               add_customer(&table, email, name, shoe_size, food);
    	} 
	else if (strcmp(command, "lookup") == 0) {
        	char email[256];
        	printf("Enter email: ");
        	scanf("%s", email);
        	Customer *customer = lookup_customer(&table, email);
        	if (customer) {
            	printf("Email: %s, Name: %s, Shoe Size: %d, Favorite Food: %s\n",
                   	customer->email, customer->name, customer->shoe_size,
                   	customer->favorite_food);
        	} 
		else {
            		printf("Customer not found!\n");
        	}
    	} 
	else if (strcmp(command, "delete") == 0) {
        	char email[256];
        	printf("Enter email: ");
        	scanf("%s", email);
        	delete_customer(&table, email);
    	} 
	else if (strcmp(command, "list") == 0) {
        	list_customers(&table);
    	} 
	else if (strcmp(command, "save") == 0) {
        	save_database(&table, "customers.tsv");
    	} 
	else if (strcmp(command, "quit") == 0) {
        	break;
    	} 
	else {
        	printf("Unknown command!\n");
    	}
	}

	free_table(&table);
	return 0;
}


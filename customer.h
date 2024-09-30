typedef struct Customer {
    char *email;
    char *name;
    int shoe_size;
    char *favorite_food;
    struct Customer *next;
} Customer;

Customer *create_customer(const char *email, const char *name, int shoe_size, const char *favorite_food);
void free_customer(Customer *customer);

We start by creating a Customer struct to store the customer’s details. We also want to create a Linked List structure to create linked list nodes. We also want an array of linked lists to handle collisions as the hash table. We need to create a hash function to hash input string. We also need a load database function to load from customers.tsv. We use this data to add a customer using the Customer struct. We also need a function save database to write to customers.tsv using the hashtable. For hash table operations, we need the add customer function. Using the input data, we create a new node. We also need a function to peak at a specific customer, maybe by email. We also need a delete function, also by email. We can also add at the end a function that prints all of the functions. As for the full program loop, first we load the database, then we start the loop. We prompt the user for input, and verify and read that input. If the input is valid, we do what the user says. Else we prompt them again. We break out of the loop when the user chooses to quit.


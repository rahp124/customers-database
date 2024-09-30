CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: businessdb

businessdb: businessdb.o customer.o hashtable.o
	$(CC) businessdb.o customer.o hashtable.o -o businessdb

businessdb.o: businessdb.c hashtable.h customer.h
	$(CC) $(CFLAGS) -c businessdb.c 

customer.o: customer.c customer.h
	$(CC) $(CFLAGS) -c customer.c 

hashtable.o: hashtable.c hashtable.h customer.h
	$(CC) $(CFLAGS) -c hashtable.c 

clean:
	rm -f businessdb
	rm -f businessdb.o customer.o hashtable.o

format:
	clang-format -i -style=file *.[ch]


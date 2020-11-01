# paths
LIB = ../../lib
INCLUDE = ../../include
MODULES = ../../modules/UsingLinkedList

# compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall -Werror -g -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS =list_insert_steps.o $(MODULES)/ADTList.o 

# Το εκτελέσιμο πρόγραμμα
EXEC = list_insert_steps

# Παράμετροι για δοκιμαστική εκτέλεση
ARGS = real

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)


clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

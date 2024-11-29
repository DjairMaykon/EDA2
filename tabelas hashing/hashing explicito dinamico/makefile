# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LIB_NAME = libhashing.a
OBJ = hashing.o
MAIN = main

# Regras
all: $(MAIN)

# Compilar o main com a biblioteca
$(MAIN): $(MAIN).o $(LIB_NAME)
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).o $(LIB_NAME)

# Compilar a biblioteca estática
$(LIB_NAME): $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)

# Compilar hashing.c
$(OBJ): hashing.c hashing.h
	$(CC) $(CFLAGS) -c hashing.c

# Compilar main.c
$(MAIN).o: main.c hashing.h
	$(CC) $(CFLAGS) -c main.c

# Limpar arquivos gerados
clean:
	rm -f *.o $(LIB_NAME) $(MAIN)

# Forçar a recompilação completa
rebuild: clean all

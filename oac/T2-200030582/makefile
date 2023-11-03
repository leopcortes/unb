NOME_SAIDA=./sim_riscv

CC=g++
EXT=cpp
CFLAGS = -g -Wall -I./include

SRC = ./src/memoria.cpp ./src/riscv.cpp
INCLUDE = ./include/globals.h ./include/memoria.h
OBJ = $(SRC:./src/%.cpp=./src/obj/%.o)

$(NOME_SAIDA): $(OBJ)
	$(CC) -o $@ $^

./src/obj/%.o: ./src/%.cpp $(INCLUDE)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) $(NOME_SAIDA)

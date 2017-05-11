# MAKEFILE

all: servidor cliente
# O compilador faz a ligação entre os dois objetos
servidor: servidor.c
	gcc -o servidor servidor.c

cliente: cliente.c
	gcc -o cliente cliente.c -lncurses

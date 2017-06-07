# MAKEFILE

all: servidor cliente
# O compilador faz a ligação entre os dois objetos

servidor: servidor.c ../comunicacao.c ../comunicacao.h
	gcc -o servidor servidor.c ../comunicacao.c

cliente: cliente.c ../comunicacao.c ../comunicacao.h
	gcc -o cliente cliente.c ../comunicacao.c

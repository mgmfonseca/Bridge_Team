#ifndef COMUNICACAO_H
#define COMUNICACAO_H

int estabelecer_ligacao_servidor(char * endereco_ip);
void escrever_texto(int socket, char * texto);
char * ler_texto(int socket);

#endif
#include "../comunicacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Cliente(int clienteSockfd)
{
  /*Buffer de dados máximo a ser mandado para o servidor*/
    char buffer_para_servidor[256];

    do {
        //read(clienteSockfd,buffer_para_servidor, sizeof (buffer_para_servidor));
        printf("Para efetuar um cálculo escreva no formato 'numerooperaçãonumero'\n");
        printf("ex: 4+4\n");
        printf("Quando desejar terminar escreva 'END':\n");
        scanf("%s",buffer_para_servidor);
        fflush(stdin);
        system("clear");

        /*Envia para o servidor*/
        //ssize_t write(int fd, const void *buf, size_t count);
        //write(clienteSockfd, buffer_para_servidor, sizeof (buffer_para_servidor));
        escrever_texto(clienteSockfd,buffer_para_servidor);

    /*Mensagem para sair com a palavra END*/
    } while (strcmp(buffer_para_servidor, "END") != 0);
    /**Encerra o descritor*/
    //close(clienteSockfd);
    exit(1);
} 

int main()
{   
    /*Define o descritor cliente*/
    int descritorCliente;
    descritorCliente = estabelecer_ligacao_servidor("127.0.0.1");
    /*chama funcao do cliente passando o descritor*/
    Cliente(descritorCliente);    
}

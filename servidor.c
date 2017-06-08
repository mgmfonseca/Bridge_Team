#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <unistd.h>//read write
#include "comunicacao.h"
#include "cpu.h"
 
void* Servidor(void* arg)
{
    /*Buffer de entrada (armazena buffer do cliente)*/
    char * buffer_do_cliente;
    /*Cast do ponteiro*/
    int sockEntrada = *(int *) arg;

    char f_instrucao[256];
    int resultado;

    /*Loop "infinito"*/
    printf("Cliente ligado: \n");
    while(1)
    {
        /*Le o que vem do cliente*/
        buffer_do_cliente=ler_texto(sockEntrada);
        if (strcmp(buffer_do_cliente, "end") != 0)
        {
            printf("%s %d \n",buffer_do_cliente, strlen(buffer_do_cliente));
            printf("Cliente %d enviou: %s\n", sockEntrada, buffer_do_cliente);
             
            if (validar(buffer_do_cliente)>0)
            {
                resultado=calcular(buffer_do_cliente);
                sprintf(f_instrucao,"%s=%d",buffer_do_cliente,resultado);
                printf("%s",f_instrucao);
                escrever_texto(sockEntrada,f_instrucao);  
            }
            else 
            printf("Erro na introdução da instrução");
            		
            free(buffer_do_cliente);
        }
        else
        {
            /*Encerra o descritor*/
            //fechar_ligacao(sockEntrada);
            /*Encerra a thread*/
            //pthread_exit((void*) 0);
            printf("ligacoa fechad acom o cliente %d \n", sockEntrada);
            return(0);
        }
    }
}
 
int main()
{
    system("clear");
    //Declaracao da estrutura
    struct sockaddr_in serverAddr;
    //Retorna da funcao e o descritor
    int sockfd = configuracaoServidor();
 
    //Loop infinito
    while (1)
    {
        int clienteSockfd;
        struct sockaddr_in clienteAddr;
        //tamanho da estrutura
        unsigned int clntLen;
        clntLen = sizeof (clienteAddr);
        //declara uma thread
        pthread_t thread;
        //Fica a aguardar a conexao do cliente
        if ((clienteSockfd = accept(sockfd, (struct sockaddr *) & clienteAddr, &clntLen)) < 0)
        {
            printf("Erro no Socket\n");
            return (0);
        }
        //Inicializa a thread
        if (pthread_create(&thread, NULL, Servidor, &clienteSockfd) != 0)
        {
            printf("Erro na Thread\n");
            return (0);
        }
 
        pthread_detach(thread);
    }
    return(0);
}
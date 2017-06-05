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
 
void* Servidor(void* arg)
{
    /*Buffer de entrada (armazena buffer do cliente)*/
    char * buffer_do_cliente;
    /*Cast do ponteiro*/
    int sockEntrada = *(int *) arg;
    /*Loop "infinito"*/
    printf("Mensagem recebida: \n");
    for (;;)
    {
        /*Le o que vem do cliente*/
        buffer_do_cliente=ler_texto(sockEntrada);
        if (strcmp(buffer_do_cliente, "end") != 0)
        {
            /*Se buffer == END termina o programa*/
            printf("%s\n",buffer_do_cliente);
            free(buffer_do_cliente);
        }
        else
        {
            /*Encerra o descritor*/
            close(sockEntrada);
            /*Encerra a thread*/
            pthread_exit((void*) 0);
        }
    }
}
 
int configuracaoServidor()
{
    //nome do socket fornecido por argumento
    int sockfd;
    //Declaracao da estrutura do socket
    struct sockaddr_in serverAddr;
    //Cria o socket para comunicação de streams
    if ((sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      printf("Erro no Socket\n");
      exit(1);
    }
    //limpa a estrutura
    memset(&serverAddr, 0, sizeof (serverAddr));
    //adress family
    serverAddr.sin_family = AF_INET;
    //The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
    //(A constante INADDR_ANY e todos os ips ou qualquer ip) htonl -> conversao
    // bind your socket to localhost only - INADDR_ANY
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //Define a porta
    serverAddr.sin_port = htons(6881);
    //bind - Relaciona o socket com o endereco (nome)
    if (bind(sockfd, (struct sockaddr *) & serverAddr, sizeof (serverAddr)) < 0)
    {
      printf("Erro no Socket\n");
      exit(1);
     }
    //canal de que vai ser utilizado para receber os pedidos de comunicação
    //backlog - numero máximo da lista de esperade pedidos de conexões pendentes
    if (listen(sockfd, 5) < 0)
    {
      printf("Erro no Socket\n");
      exit(1);
    }
    return sockfd;
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
      exit(1);
    }
        //Inicializa a thread
        if (pthread_create(&thread, NULL, Servidor, &clienteSockfd) != 0)
       {
            printf("Erro na Thread\n");
            exit(1);
       }
 
        pthread_detach(thread);
    }
    exit(0);
}
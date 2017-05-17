
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>//SOCK_STREAM
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>//read write

 
int configuracaoCliente()
{
    /*Declaração do cliente*/
    int clienteSockfd;
    /*Estrutura do Cliente*/
    struct sockaddr_in serv_addr;
    /*Tamanho da estrutura*/
    socklen_t addrlen = sizeof (serv_addr);
 
    /*Socket que define familia TCP*/
    /*apenas pode ser usado na forma de comunicação SOCK_STREAM
    e no espaço de nomes da internet
    permite definir um canal de comunicação com
    as caracteristicas de um socket*/
    //PF_INET - indica o espaço de nomes IPv4 e os seus protocolos associados
    //int socket(int domain, int type, int protocol);
    clienteSockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clienteSockfd < 0)
    {
        printf("Erro no Socket\n");
        exit(1);
    }
    /*Limpa a estrutura*/
    bzero((char *) & serv_addr, sizeof (serv_addr));
    /*Direcciona a familia*/
    serv_addr.sin_family = AF_INET;
    /*Define o IP neste caso o localhost*/
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*Define a porta de conexao*/
    serv_addr.sin_port = htons(6881);


   /*Faz a conexão com o servidor*/
  
   if(connect(clienteSockfd,(struct sockaddr *)&serv_addr, addrlen) < 0)
     {
            printf("Erro no Socket\n");
        exit(1);
    }
        return clienteSockfd;
}
 
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
        write(clienteSockfd, buffer_para_servidor, sizeof (buffer_para_servidor));
      /*Mensagem para sair com a palavra END*/
    } while (strcmp(buffer_para_servidor, "END") != 0);
    /**Encerra o descritor*/
    //close(clienteSockfd);
    exit(1);
}
 
int main()
{
    system("clear");
    /*Estrutura cliente*/
    struct sockaddr_in serv_addr;
    /*Tamanho da estrutura*/
    socklen_t addrlen = sizeof (serv_addr);
    /*Define o descritor cliente*/
    int descritorCliente;
    descritorCliente = configuracaoCliente();
    /*chama funcao do cliente passando o descritor*/
    Cliente(descritorCliente);

    exit(0);
}

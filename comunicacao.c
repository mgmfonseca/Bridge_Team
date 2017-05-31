#include <stdlib.h>
#include <string.h>
#include <unistd.h>//read write

#include <sys/types.h>
#include <sys/socket.h>//SOCK_STREAM
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <ctype.h>



 
int estabelecer_ligacao_servidor(char * endereco_ip)
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
        return -1;
    }

    /*Limpa a estrutura*/
    bzero((char *) & serv_addr, sizeof (serv_addr));
    /*Direcciona a familia*/
    serv_addr.sin_family = AF_INET;
    /*Define o IP neste caso o localhost*/
    serv_addr.sin_addr.s_addr = inet_addr(endereco_ip);
    /*Define a porta de conexao*/
    serv_addr.sin_port = htons(6881);


   /*Faz a conexão com o servidor*/
  
   if(connect(clienteSockfd,(struct sockaddr *)&serv_addr, addrlen) < 0)
    {
        return -2;
    }
    return clienteSockfd;
}
 

void escrever_texto(int socket, char * texto)
{
    
    //define tamanho do texto +1 pelo terminos do texto \0
    int tamanho=strlen(texto)+1;
    //enviamos tamanho e depois texto
    write(socket, &tamanho, sizeof(int));
    write(socket, texto, sizeof(char) * tamanho);

}

char * ler_texto(int socket)
{
    int tamanho;
    char * texto;
 
    read(socket, &tamanho, sizeof(int));
    texto=(char*)malloc(tamanho);
    read(socket, texto, sizeof(char)*tamanho);
   
    return texto;

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
      return -3;
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
      return -4;
     }
    //canal de que vai ser utilizado para receber os pedidos de comunicação
    //backlog - numero máximo da lista de esperade pedidos de conexões pendentes
    if (listen(sockfd, 5) < 0)
    {
      return -5;
    }
    return sockfd;
}
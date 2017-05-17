//ficheiro: socket_cliente.c
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>


//funcao para escrever no socket (interpretado como um ficheiro)
void escrever_socket(int socketfd, const char* mensagem){
    //tamanho da mensagem contando o caracter final '\0'
    int tamanho = strlen(mensagem) + 1; 
   
    //escrever o numero de bytes da mensagem, incluindo o '\0'
    write(socketfd, &tamanho, sizeof(tamanho));
    
    //escrever a mensagem 
    write(socketfd, mensagem, tamanho);
}

//o cliente vai receber por argumento o nome do socket e a mensagem 
int main(int argc, char *argv[]){
    int socketfd;
    //primeiro argumento e o nome do socket
    const char* const nome_socket = argv[1];
    const char* const mensagem = argv[2]; //segundo argumento e a mensagem
    int socket_fd; //descritor do socket
    struct sockaddr_un nome;//estrutura para o socket do unix

    //criar o socket
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

    //estabelecer o nome para o servidor
    nome.sun_family = AF_LOCAL;
    strcpy(nome.sun_path, nome_socket);

    /* estabelecer o endereco (nome) a ligacao ao socket 
       o cliente faz o pedido de ligacao ao socket servidor */
    connect(socket_fd, (struct sockaddr*) &nome, SUN_LEN(&nome));
    
    //escrever a mensagem no socket
    escrever_socket(socketfd, mensagem);
    close(socketfd); //fechar o descritor do socket
    
    return 0;
}

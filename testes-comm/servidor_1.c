
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>//read write

/* funcao para ler no socket (interpretado como um ficheiro)
   enquanto a mensagem do cliente nao for "END" ou vazia, o servidor vai 
   ler o que esta escrito no socket */
int ler_socket(int cliente_socket){
    while(1){
        int tamanho;//variavel que guarda o tamanho da mensagem
        /* se a leitura for vazia fechamos a ligacao, ou seja, retornamos 
           ao main com valor 0 */
        if(read(cliente_socket, &tamanho, sizeof(tamanho)) == 0)
            return 0;
            
        //reservar espaco em memoria para guardar a mensagem
        char *mensagem = (char*) malloc(tamanho);
        
        //ler a mensagem e escreve-la no stdout
        read(cliente_socket, mensagem, tamanho); 
        printf("servidor: a receber mensagem... %s\n", mensagem);
        
        //testa se o cliente pretende terminar a ligacao com a palavra 'END'
        if(!strcmp(mensagem,"END")){
            //liberta o espaco de memoria reservado para a mensagem
            free(mensagem);
            return 1;//retorna ao menu principal
        }
        free(mensagem);
    }
}

int main(int argc, char *argv[]){
    //nome do socket fornecido por argumento
    const char* const nome_socket = argv[1]; 
    int socket_fd; //descritor do socket
    struct sockaddr_un nome; //estrutura para o socket unix
    
    //declarar variavel que guarda o valor retornado pela funcao ler_socket
    int mensagem_end_cliente; 

    //criar um socket local para comunicacao de streams
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    
    /* definir este processo como sendo o servidor,
       preencher a estrutura para o socket */
    nome.sun_family = AF_LOCAL;
    strcpy(nome.sun_path, nome_socket);
    
    //bind - vincular o socket com o endereco (nome)
    bind(socket_fd, (struct sockaddr*) &nome, SUN_LEN(&nome));

    //canal de que vai ser utilizado para receber os pedidos de comunicação
    //backlog - numero máximo da lista de esperade pedidos de conexões pendentes
    listen(socket_fd, 5);
    
    /*enquanto o cliente nao enviar a mensagem 'END', 
      aceita as ligacoes e recebe mensagens */
    do{
        //estrutura para o socket unix do cliente
        struct sockaddr_un nome_cliente; 
        socklen_t cliente_nome_len; //tamanho do nome do socket do cliente
        int cliente_socket_fd; //descritor do cliente
        
        //aceitar a ligacao e retorna um descritor para o socket cliente
        /*o servidor extrai a primeira conexão da lista de pedidos pendentes
        do socketfd de escuta, cria um novo socket para a conexão e retorna um descritor para
        este socket*/
        //int accept(int sock_fd), struct sockaddr *addr, socklen_t *addrlen);
        cliente_socket_fd = accept(socket_fd, (struct sockaddr *) &nome_cliente, &cliente_nome_len);
        
        /* tratar da comunicacao entre o cliente e o servidor
          servidor vai ler o que o cliente escreveu no socket */
        mensagem_end_cliente = ler_socket(cliente_socket_fd);
        
        //fechar a ligacao - fechar o socket do cliente
        close(cliente_socket_fd);
    } while (!mensagem_end_cliente);
    //termina quando o cliente envia a mensagem 'END'

    //remover o descritor do socket - fechar o socket e desvincular o nome
    close(socket_fd);
    unlink(nome_socket);
    return 0;
}

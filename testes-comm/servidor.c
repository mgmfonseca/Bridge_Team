
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
#include "../comunicacao.h"

 
int validar(char* strg_texto)
{    
    char oper;
    int p_num, s_num, num_conver;
 
    num_conver=sscanf(strg_texto,"%d%c%d", &p_num,&oper,&s_num);

    /* se a conversão da string correspondeu a 3 valores (int/char/int), então
    confirma se o operador (char) é valido */
    if(num_conver==3) 
    {
        switch(oper)
        {
            case '+':        
                return 1;
            case '-':
                return 1;
            case '/':
                return 1;            
            case '*':
            case 'x':
            case 'X':            
                return 1;            
            default:                
                return -1;
        }
    }
    else //se um dos valores errado
    {
        return -2;
    } 
}


//Modulo de calculo da instrução

int calcular(char* instrucao)
{
    int p_num, s_num, resultado;
    char oper;

    sscanf(instrucao,"%d%c%d",&p_num,&oper,&s_num);
    
    switch(oper)
    {
        case '+':
            resultado=p_num + s_num;
            break;
        case '-':
            resultado=p_num - s_num;
            break;
        case '/':
            resultado=p_num / s_num;
            break;            
        case '*':
        case 'x':
        case 'X':
            resultado=p_num * s_num;            
            break;            
        default:                
            return 0;
    }
    
    return resultado;
}


void* Servidor(void* arg)
{
    //Buffer de entrada (armazena buffer do cliente)
    char * buffer_do_cliente;
    //Cast do ponteiro
    int sockEntrada = *(int *) arg;
    //Loop "infinito"
     printf("Mensagem recebida na socket %d: \n",sockEntrada);
    while(1)
    {
           
        //Le o que vem do cliente
         buffer_do_cliente=ler_texto(sockEntrada);

        if (strcmp(buffer_do_cliente, "end") != 0)
        {
            printf("%s\n",buffer_do_cliente);

            char f_instrucao[256];
            int result;

            if (validar(buffer_do_cliente)>0)
            {
                result=calcular(buffer_do_cliente);
                sprintf(f_instrucao,"%s=%d",buffer_do_cliente,result);
                printf("%s\n",f_instrucao);
                		
                escrever_texto( sockEntrada, f_instrucao);
            }
            else {
             escrever_texto( sockEntrada, "Erro na introdução da instrução\n");
             printf("Erro na introdução da instrução\n");
            }

            
            free(buffer_do_cliente);
        }
        else
        {
            //Encerra o descritor
            close(sockEntrada);
            //Encerra a thread
            pthread_exit((void*) 0);
        }
    }
}

 
int configuracaoServidor();
 
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
        }else{
             printf("cliente ligado na socket %d\n", clienteSockfd);
        }
        //Inicializa a thread
        if (pthread_create(&thread, NULL, Servidor, &clienteSockfd) != 0)
        {
            printf("Erro na Thread\n");
            exit(1);
        }else{
             printf("Inicia cliente na socket %d", clienteSockfd);
        }
        pthread_detach(thread);
    }
    exit(0);
}




    
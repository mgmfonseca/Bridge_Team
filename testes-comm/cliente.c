#include "../comunicacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Buffer de dados máximo a ser mandado para o servidor*/
char buffer_para_servidor[256];


void Cliente(int clienteSockfd)
{
  
    
    do {
        //read(clienteSockfd,buffer_para_servidor, sizeof (buffer_para_servidor));
        printf("Para efetuar um cálculo escreva no formato 'numerooperaçãonumero'\n");
        printf("ex: 4+4\n");
        printf("Quando desejar terminar escreva 'end':\n");
        scanf("%s",buffer_para_servidor);
        fflush(stdin);
        system("clear");

        //Envia para o servidor
        //ssize_t write(int fd, const void *buf, size_t count);
        //write(clienteSockfd, buffer_para_servidor, sizeof (buffer_para_servidor));
        escrever_texto(clienteSockfd,buffer_para_servidor);

    //Mensagem para sair com a palavra END
    } while (strcmp(buffer_para_servidor, "end") != 0);
    //Encerra o descritor
    //close(clienteSockfd);
    exit(1);
} 


int main()
{    
	    
    while ((strcmp(buffer_para_servidor, "end") != 0))
    {
        system("clear");
        printf("Digite 'start' para começar, se desejar sair digite 'end'");
        scanf("%s",buffer_para_servidor);
        fflush(stdin);
		if (strcmp(buffer_para_servidor, "start") == 0)
		{
			int descritorCliente;
			descritorCliente = estabelecer_ligacao_servidor("127.0.0.1");
			Cliente(descritorCliente); 
		}
    }
    if (strcmp(buffer_para_servidor, "end") == 0)
	{
		exit(1);
	}
      
}

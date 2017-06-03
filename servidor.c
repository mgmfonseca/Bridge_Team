#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<comunicacao.h>


#define MAX_TENTATIVAS = 10;
/* função ja criada em comunicação função escrever_texto */

/*void escreverSocket( int sock, const char* mensagem )
{
	int tamanho = strlen(mensagem) + 1; 
	
	write( sock, &tamanho, sizeof(tamanho) );
	write( sock, mensagem, tamanho);
}*/



/* funcao criada em comunicaçao com o nome de ler_texto() */

/*int lerSocket( int sock )
{
	int tamanho;
	char buffer[256];
	
	while(1)
	{
		if( read( sock, &tamanho, sizeof( tamanho ) ) == 0 )
			return 0;

		//char* mensagem = (char*) malloc(tamanho);
		read( sock, &buffer, tamanho );
	
		printf("Cliente %d enviou: %s\n", sock, buffer );
		//escreverSocket( sock, "obrigado");
        escrever_texto( sock, "obrigado");
	}
	
	return 1;
}*/

int comunica( int sock )
{
	
   ler_texto( sock );
    //lerSocket( sock );	
	//escreverSocket( sock, "obrigado");	
	return 0;
}


int main( int argc, char* argv[] )
{
	int socket_fd;
	struct sockaddr_un nome;	
	
	unlink( "nome-socket" );	
	
	socket_fd = socket( PF_LOCAL, SOCK_STREAM, 0 );
	
	nome.sun_family = AF_LOCAL;
	strcpy( nome.sun_path, "nome-socket");
	
	bind( socket_fd, (struct sockaddr*) &nome, SUN_LEN( &nome ));
	
	listen( socket_fd, 5);
	
	
	do
	{
		struct sockaddr_un nome_cliente;
		socklen_t cliente_nome_len;
		int cliente_socket_fd;
		
		cliente_socket_fd = accept( socket_fd, 
								(struct sockaddr*) &nome_cliente,
								&cliente_nome_len);
		
		printf("Ligou-se alguém no socket %d\n", cliente_socket_fd );
		comunica( cliente_socket_fd);
		
	
	}while(1);
	
	close( socket_fd );
	unlink( "nome-socket" );

	return 0;
}
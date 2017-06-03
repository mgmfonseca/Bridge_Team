#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include<comunicacao.h>

char buffer_para_servidor[256];


/* Inicio do modulo de cliente*/
// Desenhar linha horizontal
void fazer_linha(){
    int row,col,cont=0;
    getmaxyx(stdscr,row,col);
    do{    
        printw("_ ");
        cont++;
    }while (cont < col/2);
}

// Experiencia com o teclado (para apagar)
void ler_teclado(){
    char teclado[12];
    int i=0;
    printw("Digite o valor a calcular:");
    getstr(teclado);
    printw("voce escreveu %s",teclado);
    
    getch();    
    do{    
       printw("%c", teclado[i]);      
       i++;
    }while(i < 5);
}

void consola_c()
{
    int row,col;				/* to store the number of rows and the number of colums of the screen */
    initscr();				/* start the curses mode */
    start_color();			/* Start color */
    getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 
    mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
    mvprintw(2,4,"ECRAN PRINCIPAL");
    
    // Altera a cor do estado de ligação com o servidor
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, 2, 0);
    init_pair(3, 7, 0);
    attron(COLOR_PAIR(1));//colocar a vermelho a palavra 
    mvprintw(2,col-12,"Desconectado");
    attron(COLOR_PAIR(3));//volta á cor original branco letra e preto fundo
 
    mvprintw(4,2,"Programa Cliente");
    mvprintw(6,2,"Escreva 'START' para ligar ao servidor");
    mvprintw(7,2,"Quando desejar terminar escreva 'END'\n");

    fazer_linha();
   // ler_teclado();
 
    refresh();
    //getch();
    endwin();
    
    //return 0;
}

void Cliente(int clienteSockfd)
{
  
    
    do {
        scanf("%s",buffer_para_servidor);
        fflush(stdin);
        system("clear");
        /*Envia para o servidor*/        
        escrever_texto(clienteSockfd,buffer_para_servidor);
    /*Mensagem para sair com a palavra END*/
    } while (strcmp(buffer_para_servidor, "end") != 0);
    /**Encerra o descritor*/
    //close(clienteSockfd);
    exit(1);
}

int main()
{    
    consola_c();

    while ((strcmp(buffer_para_servidor, "end") != 0))
    {
        system("clear");
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

    return 0;
}

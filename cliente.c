#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include"comunicacao.h"

/* Inicio do modulo de cliente*/
struct reg_teclado buffer_servidor;

struct reg_teclado
{
    char instrucao[256];
};

struct reg_teclado teclado()
{
    struct reg_teclado resultado;

    mvscanw(9,2,"%s",resultado.instrucao);
    return(resultado);
}

// Desenhar linha horizontal
void fazer_linha(){
    int row,col,cont=0;
    getmaxyx(stdscr,row,col);
    do{    
        printw("_ ");
        cont++;
    }while (cont < col/2);
}

int output_ligado(int ligado)
{
    int col, row;
    getmaxyx(stdscr,row,col);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, 2, 0);
    init_pair(3, 7, 0);    
    
    if(ligado==1)
    {
        attron(COLOR_PAIR(2));//colocar a vermelho a palavra 
        mvprintw(2,col-12,"Conectado");
        attroff(COLOR_PAIR(2));
    }
    else
    {
        attron(COLOR_PAIR(1));//colocar a vermelho a palavra 
        mvprintw(2,col-12,"Desconectado");
        attroff(COLOR_PAIR(1));
    }
}

void consola_c()
{
    int row,col;			    /* to store the number of rows and the number of colums of the screen */
    initscr();				    /* start the curses mode */
    start_color();			    /* Start color */
    getmaxyx(stdscr,row,col);	/* get the number of rows and columns */
    mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
    mvprintw(2,4,"ECRAN PRINCIPAL");
    
    // Altera a cor do estado de ligação com o servidor
    output_ligado(0);
  
    mvprintw(4,2,"Programa Cliente");
    mvprintw(6,2,"Escreva 'START' para ligar ao servidor");
    mvprintw(7,2,"Quando desejar terminar escreva 'END'\n");    

    fazer_linha();
    
    refresh();   
    endwin();    
}

void Cliente(int clienteSockfd)
{    
   //struct reg_teclado buffer_servidor;//para apagar
    do {
        fflush(stdin);
        //system("clear");
        //Envia para o servidor   
        buffer_servidor=teclado();     
        escrever_texto(clienteSockfd, buffer_servidor.instrucao);
    //Mensagem para sair com a palavra END
    } while (strcmp(buffer_servidor.instrucao, "end") != 0);
    //Encerra o descritor
    //close(clienteSockfd);   
    //exit(1);
}

void Comunicar_servidor()
{
    //struct reg_teclado buffer_servidor;//para apagar
    while ((strcmp(buffer_servidor.instrucao, "end") != 0))
        {
            //system("clear");
            //scanf("%s",buffer_servidor);
            buffer_servidor=teclado();
            fflush(stdin);
            if (strcmp(buffer_servidor.instrucao, "start") == 0)
            {
                int descritorCliente;
                descritorCliente = estabelecer_ligacao_servidor("127.0.0.1");                
                if(descritorCliente > 0)
                {
                    int lig=1;
                    output_ligado(lig);
                }
                Cliente(descritorCliente);                
            }
        }

   /* if (strcmp(buffer_servidor.instrucao, "end") == 0)
    {
        exit(1);
    }*/
}

int main()
{    
    struct reg_teclado valor;
    consola_c();
    Comunicar_servidor();
    //valor=teclado();    
    mvprintw(10,3,"digitaste: %s",valor.instrucao);//para eliminar
    refresh();
    return 0;
}



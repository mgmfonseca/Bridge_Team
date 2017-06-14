#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include"comunicacao.h"

/* Inicio do modulo de cliente*/
struct reg_teclado buffer_servidor;

struct reg_teclado
{
    char instrucao[256];
};

// Desenhar linha horizontal
void fazer_linha(char* conteudo){
    int row,col,cont=0;
    getmaxyx(stdscr,row,col);
    do{    
        printw("%s",conteudo);
        cont++;
    }while (cont < col/(strlen(conteudo)));
}

struct reg_teclado teclado()
{
    struct reg_teclado resultado;

    mvscanw(9,2,"%s",resultado.instrucao);
    move(9,0);
    fazer_linha(" ");
    return(resultado);
    
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
        mvprintw(2,col-12,"Conectado   ");
        attroff(COLOR_PAIR(2));
    }
    else
    {
        attron(COLOR_PAIR(1));//colocar a vermelho a palavra 
        mvprintw(2,col-12,"Desconectado");
        attroff(COLOR_PAIR(1));
    }
}

void Cliente(int clienteSockfd)
{    
   char*teste_resultado;//

    do {
        fflush(stdin);
        //Envia para o servidor   
        buffer_servidor=teclado();     
        escrever_texto(clienteSockfd, buffer_servidor.instrucao);
        move(10,0);
        fazer_linha(" ");
        teste_resultado=ler_texto(clienteSockfd);   //    
        if(strcmp(teste_resultado,"ERRO")==0)
        {
            mvprintw(10,2,"ERRO na introducao da string");
        }
        else
        {
        mvprintw(10,2,"O resultado de %s",teste_resultado);
        }
        // mvprintw(10,2,"O resultado de %s",ler_texto(clienteSockfd));

        //Mensagem para sair com a palavra END
        } while (strcmp(buffer_servidor.instrucao, "end") != 0);
    //Encerra o descritor
    fechar_ligacao(clienteSockfd);   
}

void Comunicar_servidor()
{
    while ((strcmp(buffer_servidor.instrucao, "end") != 0))
    {
            buffer_servidor=teclado();
            fflush(stdin);
            if (strcmp(buffer_servidor.instrucao, "start") == 0)
            {
                int descritorCliente;
                descritorCliente = estabelecer_ligacao_servidor("127.0.0.1");                
                if(descritorCliente > 0)
                    output_ligado(1);
                
                Cliente(descritorCliente); 
                buffer_servidor.instrucao[0]='\0';               
                output_ligado(0);
            }
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

    fazer_linha("_ ");
    
    refresh();
    Comunicar_servidor();  
    endwin();    
}

int main()
{    
    struct reg_teclado valor;
    consola_c();
    
    return 0;
}



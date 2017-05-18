#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/* Inicio do modulo de cliente*/

void fazer_linha(){
    int row,col,cont=0;
    getmaxyx(stdscr,row,col);
    do{    
        printw("_ ");
        cont++;
    }while (cont < col/2);
}

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


int main(){
    /* printf("TESTE - Modulo de Cliente - COMPILADO"); */

 char mesg[]="Just a string";		/* message to be appeared on the screen */
 int row,col;				/* to store the number of rows and the number of colums of the screen */

 initscr();				/* start the curses mode */
 getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                                	/* print the message at the center of the screen */
 mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
 mvprintw(2,4,"ECRAN PRINCIPAL");
 mvprintw(2,col-12,"Conectado");
 mvprintw(4,2,"Programa Cliente");
 mvprintw(6,2,"Escreva 'START' para ligar ao servidor");
 mvprintw(7,2,"Quando desejar terminar escreva 'END'\n");

fazer_linha();
ler_teclado();
 
refresh();
getch();
endwin();

    
    return 0;
}



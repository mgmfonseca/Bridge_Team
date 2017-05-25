#include<stdio.h>
#include<string.h>


int main()
{
    char strg_texto[50];
    char operador;
    int prim_num, sec_num, numero_conversoes;

    printf ("Digite o valor a calcular:");
    scanf("%s",strg_texto);

    numero_conversoes=sscanf(strg_texto,"%d%c%d", &prim_num,&operador,&sec_num);
    if(numero_conversoes==3)
    {
        switch(operador){
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
            
            default
                return 0;
        }
    }
    else
    {
        return 0;
    }
    printf("Primeiro numero %d\n",prim_num);
    printf("Operador %c\n",operador);
    printf("Segundo numero %d\n",sec_num);
  
    
    return 0;
    
}
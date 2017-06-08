#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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

//Modulo de conversão



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

/*int main()
{
    char expressao[256];
    char f_instrucao[256];
    int result;

    printf("Escreva a expressão a calcular:");
    scanf("%s",expressao);

    if (validar(expressao)>0)
    {
        result=calcular(expressao);
        sprintf(f_instrucao,"%s=%d",expressao,result);
        printf("%s",f_instrucao);
  
    }
    else 
    printf("Erro na introdução da instrução");

    return 0;
}*/



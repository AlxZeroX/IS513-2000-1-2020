/**************************************************************
 * Integrantes
 *  Fredy Enrique Amador Quiroz
 *  Christian Alexander Ochoa
 *  David Alexander Cardenas
 *  Ariel Garcia
 **************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Lista.h"
/*======================================================*
 *=        Se deifnen las salidas del Automata         =*
 *======================================================*/
#define IDENTIFICADOR 2
#define CADENA 1
#define NUMERO 3
#define NADA 0
/*======================================================*/


/*======================================================*
 *=        Se deifnen los estados del Automata         =*
 *======================================================*/
enum estado {ESTADO_NINGUNO,ESTADO_CADENA,ESTADO_NUMERO,ESTADO_IDENTIFICADOR};
typedef enum estado Estado;
Estado estado_actual = ESTADO_NINGUNO;
/*======================================================*/

typedef struct elementoToken
{
    char *atributo;
    int tipo_token;
    unsigned numero_linea;
}Token;

void automata(FILE *fichero,Lista *lista_tokens);
bool comprobarCaracter(char caracter);
bool comprobarNumero(char numero);
char* obtenerAtributo(Lista *lista); 
void  presentacion(Lista *lista_tokens);
char* tipoToken(Token *token);

int main(int argc, const char* argv[]){
    
    FILE *fichero;
    fichero = fopen("programa.robodoc", "r");
    Lista *lista_tokens = (Lista *)malloc(sizeof(Lista));
    inicializarLista(lista_tokens,VOID);
    automata(fichero,lista_tokens);
    presentacion(lista_tokens);
    return 0;
}

void automata(FILE *fichero,Lista *lista_tokens){
    char caracter;
    estado_actual = ESTADO_NINGUNO;
    unsigned contador_lineas = 1;
    Lista *buffer = (Lista*)malloc(sizeof(Lista));
    inicializarLista(buffer,INT);
    
    while ((caracter = fgetc(fichero))!=EOF)
    {   
        if(caracter=='\n')
            contador_lineas++;
        switch (estado_actual)
        {
        case ESTADO_NINGUNO:
            if((caracter == ' ') || (caracter == '\t') || (caracter == '\n') ){
                estado_actual = ESTADO_NINGUNO;
            }
            else{
                if(comprobarCaracter(caracter)){
                    estado_actual=ESTADO_CADENA;
                    insertarUltimo(buffer,&caracter);
                }else{
                    if(comprobarNumero(caracter)){
                        estado_actual=ESTADO_NUMERO;
                        insertarUltimo(buffer,&caracter);
                    }
                }
            }
            break;
        case ESTADO_CADENA:
            if((caracter == ' ') || (caracter == '\t') || (caracter == '\n') ){
                Token *token = (Token *)malloc(sizeof(Token));
                token->atributo = obtenerAtributo(buffer);
                token->tipo_token = IDENTIFICADOR;
                token->numero_linea = contador_lineas;
                insertarUltimo(lista_tokens,token);
                estado_actual = ESTADO_NINGUNO;
                vaciarLista(buffer);
            }else
            {
                if(comprobarCaracter(caracter)){
                    insertarUltimo(buffer,&caracter);
                    estado_actual = ESTADO_CADENA;
                }else
                {
                    if(comprobarNumero(caracter)){
                        insertarUltimo(buffer,&caracter);
                        estado_actual=ESTADO_IDENTIFICADOR;
                    }
                }
                
            }
            
            break;

        case ESTADO_IDENTIFICADOR:
            if((caracter == ' ') || (caracter == '\t') || (caracter == '\n') ){
                Token *token = (Token *)malloc(sizeof(Token));
                token->atributo = obtenerAtributo(buffer);
                token->tipo_token = IDENTIFICADOR;
                token->numero_linea = contador_lineas;
                insertarUltimo(lista_tokens,token);
                estado_actual = ESTADO_NINGUNO;
                vaciarLista(buffer);
            }else
            {
                if(comprobarCaracter(caracter)){
                    insertarUltimo(buffer,&caracter);
                    estado_actual= ESTADO_IDENTIFICADOR;
                }else
                {
                    if(comprobarNumero(caracter)){
                        insertarUltimo(buffer,&caracter);
                        estado_actual = ESTADO_IDENTIFICADOR;
                    }
                }
                
            }        
            break;
        case ESTADO_NUMERO:
            if((caracter == ' ') || (caracter == '\t') || (caracter == '\n') ){
                Token *token = (Token *)malloc(sizeof(Token));
                token->atributo = obtenerAtributo(buffer);
                token->tipo_token = NUMERO;
                token->numero_linea = contador_lineas;
                insertarUltimo(lista_tokens,token);
                estado_actual = ESTADO_NINGUNO;
                vaciarLista(buffer);
            }else
            {
                if(comprobarCaracter(caracter)){
                    insertarUltimo(buffer,&caracter);
                    estado_actual = ESTADO_IDENTIFICADOR;
                }else
                {
                    if(comprobarNumero(caracter)){
                        insertarUltimo(buffer,&caracter);
                        estado_actual = ESTADO_NUMERO;
                    }
                }
                
            }            
            break;                
        default:
            printf("ERROR\n");
            break;
        }
    }
    fclose(fichero);
}

bool comprobarCaracter(char caracter){
    if( ((int)caracter >=65) && ((int)caracter <=90))
        return true;
    else
    {
        if(((int)caracter >=97) && ((int)caracter <=122))
            return true;
        else
            return false;        
    }   
}

bool comprobarNumero(char numero){
    if(((int)numero >= 48) && ((int)numero<=57))
        return true;
    else
        return false;
        
}

char* obtenerAtributo(Lista *lista){
    char *atributo = (char *)calloc(lista->tamano+1,sizeof(char));
    for(unsigned indice = 0; indice<=(lista->tamano); indice++){
        if(indice != lista->tamano){
            char caracter = (char)(obtenerPorIndice(lista,indice)).Int;        
            *(atributo+indice)= caracter;
        }else
        {
            *(atributo+indice)='\0';
        }
        
    }
    return atributo;
}

void  presentacion(Lista *lista_tokens){
    printf("=========================================\n");
    printf("=      Analizador Lexico De ROBODOC     =\n");
    printf("=========================================\n\n");

    printf("Se obtuvieron los siguientes tokens \n\n");
    for(unsigned i = 0; i<(lista_tokens->tamano); i++){
        Token *token = (Token *)(obtenerPorIndice(lista_tokens,i).Void);
        printf("Linea %d : %s_<%s> \n\n",token->numero_linea, token->atributo,tipoToken(token));
    }
}

char* tipoToken(Token *token){
  switch (token->tipo_token)
  {
  case CADENA:
    return "cadena";
    break;
  case NUMERO:
    return "numero";
    break;
  case IDENTIFICADOR:
    return "identificador";
    break;
  default:
      break;
  }
        
}
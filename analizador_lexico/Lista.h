#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>


enum tipos{INT, FLOAT, DOUBLE, CHAR, STRING, VOID}; //enumeraciones que simularan los tipos de datos ofrecidos por el lenguaje
typedef enum tipos Tipo;                           // se define un alias para los enum

/*===================================================================================================*
 *                                    Definiendo TAD Nodos                                           *
 *===================================================================================================*/
typedef struct ElementoNodo
{
    struct ElementoNodo *enlace;
    union{                                         //se utilizara para almacenar los distitos tipos de datos
        int Int;
        float Float;
        double Double;
        char  *String;
        void *Void;
    };
} Nodo;


/*===================================================================================================*
 *                                    Definiendo TAD Lista                                           *
 *===================================================================================================*/
typedef struct ElementoLista{
    Nodo *primerNodo;
    Nodo *ultimoNodo;
    unsigned tamano;
    Tipo tipoDato;
}Lista;




/*===================================================================================================*
 *                                           Operaciones                                             *
 *===================================================================================================*/

void inicializarLista(Lista *lista, Tipo tipo){
    lista->primerNodo = NULL;
    lista->ultimoNodo = NULL;
    lista->tamano = 0;
    lista->tipoDato = tipo;
}

unsigned int tamanoLista(Lista *lista){
    return lista->tamano;
}

bool vacia(Lista *lista){
    if((lista->primerNodo == NULL) && (lista->ultimoNodo == NULL))
        return true;
    else
        return false;

}

bool insertarPorIndice(Lista *lista, void * dato, unsigned indice ){
   bool exito = false;
   if((indice>=0) && ((indice < lista->tamano) || indice == 0)){
        Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));             //declaracion del nuevo nodo
        if(nuevo == NULL)                                       //retorna un false si no se puede asginar memoria
            return false;
        nuevo->enlace = NULL;
        Tipo tipo = lista->tipoDato;
        switch(tipo){
            case INT :;  //al parecer no se puede declarar una variable despues de un case,primera declaracion vacia por esta razon
                int valorInt = *((int *)dato);
                nuevo->Int = valorInt;
                break;
            case FLOAT :;
                float valorFloat = *((float *)dato);
                nuevo->Float = valorFloat;
                break;
            case DOUBLE :;
                double valorDouble = *((double*)dato);
                nuevo->Double = valorDouble;
                break;
            case CHAR:;
                char *valorPtrChar = ((char*)dato);
                nuevo->String = valorPtrChar;
                break;
            case VOID :;
                nuevo->Void = dato;
        }
        if(vacia(lista)){
            lista->primerNodo = nuevo;
            lista->ultimoNodo = nuevo;
            lista->tamano = 1;
            exito = true;
        }else{
            if(indice == 0){
                nuevo->enlace = lista->primerNodo;
                lista->primerNodo = nuevo;  // se inserto en la primera posicion
                lista->tamano++;
                exito = true;
            }else{
                if(indice == (lista->tamano-1)){ // si el el elemento que se quiere instertar es el ultimo
                    Nodo *auxiliar  = lista->ultimoNodo;
                    auxiliar->enlace = nuevo;       // se inserto en la ultima posicion
                    nuevo->enlace = NULL;
                    lista->ultimoNodo = nuevo;
                    exito = true;
                    lista->tamano++;
                }else{
                    Nodo *auxiliar = lista->primerNodo;
                    for(unsigned i = 0; i<indice; i++){
                        if(i == (indice - 1)){
                            nuevo->enlace = auxiliar->enlace;
                            auxiliar->enlace = nuevo;    // se agrega el nuevo nodo en la posicion deseada
                            lista->tamano++;
                            return true;
                        }
                        auxiliar = auxiliar->enlace;
                    }
                }
            }
        }

   }
    return exito;
}
//Esta Funcion inserta al inicio de la lista
bool insertar(Lista *lista, void *dato){
    if(insertarPorIndice(lista, dato, 0))
        return true;
    else
        return false;
}

bool insertarUltimo(Lista* lista, void* dato){
    int indice = (lista->tamano -1);
    if(indice == -1)                                            //corrige si la lista cuenta con 0 elementos
        indice = 0;
    if((indice == 0 )&& (lista->tamano)== 1){                   //Si la lista tiene un solo elemento y se necesita agregar al ultimo
        Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));             //declaracion del nuevo nodo
        if(nuevo == NULL)                                       //retorna un false si no se puede asginar memoria
            return false;
        nuevo->enlace = NULL;
        Tipo tipo = lista->tipoDato;
        switch(tipo){
            case INT :;  //al parecer no se puede declarar una variable despues de un case,primera declaracion vacia por esta razon
                int valorInt = *((int *)dato);
                nuevo->Int = valorInt;
                break;
            case FLOAT :;
                float valorFloat = *((float *)dato);
                nuevo->Float = valorFloat;
                break;
            case DOUBLE :;
                double valorDouble = *((double*)dato);
                nuevo->Double = valorDouble;
                break;
            case CHAR:;
                char *valorPtrChar = ((char*)dato);
                nuevo->String = valorPtrChar;
                break;
            case VOID :;
                nuevo->Void = dato;
         }
            Nodo *auxiliar = lista->primerNodo;
            auxiliar->enlace = nuevo;
            lista->ultimoNodo = nuevo;
            lista->tamano++;
            return true;
    }else{                                                      //si la lista tiene 2 o mas elementos
        if(insertarPorIndice(lista, dato,indice))
            return true;
        else
            return false;
    }

}

bool eliminarPorIndice(Lista *lista, unsigned indice){
    if(indice >=0 && indice< (lista->tamano)){
        if(vacia(lista)){        //si la lista esta vacia
            return false;
        }else{
            if(indice == 0){  // ingresa a esta seccion si el elemento que se quiere eliminar es el primero
                Nodo *auxiliar = lista->primerNodo;
                Nodo *auxEliminar = lista->primerNodo;
                auxiliar = auxiliar->enlace;
                lista->primerNodo = auxiliar;
                free(auxEliminar);
                lista->tamano--;
                return true;
            }else{
                if(indice == lista->tamano -1){ // si el elemento que se quiere eliminar es el ultimo
                    Nodo *auxiliar = lista->primerNodo;
                    for(unsigned i = 0; i<(lista->tamano - 1); i++){
                        if(i == (lista->tamano-2)){
                            Nodo *auxEliminar = lista->ultimoNodo;
                            lista->ultimoNodo = auxiliar;
                            free(auxEliminar);
                            lista->tamano--;
                            return true;
                        }
                        auxiliar = auxiliar->enlace;
                    }
                }else{      //ingresa si es un elemento intermedio
                    Nodo *auxiliar = lista->primerNodo;
                    Nodo *anterior = auxiliar;
                    for(unsigned i = 0 ; i<lista->tamano-1;i++){
                        auxiliar = auxiliar->enlace;
                        if(indice == i){
                            anterior->enlace = auxiliar->enlace;
                            auxiliar->enlace=NULL;
                            free(auxiliar);
                            lista->tamano--;
                            return true;
                        }
                        anterior = auxiliar;
                    }
                }
            }
        }
    }else{
        return false;
    }
}

bool eliminarUltimo(Lista *lista){
    if(eliminarPorIndice(lista, (lista->tamano -1)))
        return true;
    else
        return false;

}
bool eliminarPrimero(Lista* lista){
    if(eliminarPorIndice(lista, 0))
        return true;
    else
        return false;
}
void vaciarLista(Lista *lista){
    if(!vacia(lista)){
        /*=====inicializacion====*/
        Nodo *auxiliar = lista->primerNodo;
        Nodo *anterior = auxiliar;
        /*=======================*/

        while(auxiliar != NULL){
            auxiliar = auxiliar->enlace;
            anterior->enlace = NULL;
            //probable problema de fuga de memoria
            free(anterior);
            lista->tamano--;
            anterior = auxiliar;
        }
        lista->primerNodo = NULL;
        lista->ultimoNodo = NULL;
        lista->tamano = 0;
    }

}


Nodo obtenerPorIndice(Lista *lista, unsigned indice){
    if((indice>=0) && ((indice < lista->tamano) || indice == 0)){
        if(!vacia(lista)){
            if(indice == 0){
                Nodo nodoRetorno = *(lista->primerNodo);
                nodoRetorno.enlace=NULL;
                return nodoRetorno;
            }else{
                if(indice == (lista->tamano-1)){
                    Nodo nodoRetorno = *(lista->ultimoNodo);
                    nodoRetorno.enlace = NULL;
                    return nodoRetorno;
                }else{
                    Nodo *nodoActual = lista->primerNodo;
                    for(unsigned i = 0; i<(lista->tamano); i++){
                        if(indice == i){
                            Nodo nodoRetorno = *(nodoActual);
                            nodoRetorno.enlace = NULL;
                            return nodoRetorno;
                        }
                        nodoActual = nodoActual->enlace;
                    }
                }
            }
        }


    }
}

Nodo obtenerPrimero(Lista* lista){             //devuelve el primero elemento de la lista
    return obtenerPorIndice(lista, 0);
}

Nodo obtenerUltimo(Lista* lista){
    if(!vacia(lista)){
        return obtenerPorIndice(lista,(lista->tamano-1));
    }else{
        Nodo nodo;
        return nodo;
    }
}
Tipo tipoDeLista(Lista *lista){
    return lista->tipoDato;
}

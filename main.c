#include<stdio.h>
#include<string.h>

int main(){
char cadena[100];
int indice,l,contador=0,leyoletras=0;
printf("\ningrese una frase  :");
gets(cadena);
l= strlen(cadena);

for(indice=0;indice<l;indice++)
{
 if(cadena[indice]==' ')
 {
  if(leyoletras==1)
   if(cadena [indice+1]!=' ')
    contador=contador+1;
         }
   else
    leyoletras=1;
   }
  
if(cadena[indice-1]!=' '){
 contador=contador+1;
}
printf("\nel numero de palabras de la frase es: %d",contador);
 
 
 return 0;
}

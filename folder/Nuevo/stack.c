#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct persona{
    int id;
    char *nombre;
    struct persona *siguiente;
};
typedef struct persona Nodo;
Nodo *cabeza = NULL;
Nodo *actual = NULL;
char* getStr();
void clearBuffer();
int getId();
void push();
void pop();
void CrearRaiz();
void ContarNodos();
void ImprimirLista();
int main(){
    return menu();
}
void push(){
    Nodo *nodo = (struct persona*)malloc(sizeof(struct persona));
    if(NULL == nodo){
        printf("\n Error en creacion de nodo \n");
    }
    nodo->id = getId();
    clearBuffer();
    nodo->nombre=getStr();
    nodo->siguiente = cabeza;
    cabeza = nodo;
}
void pop(){
    if(NULL == cabeza){
            printf("La pila esta vacia \n");
    }else{
        printf("\n -------Elemento Top Removido------- \n");
        Nodo *nodo = cabeza;
        printf("\n ID: %d ",nodo->id);
        printf("Nombre: %s \n", nodo->nombre);
        cabeza=nodo->siguiente;
        free(nodo);
    }
}
void ImprimirLista(void){
    if(NULL == cabeza){
        printf("La pila esta vacia \n");
    }else{
        Nodo *nodo = cabeza;
        printf("\n -------Inicio de la Pila------- \n");
        while(nodo != NULL)
        {
            printf("\n ID: %d ",nodo->id);
            printf("Nombre: %s \n", nodo->nombre);
            nodo = nodo->siguiente;
        }
        printf("\n -------Final de la Pila------- \n");
    }
}
void ContarNodos(void){
    Nodo *nodo = cabeza;
    int i=0;
    while(nodo != NULL){
        i++;
        nodo = nodo->siguiente;
    }
    printf("\n Cantidad de nodos: %d\n", i);
    return;
}
int getId() {
  int num;
  printf("\n Ingrese el ID: ");
  scanf("%d" , &num);
  return num;
}
char* getStr() {
  char d,*newAr;
  int i = 0;
  newAr = (char*) malloc(sizeof(char)*100);
  printf("\n Ingrese el nombre: ");
  while((d = getchar()) != EOF && d != '\n') {
    newAr[i++] = d;
  }
  return newAr;
}
void clearBuffer() {
  while(getchar() != '\n')
    ;
}
int menu() {
  char c;
  do {
    printf("\n~~ MENU: pila! ~~");
    printf("\nHaga una seleccion:");
    printf("\n 1. push()");
    printf("\n 2. pop()");
    printf("\n 3. ImprimirLista()");
    printf("\n 4. ContarNodos()");
    printf("\n q: salir.\n");
    c = getchar();
    switch(c) {
      case '1':
          clearBuffer();
          push();
        break;
      case '2':
          clearBuffer();
          pop();
        break;
      case '3':
          clearBuffer();
          ImprimirLista();
        break;
      case '4':
          clearBuffer();
          ContarNodos();
        break;
      default:
        break;
    }
  } while(c != 'q' && c != EOF);
}
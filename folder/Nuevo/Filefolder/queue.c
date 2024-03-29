#include <stdio.h>
#include <stdlib.h>
char* getPtrNom();
int getId();
int isEmpty();
int menu();
void clearBuffer();
void dequeue();
void enqueue();
void isEmptyWrap();
struct persona {
  int id;
  char *nombre;
  struct persona *siguiente;
};
typedef struct persona Nodo;
Nodo *final;
Nodo *inicio;
main() {
  final = inicio = 0;
  return menu();
}
int menu() {
  char c;
  do {
    printf("\n~~ MENU: cola! ~~");
    printf("\nHaga una seleccion:");
    printf("\n 1. enqueue()");
    printf("\n 2. dequeue()");
    printf("\n 3. isEmpty()");
    printf("\n q: salir.\n");
    c = getchar();
    switch(c) {
      case '1':
        enqueue();
        break;
      case '2':
        dequeue();
        break;
      case '3':
        isEmptyWrap();
        break;
      default:
        break;
    }
  } while(c != 'q' && c != EOF);
  return 1;
}
// metodo wrapper para el menu
void isEmptyWrap() {
  clearBuffer();
  if (isEmpty()) {
    printf("sirilo piscuilo.\n");
  } else {
    printf("nel pastel.\n");
  }
}
int getId() {
  int num;
  printf("Ingrese el ID: ");
  scanf("%d" , &num);
  return num;
}
// retorna un nuevo puntero a un arreglo
char* getPtrNom() {
  char d,*newAr;
  int i = 0;
  newAr = (char*) malloc(sizeof(char)*100);
  printf("Ingrese el nombre: ");
  while((d = getchar()) != EOF && d != '\n') {
    newAr[i++] = d;
  }
  return newAr;
}
// imprime el primer valor ingresado
// el penultimo valor es el nuevo inicio
// el primer valor es borrado de la lista
void dequeue() {
  Nodo *actual,
       *temporal;
  //printf("\tdequeue()\n");
  //printf("nfin: %p\nini: %p\n", final, inicio);
  clearBuffer();
  if (isEmpty()) {
    printf("Y metiamos algo en la cola...");
  } else {
    if (final == inicio) { // si solo hay 1 nodo
      //printf("1nodo\t\tnfin: %p\nini: %p\n", final, inicio);
      printf("%d | %s\n", final->id, final->nombre);
      //free(final); // liberamos la memoria que uso el nodo
      //free(inicio); // liberamos la memoria que uso el nodo
      final = inicio = 0; // dejamos los punteros en null
    } else { // si hay mas de 1 nodo
      //printf("1+nodo\t\tnfin: %p\nini: %p\n", final, inicio);
      actual = final;
      while (actual != inicio) { // recorra la cola y quede en el penultimo
        temporal = actual; // temporal guarda la direccion del penultimo
        actual = temporal->siguiente;
      }
      printf("%d | %s\n", inicio->id, inicio->nombre); // imprimimos el ultimo nodo
      //free(inicio); // liberamos la memoria usada por el ultimo nodo
      inicio = temporal; // el penultimo es ahora el ultimo
    }
  }
}
// agrega un nodo nuevo al final de la cola
void enqueue() {
  Nodo *nodoNuevo,
       *temporal;
  nodoNuevo = (Nodo*) malloc(sizeof(Nodo));
  clearBuffer();
  nodoNuevo->nombre = getPtrNom();
  nodoNuevo->id = getId();
  //printf("\n\tenqueue()\n");
  if (isEmpty()) { // si la cola esta vacia
    final = nodoNuevo; // el nodo toma el primer
    inicio = nodoNuevo; // y el ultimo lugar
  } else { // si hay al menos 1 nodo
    temporal = final; // almacenamos el ultimo nodo agregado
    final = nodoNuevo; // el nodoNuevo toma el primer lugar
    final->siguiente = temporal; // apuntando al nodo que estaba en primer lugar
  }
  //printf("nvo: %p\nfin: %p\nini: %p\n", nodoNuevo, final, inicio);
  clearBuffer();
}
int isEmpty() {
  if (!final) {
    return 1;
  } else {
    return 0;
  }
}
// cuando se manejan menus que tienen breaklines, se ocupa limpiar el buffer
// antes de empezar a leer caracteres
void clearBuffer() {
  while(getchar() != '\n')
    ;
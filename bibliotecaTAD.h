#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char tString[50];

typedef struct {
    tString titulo;
    tString autor;
    int ISBN;
    int copias;
} tLibro;

typedef struct nodo {
    tLibro libro;
    struct nodo *siguiente;
} tListaLibros;

tListaLibros * lista;
FILE * archivoBiblioteca;

//Prototipado
void inicializarLista();
bool listaVacia(tListaLibros *);
tLibro crearLibro();
void crearPrimerNodo(tLibro);
void insertarLibroAdelante(tLibro);
void insertarEnPosicionDeterminada(tLibro, int);
void eliminarEnPosicionDeterminada(int);
void mostrarLista();
void almacenarListaEnArchivoBinario();
void mostrarLibrosAlmacenadosEnArchivoBinario();
void inicializacion(tLibro);
void procesoCorte(tLibro);
void finalizacion();

//Definicion de funciones
void inicializarLista(){
  lista = NULL;
}

bool esListaVacia(tListaLibros *pLista){
  return pLista == NULL;
}

tLibro crearLibro(){
  tLibro libro;

  printf("Ingrese los datos del libro:\n");
  printf("Titulo del libro: \n");
  fflush(stdin);
  scanf("%[^\n]s", &libro.titulo);
  printf("Autor del libro: \n");
  fflush(stdin);
  scanf("%[^\n]s", &libro.autor);
  printf("Codigo ISBN: \n");
  scanf("%d", &libro.ISBN);
  printf("Copias del libro: \n");
  scanf("%d", &libro.copias);

  return libro;
}

void crearPrimerLibro(tLibro pLibro){
  tListaLibros * nuevoNodo;
  nuevoNodo = (tListaLibros*) malloc(sizeof(tListaLibros));

  nuevoNodo->libro = pLibro;
  nuevoNodo->siguiente = NULL;

  lista = nuevoNodo;

  printf("Primer libro creado!\n");
}

void insertarLibroAdelante(tLibro pLibro){
  tListaLibros * nuevoNodo;
  nuevoNodo = (tListaLibros*) malloc(sizeof(tListaLibros));

  nuevoNodo->libro = pLibro;
  nuevoNodo->siguiente = lista;

  lista = nuevoNodo;

  printf("Libro agregado!\n");
}

void insertarEnPosicionDeterminada(tLibro pLibro, int k){ //4 //posicion 3
  tListaLibros * nuevoNodo, * aux;
  //int i;
  aux = lista;

  for(int i = 1; k - 1; i++){
    aux = aux->siguiente;
  }

  nuevoNodo = (tListaLibros*) malloc(sizeof(tListaLibros));
  nuevoNodo->libro = pLibro;
  nuevoNodo->siguiente = aux->siguiente;
  aux->siguiente = nuevoNodo;

  lista = aux;

  printf("Libro agregado en posición %d!\n", k);
}

void eliminarEnPosicionDeterminada(int k){
  tListaLibros * nodoASuprimir, * anterior;
  int i;

  if(k == 1){
    nodoASuprimir = lista;
    lista = lista->siguiente;

    free(nodoASuprimir);
    nodoASuprimir = NULL;

    printf("Primer producto eliminado!\n");
  }

  nodoASuprimir = lista;
  anterior = NULL;

  for(i = 1; i < k - 1; i++){
    anterior = nodoASuprimir;
    nodoASuprimir = nodoASuprimir->siguiente;
  }

  anterior->siguiente = nodoASuprimir->siguiente;

  free(nodoASuprimir);
  nodoASuprimir = NULL;

  lista = anterior;

  printf("Producto eliminado en posición %d!\n", k);
}

void buscarPorISBN(int ISBN){
  tListaLibros * aux;
  aux = lista;

  while(aux!= NULL){
    if(aux->libro.ISBN == ISBN){
      printf("\n------------------------\n");
      printf("Titulo: %s\n", aux->libro.titulo);
      printf("Autor: %s\n", aux->libro.autor);
      printf("Codigo ISBN: %d\n", aux->libro.ISBN);
      printf("Copias: %d\n", aux->libro.copias);
      printf("\n------------------------\n");
      return;
    }
    aux = aux->siguiente;
  }

  printf("Libro no encontrado!\n"); 
}

void buscarPorTitulo(tString titulo){
  tListaLibros * aux;
  aux = lista;

  while(aux!= NULL){
    if(strcmp(aux->libro.titulo, titulo) == 0){
      printf("\n------------------------\n");
      printf("Titulo: %s\n", aux->libro.titulo);
      printf("Autor: %s\n", aux->libro.autor);
      printf("Codigo ISBN: %d\n", aux->libro.ISBN);
      printf("Copias: %d\n", aux->libro.copias);
      printf("\n------------------------\n");
      return;
    }
    aux = aux->siguiente;
  }

  printf("Libro no encontrado!\n");
}

void mostrarLista(){
  tListaLibros * aux;
  aux = lista;

  if(aux == NULL){
    printf("La lista está vacía!\n");
    return;
  }

  while(aux != NULL){
    printf("\n--------------------------\n");
    printf("Titulo: %s\n", aux->libro.titulo);
    printf("Autor: %s\n", aux->libro.autor);
    printf("Codigo ISBN: %d\n", aux->libro.ISBN);
    printf("Copias: %d\n", aux->libro.copias);
    printf("\n--------------------------\n");

    aux = aux->siguiente;
  }
}

void almacenarListaEnArchivoBinario(){
  tListaLibros * aux;
  aux = lista;
  tLibro regLibro;

  archivoBiblioteca = fopen("biblioteca.dat", "wb");

  while(aux!= NULL){
      strcpy(regLibro.titulo, aux->libro.titulo);
      strcpy(regLibro.autor, aux->libro.autor);
      regLibro.ISBN = aux->libro.ISBN;
      regLibro.copias = aux->libro.copias;

    fwrite(&regLibro, sizeof(tLibro), 1, archivoBiblioteca);

    aux = aux->siguiente;
  };

  fclose(archivoBiblioteca);

  printf("Listado almacenado en archivo!\n");
}

void mostrarLibrosAlmacenadosEnArchivoBinario(){
  tLibro libro;

  inicializacion(libro);
  procesoCorte(libro);
  finalizacion();
}

void inicializacion(tLibro pLibro){

  archivoBiblioteca = fopen("biblioteca.dat", "rb");

  if(archivoBiblioteca == NULL){
    printf("Error al abrir el archivo!\n");
    exit(EXIT_FAILURE);
  }
}

void procesoCorte(tLibro pLibro){
  fread(&pLibro, sizeof(tLibro), 1, archivoBiblioteca);

  while(!feof(archivoBiblioteca)){
    printf("\n------------------------\n");
    printf("Titulo: %s\n", pLibro.titulo);
    printf("Autor: %s\n", pLibro.autor);
    printf("Codigo ISBN: %d\n", pLibro.ISBN);
    printf("Copias: %d\n", pLibro.copias);
    printf("\n------------------------\n");

    fread(&pLibro, sizeof(tLibro), 1, archivoBiblioteca);
  }
}

void finalizacion(){
  fclose(archivoBiblioteca);
}
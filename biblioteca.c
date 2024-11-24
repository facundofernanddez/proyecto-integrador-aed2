#include "bibliotecaTAD.h"

void menuBiblioteca();

int main() {
  inicializarLista();
  menuBiblioteca();

  return 0;
}

void menuBiblioteca() {
  int opcion;

  do {
    printf("\n--- Menu Biblioteca ---\n");
    printf("1. Ingresar libro\n");
    printf("2. Mostrar libros\n");
    printf("3. Buscar por ISBN\n");
    printf("4. Buscar por titulo\n");
    printf("5. Almacenar lista en un archivo\n");
    printf("6. Mostrar lista almacenada en archivo\n");

    printf("7. Salir\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);

    switch (opcion) {
      case 1:
        if(esListaVacia(lista)){
          crearPrimerLibro(crearLibro());
        }else{
         insertarLibroAdelante(crearLibro());
        }
        break;
      case 2:
        mostrarLista();
        break;
      case 3:
        printf("Ingrese codigo ISBN a buscar\n");
        int ISBN;
        scanf("%d", &ISBN);
        buscarPorISBN(ISBN);
        break;
      case 4:
        printf("Ingrese el titulo del libro a buscar\n");
        tString titulo;
        fflush(stdin);
        scanf("%[^\n]s", &titulo);
        buscarPorTitulo(titulo);
        break;
      case 5:
        almacenarListaEnArchivoBinario();
        break;
      case 6:
        mostrarLibrosAlmacenadosEnArchivoBinario();
        break;
      case 7:
      break;
      default:
        printf("Opcion invalida.\n");
    }
  } while (opcion != 7);
}

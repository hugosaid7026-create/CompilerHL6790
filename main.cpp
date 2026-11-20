#include "Compilador.hpp"
#include <iostream>

int main(int cantidadArgumentos, char *argumentos[]) {
  if (cantidadArgumentos != 2) {
    std::cerr << "Uso: " << argumentos[0] << " archivo.hugo\n";
    return 1;
  }
  Compilador compilador;
  return compilador.compilarArchivo(argumentos[1]) ? 0 : 1;
}

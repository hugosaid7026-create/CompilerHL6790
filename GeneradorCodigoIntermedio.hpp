#pragma once

#include "Instruccion.hpp"
#include <string>
#include <vector>

class GeneradorCodigoIntermedio {
public:
  std::string nuevoTemporal();
  std::string nuevaEtiqueta();
  void emitir(const std::string &op, const std::string &arg1 = "", const std::string &arg2 = "",
              const std::string &resultado = "");
  std::vector<Instruccion> extraerDesde(std::size_t indice);
  const std::vector<Instruccion> &obtenerInstrucciones() const;

private:
  int contadorTemporales = 0;
  int contadorEtiquetas = 0;
  std::vector<Instruccion> instrucciones;
};

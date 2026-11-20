#pragma once

#include "Simbolo.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class TablaSimbolos {
public:
  TablaSimbolos();
  void entrarAmbito();
  void salirAmbito();
  bool declarar(const Simbolo &simbolo);
  const Simbolo *buscar(const std::string &nombre) const;
  bool existeEnAmbitoActual(const std::string &nombre) const;
  int ambitoActual() const;
  const std::vector<Simbolo> &obtenerSimbolos() const;

private:
  std::vector<std::unordered_map<std::string, Simbolo>> ambitos;
  std::vector<Simbolo> simbolos;
};

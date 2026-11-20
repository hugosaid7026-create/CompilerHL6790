#pragma once

#include <string>
#include <vector>

struct ErrorCompilador {
  std::string mensaje;
  int linea;
  int columna;
};

class AnalizadorSemantico {
public:
  void agregarError(const std::string &mensaje, int linea, int columna);
  std::string tipoOperacion(const std::string &operador, const std::string &izquierdo,
                            const std::string &derecho, int linea, int columna);
  bool asignacionCompatible(const std::string &destino, const std::string &origen) const;
  const std::vector<ErrorCompilador> &obtenerErrores() const;

private:
  std::vector<ErrorCompilador> errores;
};

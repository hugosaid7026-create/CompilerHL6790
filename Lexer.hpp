#pragma once

#include "Token.hpp"
#include <string>
#include <vector>

class AnalizadorLexico {
public:
    explicit AnalizadorLexico(const std::string& fuente);
    std::vector<Token> analizar();
    const std::vector<std::string>& obtenerErrores() const;
private:
    char actual() const;
    char siguiente() const;
    char avanzar();
    void ignorarEspaciosYComentarios();
    void agregar(TipoToken tipo, const std::string& lexema, int linea, int columna);
    std::string fuente;
    std::size_t posicion = 0;
    int linea = 1;
    int columna = 1;
    std::vector<Token> tokens;
    std::vector<std::string> errores;
};

#pragma once

#include "AnalizadorSemantico.hpp"
#include "GeneradorCodigoIntermedio.hpp"
#include "TablaSimbolos.hpp"
#include "Token.hpp"
#include <string>
#include <vector>

class Compilador {
public:
    bool compilarArchivo(const std::string& ruta);
private:
    void imprimirTokens(const std::vector<Token>& tokens) const;
    void imprimirTabla(const TablaSimbolos& tabla) const;
    void imprimirCodigo(const std::vector<Instruccion>& instrucciones) const;
};

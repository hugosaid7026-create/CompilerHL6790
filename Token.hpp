#pragma once

#include <string>

enum class TipoToken {
    FinArchivo, Identificador, LiteralEntero, LiteralFlotante, LiteralCadena,
    Verdadero, Falso, TipoInt, TipoFloat, TipoBool, TipoString,
    Si, Sino, Mientras, Para, Retornar, Imprimir,
    ParentesisIzquierdo, ParentesisDerecho, LlaveIzquierda, LlaveDerecha,
    PuntoComa, Coma, Asignacion, Mas, Menos, Multiplicacion, Division, Modulo,
    Menor, Mayor, MenorIgual, MayorIgual, Igual, Diferente,
    YLogico, OLogico, NoLogico
};

struct Token {
    TipoToken tipo;
    std::string lexema;
    int linea;
    int columna;
};

std::string nombreTipoToken(TipoToken tipo);

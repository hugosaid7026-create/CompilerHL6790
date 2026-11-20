#pragma once

#include "AnalizadorSemantico.hpp"
#include "GeneradorCodigoIntermedio.hpp"
#include "TablaSimbolos.hpp"
#include "Token.hpp"
#include <string>
#include <vector>

struct ResultadoExpresion { std::string valor; std::string tipo; int linea; int columna; };

class AnalizadorSintactico {
public:
    AnalizadorSintactico(const std::vector<Token>& tokens, TablaSimbolos& tabla, AnalizadorSemantico& semantico, GeneradorCodigoIntermedio& generador);
    void analizar();
    const std::vector<ErrorCompilador>& obtenerErrores() const;
private:
    bool coincide(TipoToken tipo);
    bool verificar(TipoToken tipo) const;
    const Token& avanzar();
    const Token& actual() const;
    bool esTipo(TipoToken tipo) const;
    std::string consumirTipo();
    Token consumir(TipoToken tipo, const std::string& mensaje);
    void error(const Token& token, const std::string& mensaje);
    void declaracionOFuncion();
    void funcion(const std::string& tipo, const Token& nombre);
    void declaracionVariable(const std::string& tipo, const Token& nombre, bool requierePuntoComa = true);
    void sentencia();
    void bloque(bool crearAmbito = true);
    void sentenciaSi();
    void sentenciaMientras();
    void sentenciaPara();
    void sentenciaRetornar();
    void sentenciaImprimir();
    void asignacion(bool requierePuntoComa = true);
    ResultadoExpresion expresion();
    ResultadoExpresion oLogico();
    ResultadoExpresion yLogico();
    ResultadoExpresion igualdad();
    ResultadoExpresion comparacion();
    ResultadoExpresion termino();
    ResultadoExpresion factor();
    ResultadoExpresion unario();
    ResultadoExpresion primario();
    ResultadoExpresion binaria(ResultadoExpresion izquierdo, const Token& operador, ResultadoExpresion derecho);
    std::vector<Token> tokens;
    std::size_t posicion = 0;
    TablaSimbolos& tabla;
    AnalizadorSemantico& semantico;
    GeneradorCodigoIntermedio& generador;
    std::vector<ErrorCompilador> errores;
};

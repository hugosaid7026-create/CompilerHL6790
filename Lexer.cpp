#include "Lexer.hpp"
#include <cctype>
#include <unordered_map>

std::string nombreTipoToken(TipoToken tipo) {
    static const std::vector<std::string> nombres = {"FinArchivo","Identificador","LiteralEntero","LiteralFlotante","LiteralCadena","Verdadero","Falso","TipoInt","TipoFloat","TipoBool","TipoString","Si","Sino","Mientras","Para","Retornar","Imprimir","ParentesisIzquierdo","ParentesisDerecho","LlaveIzquierda","LlaveDerecha","PuntoComa","Coma","Asignacion","Mas","Menos","Multiplicacion","Division","Modulo","Menor","Mayor","MenorIgual","MayorIgual","Igual","Diferente","YLogico","OLogico","NoLogico"};
    return nombres[static_cast<int>(tipo)];
}
AnalizadorLexico::AnalizadorLexico(const std::string& fuente) : fuente(fuente) {}
char AnalizadorLexico::actual() const { return posicion < fuente.size() ? fuente[posicion] : '\0'; }
char AnalizadorLexico::siguiente() const { return posicion + 1 < fuente.size() ? fuente[posicion + 1] : '\0'; }
char AnalizadorLexico::avanzar() { char caracter = actual(); if (caracter == '\n') { ++linea; columna = 1; } else ++columna; ++posicion; return caracter; }
void AnalizadorLexico::agregar(TipoToken tipo, const std::string& lexema, int lineaToken, int columnaToken) { tokens.push_back({tipo, lexema, lineaToken, columnaToken}); }
void AnalizadorLexico::ignorarEspaciosYComentarios() { while (true) { while (std::isspace(static_cast<unsigned char>(actual()))) avanzar(); if (actual() == '/' && siguiente() == '/') while (actual() != '\0' && actual() != '\n') avanzar(); else break; } }
std::vector<Token> AnalizadorLexico::analizar() {
    std::unordered_map<std::string, TipoToken> reservadas = {{"int",TipoToken::TipoInt},{"float",TipoToken::TipoFloat},{"bool",TipoToken::TipoBool},{"string",TipoToken::TipoString},{"if",TipoToken::Si},{"else",TipoToken::Sino},{"while",TipoToken::Mientras},{"for",TipoToken::Para},{"return",TipoToken::Retornar},{"print",TipoToken::Imprimir},{"true",TipoToken::Verdadero},{"false",TipoToken::Falso}};
    while (actual() != '\0') { ignorarEspaciosYComentarios(); if (actual() == '\0') break; int fila = linea, col = columna; char c = actual();
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') { std::string palabra; while (std::isalnum(static_cast<unsigned char>(actual())) || actual() == '_') palabra += avanzar(); auto it = reservadas.find(palabra); agregar(it == reservadas.end() ? TipoToken::Identificador : it->second, palabra, fila, col); continue; }
        if (std::isdigit(static_cast<unsigned char>(c))) { std::string numero; bool flotante = false; while (std::isdigit(static_cast<unsigned char>(actual())) || (actual() == '.' && !flotante)) { if (actual() == '.') flotante = true; numero += avanzar(); } agregar(flotante ? TipoToken::LiteralFlotante : TipoToken::LiteralEntero, numero, fila, col); continue; }
        if (c == '"') { avanzar(); std::string cadena; while (actual() != '"' && actual() != '\0' && actual() != '\n') cadena += avanzar(); if (actual() != '"') errores.push_back("Cadena sin cerrar en linea " + std::to_string(fila) + ", columna " + std::to_string(col)); else { avanzar(); agregar(TipoToken::LiteralCadena, "\"" + cadena + "\"", fila, col); } continue; }
        std::string dos; dos += c; dos += siguiente(); if (dos == "<=" || dos == ">=" || dos == "==" || dos == "!=" || dos == "&&" || dos == "||") { TipoToken tipo = dos == "<=" ? TipoToken::MenorIgual : dos == ">=" ? TipoToken::MayorIgual : dos == "==" ? TipoToken::Igual : dos == "!=" ? TipoToken::Diferente : dos == "&&" ? TipoToken::YLogico : TipoToken::OLogico; avanzar(); avanzar(); agregar(tipo, dos, fila, col); continue; }
        std::unordered_map<char, TipoToken> simples = {{'(',TipoToken::ParentesisIzquierdo},{')',TipoToken::ParentesisDerecho},{'{',TipoToken::LlaveIzquierda},{'}',TipoToken::LlaveDerecha},{';',TipoToken::PuntoComa},{',',TipoToken::Coma},{'=',TipoToken::Asignacion},{'+',TipoToken::Mas},{'-',TipoToken::Menos},{'*',TipoToken::Multiplicacion},{'/',TipoToken::Division},{'%',TipoToken::Modulo},{'<',TipoToken::Menor},{'>',TipoToken::Mayor},{'!',TipoToken::NoLogico}};
        auto it = simples.find(c); if (it != simples.end()) { avanzar(); agregar(it->second, std::string(1,c), fila, col); } else { errores.push_back("Caracter inesperado '" + std::string(1,c) + "' en linea " + std::to_string(fila) + ", columna " + std::to_string(col)); avanzar(); }
    } agregar(TipoToken::FinArchivo, "", linea, columna); return tokens;
}
const std::vector<std::string>& AnalizadorLexico::obtenerErrores() const { return errores; }

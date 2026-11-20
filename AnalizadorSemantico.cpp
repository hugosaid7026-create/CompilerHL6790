#include "AnalizadorSemantico.hpp"

void AnalizadorSemantico::agregarError(const std::string& mensaje, int linea, int columna) { errores.push_back({mensaje, linea, columna}); }
bool AnalizadorSemantico::asignacionCompatible(const std::string& destino, const std::string& origen) const {
    return destino == origen || (destino == "float" && origen == "int");
}
std::string AnalizadorSemantico::tipoOperacion(const std::string& operador, const std::string& izquierdo, const std::string& derecho, int linea, int columna) {
    bool numericos = (izquierdo == "int" || izquierdo == "float") && (derecho == "int" || derecho == "float");
    if (operador == "&&" || operador == "||") {
        if (izquierdo == "bool" && derecho == "bool") return "bool";
    } else if (operador == "+" && izquierdo == "string" && derecho == "string") return "string";
    else if (operador == "<" || operador == ">" || operador == "<=" || operador == ">=" || operador == "==" || operador == "!=") {
        if (numericos || izquierdo == derecho) return "bool";
    } else if (numericos) {
        if (operador == "%" && (izquierdo != "int" || derecho != "int")) { agregarError("El operador % solo acepta enteros", linea, columna); return "int"; }
        return (izquierdo == "float" || derecho == "float") ? "float" : "int";
    }
    agregarError("Tipos incompatibles para el operador " + operador, linea, columna);
    return "desconocido";
}
const std::vector<ErrorCompilador>& AnalizadorSemantico::obtenerErrores() const { return errores; }

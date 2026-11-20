#include "TablaSimbolos.hpp"

TablaSimbolos::TablaSimbolos() { ambitos.emplace_back(); }
void TablaSimbolos::entrarAmbito() { ambitos.emplace_back(); }
void TablaSimbolos::salirAmbito() { if (ambitos.size() > 1) ambitos.pop_back(); }
bool TablaSimbolos::declarar(const Simbolo& simbolo) {
    auto& actual = ambitos.back();
    if (actual.find(simbolo.nombre) != actual.end()) return false;
    actual[simbolo.nombre] = simbolo;
    simbolos.push_back(simbolo);
    return true;
}
const Simbolo* TablaSimbolos::buscar(const std::string& nombre) const {
    for (auto it = ambitos.rbegin(); it != ambitos.rend(); ++it) {
        auto encontrado = it->find(nombre);
        if (encontrado != it->end()) return &encontrado->second;
    }
    return nullptr;
}
bool TablaSimbolos::existeEnAmbitoActual(const std::string& nombre) const { return ambitos.back().find(nombre) != ambitos.back().end(); }
int TablaSimbolos::ambitoActual() const { return static_cast<int>(ambitos.size()) - 1; }
const std::vector<Simbolo>& TablaSimbolos::obtenerSimbolos() const { return simbolos; }

#include "GeneradorCodigoIntermedio.hpp"

std::string GeneradorCodigoIntermedio::nuevoTemporal() { return "t" + std::to_string(contadorTemporales++); }
std::string GeneradorCodigoIntermedio::nuevaEtiqueta() { return "L" + std::to_string(contadorEtiquetas++); }
void GeneradorCodigoIntermedio::emitir(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& resultado) { instrucciones.push_back({op, arg1, arg2, resultado}); }
std::vector<Instruccion> GeneradorCodigoIntermedio::extraerDesde(std::size_t indice) { std::vector<Instruccion> resultado(instrucciones.begin() + static_cast<std::ptrdiff_t>(indice), instrucciones.end()); instrucciones.erase(instrucciones.begin() + static_cast<std::ptrdiff_t>(indice), instrucciones.end()); return resultado; }
const std::vector<Instruccion>& GeneradorCodigoIntermedio::obtenerInstrucciones() const { return instrucciones; }

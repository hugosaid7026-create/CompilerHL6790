#pragma once

#include "Instruccion.hpp"
#include <vector>

class Optimizador {
public:
    std::vector<Instruccion> optimizar(const std::vector<Instruccion>& instrucciones) const;
private:
    std::vector<Instruccion> propagarConstantes(const std::vector<Instruccion>& instrucciones) const;
    std::vector<Instruccion> plegarConstantes(const std::vector<Instruccion>& instrucciones) const;
    std::vector<Instruccion> eliminarCodigoMuerto(const std::vector<Instruccion>& instrucciones) const;
};

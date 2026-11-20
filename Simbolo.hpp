#pragma once

#include <string>
#include <vector>

struct Simbolo {
    std::string nombre;
    std::string tipo;
    std::string categoria;
    int ambito;
    int linea;
    std::vector<std::string> tiposParametros;
};

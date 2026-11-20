#include "Optimizador.hpp"
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

namespace {
bool esNumero(const std::string& valor) { if (valor.empty()) return false; char* final = nullptr; std::strtod(valor.c_str(), &final); return final && *final == '\0'; }
bool esTemporal(const std::string& valor) { return valor.size() > 1 && valor[0] == 't' && std::all_of(valor.begin()+1, valor.end(), ::isdigit); }
std::string numero(double valor) { std::ostringstream salida; salida << std::setprecision(12) << valor; return salida.str(); }
}
std::vector<Instruccion> Optimizador::propagarConstantes(const std::vector<Instruccion>& instrucciones) const {
    std::unordered_map<std::string, std::string> constantes; std::vector<Instruccion> salida;
    for (auto instruccion : instrucciones) { if (instruccion.op == "etiqueta") constantes.clear(); if (constantes.count(instruccion.arg1)) instruccion.arg1 = constantes[instruccion.arg1]; if (constantes.count(instruccion.arg2)) instruccion.arg2 = constantes[instruccion.arg2]; if (instruccion.op == "=" && esNumero(instruccion.arg1)) constantes[instruccion.resultado] = instruccion.arg1; else if (!instruccion.resultado.empty()) constantes.erase(instruccion.resultado); salida.push_back(instruccion); } return salida;
}
std::vector<Instruccion> Optimizador::plegarConstantes(const std::vector<Instruccion>& instrucciones) const {
    std::vector<Instruccion> salida; for (auto instruccion : instrucciones) { if (esNumero(instruccion.arg1) && esNumero(instruccion.arg2)) { double a=std::stod(instruccion.arg1), b=std::stod(instruccion.arg2), r=0; bool valido=true; if(instruccion.op=="+")r=a+b; else if(instruccion.op=="-")r=a-b; else if(instruccion.op=="*")r=a*b; else if(instruccion.op=="/"&&b!=0)r=a/b; else if(instruccion.op=="%"&&b!=0)r=static_cast<int>(a)%static_cast<int>(b); else if(instruccion.op=="<")r=a<b; else if(instruccion.op==">")r=a>b; else if(instruccion.op=="<=")r=a<=b; else if(instruccion.op==">=")r=a>=b; else if(instruccion.op=="==")r=a==b; else if(instruccion.op=="!=")r=a!=b; else valido=false; if(valido) instruccion={"=",numero(r),"",instruccion.resultado}; } salida.push_back(instruccion); } return salida;
}
std::vector<Instruccion> Optimizador::eliminarCodigoMuerto(const std::vector<Instruccion>& instrucciones) const {
    std::unordered_set<std::string> usados; std::vector<Instruccion> salida; for (auto it=instrucciones.rbegin();it!=instrucciones.rend();++it) { const auto& ins=*it; bool quitar=esTemporal(ins.resultado)&&!usados.count(ins.resultado)&&(ins.op=="="||ins.op=="+"||ins.op=="-"||ins.op=="*"||ins.op=="/"||ins.op=="%"||ins.op=="<"||ins.op==">"||ins.op=="<="||ins.op==">="||ins.op=="=="||ins.op=="!="||ins.op=="&&"||ins.op=="||"||ins.op=="no"||ins.op=="negativo"); if (!quitar) { if (!ins.arg1.empty()) usados.insert(ins.arg1); if (!ins.arg2.empty()) usados.insert(ins.arg2); if (!ins.resultado.empty()) usados.erase(ins.resultado); salida.push_back(ins); } } std::reverse(salida.begin(),salida.end()); return salida;
}
std::vector<Instruccion> Optimizador::optimizar(const std::vector<Instruccion>& instrucciones) const { return eliminarCodigoMuerto(plegarConstantes(propagarConstantes(instrucciones))); }

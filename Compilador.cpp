#include "Compilador.hpp"
#include "Lexer.hpp"
#include "Optimizador.hpp"
#include "Parser.hpp"
#include <fstream>
#include <iostream>

bool Compilador::compilarArchivo(const std::string &ruta) {
  std::ifstream archivo(ruta);
  if (!archivo) {
    std::cerr << "No se pudo abrir el archivo: " << ruta << "\n";
    return false;
  }
  std::string fuente((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
  AnalizadorLexico lexico(fuente);
  std::vector<Token> tokens = lexico.analizar();
  TablaSimbolos tabla;
  AnalizadorSemantico semantico;
  GeneradorCodigoIntermedio generador;
  AnalizadorSintactico parser(tokens, tabla, semantico, generador);
  parser.analizar();
  Optimizador optimizador;
  std::vector<Instruccion> optimizado = optimizador.optimizar(generador.obtenerInstrucciones());
  std::cout << "=== 1. ANALISIS LEXICO ===\n";
  imprimirTokens(tokens);
  std::cout << "\n=== 2. ANALISIS SINTACTICO Y SEMANTICO ===\n";
  std::cout << "Parser recursivo descendente finalizado.\n";
  std::cout << "\n=== 3. TABLA DE SIMBOLOS ===\n";
  imprimirTabla(tabla);
  std::cout << "\n=== 4. CODIGO INTERMEDIO ===\n";
  imprimirCodigo(generador.obtenerInstrucciones());
  std::cout << "\n=== 5. CODIGO OPTIMIZADO ===\n";
  imprimirCodigo(optimizado);
  std::cout << "\n=== ERRORES ===\n";
  bool hayErrores = false;
  for (const auto &e : lexico.obtenerErrores()) {
    std::cout << e << "\n";
    hayErrores = true;
  }
  for (const auto &e : parser.obtenerErrores()) {
    std::cout << "Linea " << e.linea << ", columna " << e.columna << ": " << e.mensaje << "\n";
    hayErrores = true;
  }
  for (const auto &e : semantico.obtenerErrores()) {
    std::cout << "Linea " << e.linea << ", columna " << e.columna << ": " << e.mensaje << "\n";
    hayErrores = true;
  }
  if (!hayErrores)
    std::cout << "No se encontraron errores.\n";
  return !hayErrores;
}
void Compilador::imprimirTokens(const std::vector<Token> &tokens) const {
  for (const auto &t : tokens)
    std::cout << nombreTipoToken(t.tipo) << " | " << t.lexema << " | " << t.linea << ":"
              << t.columna << "\n";
}
void Compilador::imprimirTabla(const TablaSimbolos &tabla) const {
  for (const auto &s : tabla.obtenerSimbolos())
    std::cout << s.nombre << " | " << s.tipo << " | " << s.categoria << " | ambito " << s.ambito
              << " | linea " << s.linea << "\n";
}
void Compilador::imprimirCodigo(const std::vector<Instruccion> &instrucciones) const {
  for (const auto &i : instrucciones) {
    if (i.op == "etiqueta")
      std::cout << i.resultado << ":\n";
    else if (i.op == "=")
      std::cout << i.resultado << " = " << i.arg1 << "\n";
    else if (i.op == "salto")
      std::cout << "goto " << i.resultado << "\n";
    else if (i.op == "si_falso")
      std::cout << "ifFalse " << i.arg1 << " goto " << i.resultado << "\n";
    else if (i.op == "imprimir" || i.op == "retornar" || i.op == "parametro")
      std::cout << i.op << " " << i.arg1 << "\n";
    else if (i.op == "llamar")
      std::cout << i.resultado << " = call " << i.arg1 << ", " << i.arg2 << "\n";
    else if (i.op == "funcion" || i.op == "fin_funcion")
      std::cout << i.op << " " << i.arg1 << "\n";
    else if (i.arg2.empty())
      std::cout << i.resultado << " = " << i.op << " " << i.arg1 << "\n";
    else
      std::cout << i.resultado << " = " << i.arg1 << " " << i.op << " " << i.arg2 << "\n";
  }
}

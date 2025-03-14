/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * Curso: 3º
 * Práctica 4: Experimentación con Programación Dinámica
 * @autor Daniel Carbonell González de Chaves
 * @email alu0101578064@ull.edu.es
 * @autor Guillermo González Pineda
 * @email alu0101574899@ull.edu.es
 * @date 14/03/2025
 * @file main.cc: archivo main
 * @brief Contiene el main del programa que resuelve el problema del TSP
 */

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>

#include "../include/tsp-fuerza-bruta.h"
#include "../include/tsp-voraz.h"
#include "../include/tsp-dinamico.h"
#include "../include/generar-instancia.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " <ruta_carpeta>" << std::endl;
    return 1;
  }
  std::string ruta_carpeta = argv[1];
  std::vector<std::string> instancias;
  GenerarInstancia generador;
  generador.generar(6, 1, ruta_carpeta); // Generar 3 instancias con 5 nodos cada una
  for (const auto& entry : std::filesystem::directory_iterator(ruta_carpeta)) {
    if (entry.is_regular_file()) {
      instancias.push_back(entry.path().string());
    }
  }
  for (const auto& instancia : instancias) {
    TSPFuerzaBruta fuerza_bruta(instancia);
    TSPVoraz voraz(instancia);
    TSPDinamico dinamico(instancia);
    fuerza_bruta.resolver();
    voraz.resolver();
    dinamico.resolver();
    std::cout << "Instancia: " << instancia << std::endl << std::endl;
    std::cout << "Valor Fuerza Bruta: " << fuerza_bruta.obtenerMejorCosto() << std::endl;
    std::cout << "Tiempo Fuerza Bruta (ms): " << fuerza_bruta.obtenerTiempoEjecucion() << std::endl;
    std::cout << "Ruta Fuerza Bruta: " << fuerza_bruta.obtenerMejorRuta() << std::endl << std::endl;
    std::cout << "Valor Voraz: " << voraz.obtenerMejorCosto() << std::endl;
    std::cout << "Tiempo Voraz (ms): " << voraz.obtenerTiempoEjecucion() << std::endl;
    std::cout << "Ruta Voraz: " << voraz.obtenerMejorRuta() << std::endl << std::endl;
    // std::cout << "Valor Prog. Dinámica: " << dinamico.obtenerMejorCosto() << std::endl;
    // std::cout << "Tiempo Prog. Dinámica (ms): " << dinamico.obtenerTiempoEjecucion() << std::endl;
    // std::cout << "Ruta Prog. Dinámica: " << dinamico.obtenerMejorRuta() << std::endl;
  }
  return 0;
}

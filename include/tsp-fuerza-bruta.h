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
 * @file tsp-fuerza-bruta.h: archivo que contiene la cabecera de la clase TSPFuerzaBruta
 * @brief Contiene la cabecera de la clase TSPFuerzaBruta del programa que resuelve el problema del TSP
 */

#ifndef TSP_FUERZA_BRUTA_H
#define TSP_FUERZA_BRUTA_H

#include <vector>
#include <chrono>
#include <string>

#include "tsp-algoritmo.h"

/**
 * @class TSPFuerzaBruta
 * @brief Clase que implementa el algoritmo de fuerza bruta para resolver el problema del TSP.
 */
class TSPFuerzaBruta : public TSPAlgoritmo {
 private:
  std::string tiempo_ejecucion;
  std::chrono::time_point<std::chrono::high_resolution_clock> inicio;
  void permutar(std::vector<std::string>& ciudades, int l, int r, const std::string& punto_partida, int& costo_minimo, std::vector<std::string>& mejor_ruta_local);
 public:
  TSPFuerzaBruta(std::string nombreFichero) : TSPAlgoritmo(nombreFichero), tiempo_ejecucion("0"), inicio(std::chrono::high_resolution_clock::now()) {}
  ~TSPFuerzaBruta() override {}
  void resolver() override;
  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif
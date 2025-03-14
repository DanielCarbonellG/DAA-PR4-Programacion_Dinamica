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
 * @file tsp-voraz.cc: archivo que contiene la implementacion de la clase TSPVoraz
 * @brief Contiene la implementacion de la clase TSPVoraz del programa que resuelve el problema del TSP
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

#include "../include/tsp-voraz.h"

/**
 * @brief Método para resolver el problema del TSP utilizando un algoritmo voraz.
 */
void TSPVoraz::resolver() {
  auto start = std::chrono::high_resolution_clock::now();
  std::unordered_map<std::string, bool> visitado;
  std::vector<std::string> camino;
  std::string actual = punto_origen;
  visitado[actual] = true;
  camino.push_back(actual);
  for (int i = 1; i < cantidad_ciudades; ++i) {
    std::string siguiente;
    int minCosto = INFINITO;
    for (const auto& [ciudad, costo] : matriz_distancias[actual]) {
      if (!visitado[ciudad] && costo < minCosto) {
        minCosto = costo;
        siguiente = ciudad;
      }
    }
    if (siguiente.empty()) break;
    visitado[siguiente] = true;
    camino.push_back(siguiente);
    actual = siguiente;
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    if (elapsed.count() > 300) {
      tiempo_ejecucion = "EXCESIVO";
      return;
    }
  }
  camino.push_back(punto_origen);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  tiempo_ejecucion = std::to_string(elapsed.count());
  mejor_ruta = "";
  mejor_costo = 0;
  for (size_t i = 0; i < camino.size() - 1; ++i) {
    mejor_ruta += camino[i] + " -> ";
    mejor_costo += matriz_distancias[camino[i]][camino[i + 1]];
  }
  mejor_ruta += camino.back();
}
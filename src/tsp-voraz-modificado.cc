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
 * @file tsp-voraz-modificado.cc: archivo que contiene la implementacion de la clase TSPVorazModificado
 * @brief Contiene la implementacion de la clase TSPVorazModificado del programa que resuelve el problema del TSP
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <algorithm>

#include "../include/tsp-voraz-modificado.h"

/**
 * @brief Método para resolver el problema del TSP utilizando un algoritmo voraz modificado.
 */
void TSPVorazModificado::resolver() {
  auto start = std::chrono::high_resolution_clock::now();
  std::unordered_map<std::string, bool> visitado;
  std::vector<std::string> camino;
  std::string actual = punto_origen;
  visitado[actual] = true;
  camino.push_back(actual);
  for (int i = 1; i < cantidad_ciudades; ++i) {
    std::vector<std::pair<std::string, int>> opciones;
    for (const auto& [ciudad, costo] : matriz_distancias[actual]) {
      if (!visitado[ciudad]) {
        opciones.emplace_back(ciudad, costo);
      }
    }
    if (opciones.empty()) break;
    std::sort(opciones.begin(), opciones.end(), [](const auto& a, const auto& b) {
      return a.second < b.second;
    });
    int medio = opciones.size() / 2;
    std::string siguiente = opciones[medio].first;
    if (opciones.size() % 2 == 0) {
      siguiente = opciones[medio - 1].first;
    }
    visitado[siguiente] = true;
    camino.push_back(siguiente);
    actual = siguiente;
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = now - start;
    if (elapsed.count() > 300) {
      tiempo_ejecucion = "EXCESIVO";
      break;
    }
  }
  camino.push_back(punto_origen);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  if (tiempo_ejecucion != "EXCESIVO") {
    tiempo_ejecucion = std::to_string(elapsed.count());
  }
  mejor_ruta = "";
  mejor_costo = 0;
  for (size_t i = 0; i < camino.size() - 1; ++i) {
    mejor_ruta += camino[i] + " -> ";
    mejor_costo += matriz_distancias[camino[i]][camino[i + 1]];
  }
  mejor_ruta += camino.back();
}
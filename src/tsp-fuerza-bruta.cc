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
 * @file tsp-fuerza-bruta.cc: archivo que contiene la implementacion de la clase TSPFuerzaBruta
 * @brief Contiene la implementacion de la clase TSPFuerzaBruta del programa que resuelve el problema del TSP
 */

#include <vector>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <string>

#include "../include/tsp-fuerza-bruta.h"

/**
 * @brief Función recursiva para permutar las ciudades y encontrar la mejor ruta.
 * @param ciudades Vector de ciudades.
 * @param l Índice izquierdo.
 * @param r Índice derecho.
 * @param punto_partida Ciudad de partida.
 * @param costo_minimo Costo mínimo encontrado.
 * @param mejor_ruta_local Mejor ruta local encontrada.
 */
void TSPFuerzaBruta::permutar(std::vector<std::string>& ciudades, int l, int r, const std::string& punto_partida, int& costo_minimo, std::vector<std::string>& mejor_ruta_local) {
  auto ahora = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = ahora - inicio;
  if (elapsed.count() > 300) {
    tiempo_ejecucion = "EXCESIVO";
    return;
  }
  if (l == r) {
    int costo = 0;
    std::string anterior = punto_partida;
    for (const std::string& ciudad : ciudades) {
      costo += matriz_distancias[anterior][ciudad];
      anterior = ciudad;
    }
    costo += matriz_distancias[anterior][punto_partida];
    if (costo < costo_minimo) {
      costo_minimo = costo;
      mejor_ruta_local = ciudades;
    }
  } 
  else {
    for (int i = l; i <= r; i++) {
      std::swap(ciudades[l], ciudades[i]);
      permutar(ciudades, l + 1, r, punto_partida, costo_minimo, mejor_ruta_local);
      std::swap(ciudades[l], ciudades[i]);
    }
  }
}

/**
 * @brief Método para resolver el problema del TSP utilizando fuerza bruta.
 */
void TSPFuerzaBruta::resolver() {
  std::vector<std::string> ciudades;
  for (const auto& par : matriz_distancias) {
    ciudades.push_back(par.first);
  }
  std::string punto_partida = obtenerPuntoOrigen();
  ciudades.erase(std::remove(ciudades.begin(), ciudades.end(), punto_partida), ciudades.end());
  inicio = std::chrono::high_resolution_clock::now();
  int costo_minimo = INFINITO;
  std::vector<std::string> mejor_ruta_local;
  permutar(ciudades, 0, ciudades.size() - 1, punto_partida, costo_minimo, mejor_ruta_local);
  auto fin = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = fin - inicio;
  if (tiempo_ejecucion != "EXCESIVO") {
    tiempo_ejecucion = std::to_string(elapsed.count());
    mejor_costo = costo_minimo;
    mejor_ruta = punto_partida + " -> ";
    for (const std::string& ciudad : mejor_ruta_local) {
      mejor_ruta += ciudad + " -> ";
    }
    mejor_ruta += punto_partida;
  }
  else {
    mejor_costo = 0;
    mejor_ruta = "EXCESIVO";
  }
}
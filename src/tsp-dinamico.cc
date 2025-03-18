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
 * @file tsp-dinamico.cc: archivo que contiene la implementacion de la clase TSPDinamico
 * @brief Contiene la implementacion de la clase TSPDinamico del programa que resuelve el problema del TSP
 */

 #include "../include/tsp-dinamico.h"
 #include <vector>
 #include <unordered_map>
 #include <algorithm>
 #include <chrono>
 #include <limits>

/**
 * @brief Método para resolver el problema del TSP utilizando programación dinámica.
 */
void TSPDinamico::resolver() {
  auto inicio = std::chrono::high_resolution_clock::now();
  int n = cantidad_ciudades;
  std::vector<std::string> ciudades;
  std::unordered_map<std::string, int> ciudad_a_indice;
  for (const auto &par : matriz_distancias) {
    ciudades.push_back(par.first);
  }
  auto it = std::find(ciudades.begin(), ciudades.end(), punto_origen);
  if (it != ciudades.end() && it != ciudades.begin()) {
    std::swap(ciudades[0], *it);
  }
  for (int i = 0; i < n; i++) {
    ciudad_a_indice[ciudades[i]] = i;
  }
  std::vector<std::vector<int>> costo(n, std::vector<int>(n, INFINITO));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j)
        costo[i][j] = 0;
      else {
        costo[i][j] = matriz_distancias[ciudades[i]][ciudades[j]];
      }
    }
  }
  int ALL = 1 << n;
  std::vector<std::vector<int>> dp(ALL, std::vector<int>(n, INFINITO));
  std::vector<std::vector<int>> parent(ALL, std::vector<int>(n, -1));
  dp[1][0] = 0;
  for (int mask = 1; mask < ALL; mask++) {
    auto ahora = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo_transcurrido = ahora - inicio;
    if (tiempo_transcurrido.count() > 300) {
      tiempo_ejecucion = "EXCESIVO";
      mejor_costo = 0;
      mejor_ruta = "EXCESIVO";
      return;
    }
    if (!(mask & 1))
      continue;
    for (int i = 0; i < n; i++) {
      if (!(mask & (1 << i)) || dp[mask][i] == INFINITO)
        continue;
      for (int j = 0; j < n; j++) {
        if (mask & (1 << j))
          continue;
        int nuevo_mask = mask | (1 << j);
        int nuevo_costo = dp[mask][i] + costo[i][j];
        if (nuevo_costo < dp[nuevo_mask][j]) {
          dp[nuevo_mask][j] = nuevo_costo;
          parent[nuevo_mask][j] = i;
        }
      }
    }
  }
  int full_mask = ALL - 1;
  int best_cost = INFINITO;
  int best_last = -1;
  for (int i = 1; i < n; i++) {
    if (dp[full_mask][i] + costo[i][0] < best_cost) {
      best_cost = dp[full_mask][i] + costo[i][0];
      best_last = i;
    }
  }
  if (best_cost == INFINITO) {
    tiempo_ejecucion = "EXCESIVO";
    mejor_costo = 0;
    mejor_ruta = "EXCESIVO";
    return;
  }
  std::vector<int> camino;
  int mask = full_mask;
  int actual = best_last;
  while (actual != -1) {
    camino.push_back(actual);
    int temp = parent[mask][actual];
    mask = mask & ~(1 << actual);
    actual = temp;
  }
  std::reverse(camino.begin(), camino.end());
  camino.push_back(0);
  std::string ruta;
  for (size_t i = 0; i < camino.size(); i++) {
    ruta += ciudades[camino[i]];
    if (i != camino.size() - 1)
      ruta += " -> ";
  }
  auto fin = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duracion_total = fin - inicio;
  tiempo_ejecucion = std::to_string(duracion_total.count());
  mejor_costo = best_cost;
  mejor_ruta = ruta;
}
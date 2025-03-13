#ifndef TSP_DINAMICO_H
#define TSP_DINAMICO_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>

#include "tsp-algoritmo.h"

class TSPDinamico : public TSPAlgoritmo {
 private:
  std::unordered_map<int, std::unordered_map<int, int>> memoria;
  std::unordered_map<std::string, int> ciudad_a_indice;
  std::vector<std::string> indice_a_ciudad;
  std::string tiempo_ejecucion;

 public:
  TSPDinamico(std::string nombreFichero)
    : TSPAlgoritmo(nombreFichero), memoria(), ciudad_a_indice(), indice_a_ciudad(), tiempo_ejecucion("0") {
    int indice = 0;
    for (const auto& par : matriz_distancias) {
      ciudad_a_indice[par.first] = indice++;
      indice_a_ciudad.push_back(par.first);
    }
  }
  ~TSPDinamico() override {}
  int tsp(int mascara, int posicion) {
    // Si todas las ciudades han sido visitadas, retornar la distancia a la ciudad de origen
    if (mascara == (1 << cantidad_ciudades) - 1) {
      return matriz_distancias[indice_a_ciudad[posicion]]["0"];
    }
    // Si el resultado ya está memorizado, retornarlo
    if (memoria[mascara].count(posicion)) {
      return memoria[mascara][posicion];
    }
    int costo_minimo = INFINITO;
    // Probar todas las ciudades no visitadas
    for (int siguiente = 0; siguiente < cantidad_ciudades; siguiente++) {
      if (!(mascara & (1 << siguiente))) {
        int nuevo_costo = matriz_distancias[indice_a_ciudad[posicion]][indice_a_ciudad[siguiente]] + tsp(mascara | (1 << siguiente), siguiente);
        costo_minimo = std::min(costo_minimo, nuevo_costo);
      }
    }
    // Memorizar y retornar el costo mínimo
    return memoria[mascara][posicion] = costo_minimo;
  }

  void resolver() override {
    auto inicio = std::chrono::high_resolution_clock::now();
    mejor_costo = tsp(1, 0);
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    if (duracion > TIEMPO_LIMITE_MS) {
      tiempo_ejecucion = "EXCESIVO";
    } else {
      tiempo_ejecucion = std::to_string(duracion);
    }
    mejor_ruta = "Calculado con DP";
  }
  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif // TSP_DINAMICO_H

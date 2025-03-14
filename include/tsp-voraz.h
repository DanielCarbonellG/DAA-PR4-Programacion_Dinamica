#ifndef TSP_VORAZ_H
#define TSP_VORAZ_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <string>

#include "tsp-algoritmo.h"

class TSPVoraz : public TSPAlgoritmo {
 private:
  std::string tiempo_ejecucion;
 public:
  TSPVoraz(std::string nombreFichero)
    : TSPAlgoritmo(nombreFichero), tiempo_ejecucion("0") {}
  ~TSPVoraz() override {}
  void resolver() override {
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
      if (elapsed.count() > 300) { // 300 seconds = 5 minutes
        tiempo_ejecucion = "EXCESIVO";
        return;
      }
    }

    // Volver al nodo inicial
    camino.push_back(punto_origen);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    tiempo_ejecucion = std::to_string(elapsed.count());

    // Actualizar mejor ruta y costo
    mejor_ruta = "";
    mejor_costo = 0;
    for (size_t i = 0; i < camino.size() - 1; ++i) {
      mejor_ruta += camino[i] + " -> ";
      mejor_costo += matriz_distancias[camino[i]][camino[i + 1]];
    }
    mejor_ruta += camino.back();
  }
  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif // TSP_VORAZ_H

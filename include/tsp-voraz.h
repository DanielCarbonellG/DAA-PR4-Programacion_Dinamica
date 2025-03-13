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
    std::unordered_map<std::string, bool> visitado;
    std::vector<std::string> ruta;
    int costo = 0;
    std::string actual = "0"; // Asumiendo que "0" es el punto de partida
    auto inicio = std::chrono::high_resolution_clock::now();
    ruta.push_back(actual);
    visitado[actual] = true;
    for (int i = 1; i < cantidad_ciudades; i++) {
      std::string siguiente_ciudad;
      int minima_distancia = INFINITO;
      for (const auto& par : matriz_distancias[actual]) {
        const std::string& ciudad = par.first;
        int distancia = par.second;
        if (!visitado[ciudad] && distancia < minima_distancia) {
          siguiente_ciudad = ciudad;
          minima_distancia = distancia;
        }
      }
      if (minima_distancia == INFINITO) { break; }
      visitado[siguiente_ciudad] = true;
      costo += minima_distancia;
      actual = siguiente_ciudad;
      ruta.push_back(actual);
    }
    costo += matriz_distancias[actual]["0"]; // Volver al inicio
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    if (duracion > TIEMPO_LIMITE_MS) {
      tiempo_ejecucion = "EXCESIVO";
    } else {
      tiempo_ejecucion = std::to_string(duracion);
    }
    mejor_costo = costo;
    mejor_ruta = "0 -> ";
    for (const std::string& ciudad : ruta) {
      mejor_ruta += ciudad + " -> ";
    }
    mejor_ruta += "0";
  }
  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif // TSP_VORAZ_H

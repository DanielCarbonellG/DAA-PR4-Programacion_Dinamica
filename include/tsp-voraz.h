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

using namespace std;
using namespace std::chrono;

const int INFINITO = numeric_limits<int>::max();
const int TIEMPO_LIMITE_MS = 300000; // 5 minutos

class TSPVoraz : public TSPAlgoritmo {
 public:
  TSPVoraz(vector<vector<int>> matriz) : TSPAlgoritmo(matriz) {}
  void resolver() override {
    vector<bool> visitado(cantidad_ciudades, false);
    vector<int> ruta;
    int costo = 0, actual = 0;
    auto inicio = high_resolution_clock::now();
    ruta.push_back(actual);
    visitado[actual] = true;
    for (int i = 1; i < cantidad_ciudades; i++) {
      int siguiente_ciudad = -1, minima_distancia = INFINITO;
      for (int j = 0; j < cantidad_ciudades; j++) {
        if (!visitado[j] && matriz_distancias[actual][j] < minima_distancia) {
          siguiente_ciudad = j;
          minima_distancia = matriz_distancias[actual][j];
        }
      }
      if (siguiente_ciudad == -1) { break; }
      visitado[siguiente_ciudad] = true;
      costo += minima_distancia;
      actual = siguiente_ciudad;
      ruta.push_back(actual);
    }
    costo += matriz_distancias[actual][0]; // Volver al inicio
    mejor_costo = costo;
    mejor_ruta = "0 -> ";
    for (int ciudad : ruta) {
      mejor_ruta += to_string(ciudad) + " -> ";
    }
    mejor_ruta += "0";
  }
};

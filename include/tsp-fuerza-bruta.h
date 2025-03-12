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

class TSPFuerzaBruta : public TSPAlgoritmo {
 public:
  TSPFuerzaBruta(vector<vector<int>> matriz) : TSPAlgoritmo(matriz) {}
  void resolver() override {
    vector<int> ciudades;
    for (int i = 1; i < cantidad_ciudades; i++) {
      ciudades.push_back(i);
    }
    auto inicio = high_resolution_clock::now();
    int costo_minimo = INFINITO;
    vector<int> mejor_ruta_local;
    do {
      int costo = 0, anterior = 0;
      for (int ciudad : ciudades) {
        costo += matriz_distancias[anterior][ciudad];
        anterior = ciudad;
      }
      costo += matriz_distancias[anterior][0];
      if (costo < costo_minimo) {
        costo_minimo = costo;
        mejor_ruta_local = ciudades;
      }
      auto ahora = high_resolution_clock::now();
      if (duration_cast<milliseconds>(ahora - inicio).count() > TIEMPO_LIMITE_MS) {
        mejor_costo = costo_minimo;
        mejor_ruta = "EXCESIVO";
        return;
      }
    } while (next_permutation(ciudades.begin(), ciudades.end()));
    mejor_costo = costo_minimo;
    mejor_ruta = "0 -> ";
    for (int ciudad : mejor_ruta_local) {
      mejor_ruta += to_string(ciudad) + " -> ";
    }
    mejor_ruta += "0";
  }
};
  
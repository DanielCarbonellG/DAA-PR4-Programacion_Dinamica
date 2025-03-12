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

class TSPDinamico : public TSPAlgoritmo {
 private:
  unordered_map<int, unordered_map<int, int>> memoria;
 
 public:
  TSPDinamico(vector<vector<int>> matriz) : TSPAlgoritmo(matriz) {}
  int tsp(int mascara, int posicion) {
    if (mascara == (1 << cantidad_ciudades) - 1) {
      return matriz_distancias[posicion][0];
    }
    if (memoria[mascara].count(posicion)) {
      return memoria[mascara][posicion];
    }
    int costo_minimo = INFINITO;
    for (int siguiente = 0; siguiente < cantidad_ciudades; siguiente++) {
      if (!(mascara & (1 << siguiente))) {
        int nuevo_costo = matriz_distancias[posicion][siguiente] + tsp(mascara | (1 << siguiente), siguiente);
        costo_minimo = min(costo_minimo, nuevo_costo);
      }
    }
    return memoria[mascara][posicion] = costo_minimo;
  }
  void resolver() override {
    auto inicio = high_resolution_clock::now();
    mejor_costo = tsp(1, 0);
    mejor_ruta = "Calculado con DP";
  }
};
  
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

class GeneradorTSP {
 public:
  static void generarInstancia(int cantidad_ciudades, string nombre_archivo) {
    ofstream archivo(nombre_archivo);
    archivo << cantidad_ciudades << endl;
    for (int i = 0; i < cantidad_ciudades; i++) {
      for (int j = i + 1; j < cantidad_ciudades; j++) {
        int distancia = rand() % 100 + 1;
        archivo << i << " " << j << " " << distancia << endl;
      }
    }
    archivo.close();
  }
};
  
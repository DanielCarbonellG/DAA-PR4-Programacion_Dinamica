#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>

using namespace std;
using namespace std::chrono;

const int INFINITO = numeric_limits<int>::max();
const int TIEMPO_LIMITE_MS = 300000; // 5 minutos

class TSPAlgoritmo {
 protected:
  vector<vector<int>> matriz_distancias;
  int cantidad_ciudades;
  string mejor_ruta;
  int mejor_costo;
 public:
  TSPAlgoritmo(vector<vector<int>> matriz) : matriz_distancias(matriz), cantidad_ciudades(matriz.size()), mejor_costo(INFINITO) {}
  virtual void resolver() = 0;
  int obtenerMejorCosto() { return mejor_costo; }
  string obtenerMejorRuta() { return mejor_ruta; }
};

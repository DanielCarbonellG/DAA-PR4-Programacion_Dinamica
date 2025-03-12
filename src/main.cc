#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>

#include "../include/tsp-fuerza-bruta.h"
#include "../include/tsp-voraz.h"
#include "../include/tsp-dinamico.h"

using namespace std;
using namespace std::chrono;

int main() {
  vector<vector<int>> matriz = {
      {  0, 25, 10, 15 },
      { 25,  0, 10, 45 },
      { 10, 10,  0,  5 },
      { 15, 45,  5,  0 }
  };

  TSPFuerzaBruta fuerza_bruta(matriz);
  TSPVoraz voraz(matriz);
  TSPDinamico dinamico(matriz);

  fuerza_bruta.resolver();
  voraz.resolver();
  dinamico.resolver();

  cout << "Fuerza Bruta: " << fuerza_bruta.obtenerMejorCosto() << " | " << fuerza_bruta.obtenerMejorRuta() << endl;
  cout << "Voraz: " << voraz.obtenerMejorCosto() << " | " << voraz.obtenerMejorRuta() << endl;
  cout << "Programación Dinámica: " << dinamico.obtenerMejorCosto() << " | " << dinamico.obtenerMejorRuta() << endl;

  return 0;
}

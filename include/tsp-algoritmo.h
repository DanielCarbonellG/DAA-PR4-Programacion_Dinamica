#ifndef TSP_ALGORITMO_H
#define TSP_ALGORITMO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <limits>

const int INFINITO = std::numeric_limits<int>::max();
const int TIEMPO_LIMITE_MS = 300000; // 5 minutos

class TSPAlgoritmo {
 protected:
  std::unordered_map<std::string, std::unordered_map<std::string, int>> matriz_distancias;
  int cantidad_ciudades;
  std::string mejor_ruta;
  int mejor_costo;
  std::string punto_origen; // Añadir miembro para almacenar el punto de origen
 public:
  TSPAlgoritmo(std::string nombreFichero)
    : matriz_distancias(), cantidad_ciudades(0), mejor_ruta(""), mejor_costo(INFINITO), punto_origen("") {
    std::ifstream entrada(nombreFichero);
    if (!entrada.is_open()) {
      std::cout << "Error al abrir el archivo de entrada.";
      exit(EXIT_FAILURE);
    }
    std::string linea;
    std::getline(entrada, linea);
    cantidad_ciudades = std::stoi(linea);

    bool primer_punto = true;
    while (std::getline(entrada, linea)) {
      std::istringstream iss(linea);
      std::string ciudad1, ciudad2;
      int distancia;
      iss >> ciudad1 >> ciudad2 >> distancia;

      if (primer_punto) {
        punto_origen = ciudad1;
        primer_punto = false;
      }

      matriz_distancias[ciudad1][ciudad2] = distancia;
      matriz_distancias[ciudad2][ciudad1] = distancia; // Asumiendo que la distancia es bidireccional
    }
  }
  virtual ~TSPAlgoritmo() {}
  virtual void resolver() = 0;
  int obtenerMejorCosto() { return mejor_costo; }
  std::string obtenerMejorRuta() { return mejor_ruta; }
  std::string obtenerPuntoOrigen() const { return punto_origen; } // Añadir getter para el punto de origen
};

#endif // TSP_ALGORITMO_H

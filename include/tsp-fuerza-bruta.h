#ifndef TSP_FUERZA_BRUTA_H
#define TSP_FUERZA_BRUTA_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <string>

#include "tsp-algoritmo.h"

class TSPFuerzaBruta : public TSPAlgoritmo {
 private:
  std::string tiempo_ejecucion;
  std::chrono::time_point<std::chrono::high_resolution_clock> inicio;

  void permutar(std::vector<std::string>& ciudades, int l, int r, const std::string& punto_partida, int& costo_minimo, std::vector<std::string>& mejor_ruta_local) {
    // Verificar si el tiempo de ejecución ha excedido el límite
    auto ahora = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(ahora - inicio).count() > TIEMPO_LIMITE_MS) {
      tiempo_ejecucion = "EXCESIVO";
      return;
    }

    if (l == r) {
      int costo = 0;
      std::string anterior = punto_partida;

      // Calcular el costo de la ruta actual
      for (const std::string& ciudad : ciudades) {
        costo += matriz_distancias[anterior][ciudad];
        anterior = ciudad;
      }
      // Añadir el costo de regresar al punto de partida
      costo += matriz_distancias[anterior][punto_partida];

      // Si el costo de la ruta actual es menor que el costo mínimo, actualizar el costo mínimo y la mejor ruta
      if (costo < costo_minimo) {
        costo_minimo = costo;
        mejor_ruta_local = ciudades;
      }
    } else {
      for (int i = l; i <= r; i++) {
        std::swap(ciudades[l], ciudades[i]);
        permutar(ciudades, l + 1, r, punto_partida, costo_minimo, mejor_ruta_local);
        std::swap(ciudades[l], ciudades[i]); // backtrack
      }
    }
  }

 public:
  TSPFuerzaBruta(std::string nombreFichero)
    : TSPAlgoritmo(nombreFichero), tiempo_ejecucion("0") {}
  ~TSPFuerzaBruta() override {}

  void resolver() override {
    // Crear un vector con todas las ciudades
    std::vector<std::string> ciudades;
    for (const auto& par : matriz_distancias) {
      ciudades.push_back(par.first);
    }

    // Obtener el punto de origen detectado
    std::string punto_partida = obtenerPuntoOrigen();
    // Eliminar el punto de origen del vector de ciudades
    ciudades.erase(std::remove(ciudades.begin(), ciudades.end(), punto_partida), ciudades.end());

    // Iniciar el cronómetro para medir el tiempo de ejecución
    inicio = std::chrono::high_resolution_clock::now();
    int costo_minimo = INFINITO;
    std::vector<std::string> mejor_ruta_local;

    // Generar todas las permutaciones posibles de las ciudades manualmente
    permutar(ciudades, 0, ciudades.size() - 1, punto_partida, costo_minimo, mejor_ruta_local);

    // Detener el cronómetro y calcular la duración total
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    if (tiempo_ejecucion != "EXCESIVO") {
      tiempo_ejecucion = std::to_string(duracion);
      // Actualizar el costo mínimo y la mejor ruta
      mejor_costo = costo_minimo;
      mejor_ruta = punto_partida + " -> ";
      for (const std::string& ciudad : mejor_ruta_local) {
        mejor_ruta += ciudad + " -> ";
      }
      mejor_ruta += punto_partida;
    }
    else {
      mejor_costo = 0;
      mejor_ruta = "EXCESIVO";
    }

  }

  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif // TSP_FUERZA_BRUTA_H
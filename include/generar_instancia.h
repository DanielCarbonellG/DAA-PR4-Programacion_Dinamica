#ifndef GENERAR_INSTANCIA_H
#define GENERAR_INSTANCIA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

class GenerarInstancia {
 public:
  GenerarInstancia() {}
  ~GenerarInstancia() {}

  void generar(int num_nodos, int num_instancias, const std::string& carpeta_salida) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < num_instancias; ++i) {
      std::string nombre_fichero = carpeta_salida + "/instancia_" + std::to_string(num_nodos) + "_nodos_" + std::to_string(i + 1) + ".txt";
      std::ofstream archivo(nombre_fichero);

      if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombre_fichero << std::endl;
        continue;
      }

      archivo << num_nodos << std::endl;
      std::vector<std::string> nodos;
      for (int j = 0; j < num_nodos; ++j) {
        nodos.push_back(std::string(1, 'A' + j)); // Asignar nombres a los nodos con letras
      }

      for (int j = 0; j < num_nodos; ++j) {
        for (int k = j + 1; k < num_nodos; ++k) {
          int distancia = dist(gen);
          archivo << nodos[j] << " " << nodos[k] << " " << distancia << std::endl;
        }
      }

      archivo.close();
    }
  }
};

#endif // GENERAR_INSTANCIA_H
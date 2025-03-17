/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * Curso: 3º
 * Práctica 4: Experimentación con Programación Dinámica
 * @autor Daniel Carbonell González de Chaves
 * @email alu0101578064@ull.edu.es
 * @autor Guillermo González Pineda
 * @email alu0101574899@ull.edu.es
 * @date 14/03/2025
 * @file main.cc: archivo main
 * @brief Contiene el main del programa que resuelve el problema del TSP con dos modos de funcionamiento.
 */

#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm>

// Inclusión de los headers de las distintas implementaciones TSP
#include "../include/tsp-fuerza-bruta.h"
#include "../include/tsp-voraz.h"
#include "../include/tsp-dinamico.h"
#include "../include/generar-instancia.h"

void imprimirResultados(std::vector<std::tuple<std::string, TSPFuerzaBruta ,TSPVoraz, TSPDinamico>>& resultados) {
  std::ofstream archivo("../output/resultado.txt");
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo de resultados." << std::endl;
    return;
  }
  // Se añade la columna para los caminos de cada algoritmo.
  archivo << "Instancia | "
          << "Valor Fuerza Bruta | Tiempo Fuerza Bruta (ms) | "
          << "Valor Prog. Dinámica | Tiempo Prog. Dinámica (ms) | "
          << "Valor Voraz | Tiempo Voraz (ms)" << std::endl;
  for (auto& resultado : resultados) {
    auto& [instancia, fuerza_bruta, voraz, dinamico] = resultado;
    archivo << instancia << " | "
            << fuerza_bruta.obtenerMejorCosto() << " | "
            << fuerza_bruta.obtenerTiempoEjecucion() << " | "
            << dinamico.obtenerMejorCosto() << " | "
            << dinamico.obtenerTiempoEjecucion() << " | "
            << voraz.obtenerMejorCosto() << " | "
            << voraz.obtenerTiempoEjecucion() << std::endl;
  }
  archivo.close();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " <ruta_carpeta_salida>" << std::endl;
    return 1;
  }
  int opcion;
  std::cout << "Seleccione el modo de ejecución:\n";
  std::cout << "1. Probar un único grafo y mostrarlo por pantalla\n";
  std::cout << "2. Probar múltiples grafos en un intervalo y guardar resultados en archivo\n";
  std::cout << "Opción: ";
  std::cin >> opcion;
  
  GenerarInstancia generador;
  
  if (opcion == 1) {
    // MODO 1: Probar un único grafo
    int num_nodos;
    std::cout << "Ingrese el número de nodos para el grafo: ";
    std::cin >> num_nodos;
    
    // Utilizamos una carpeta temporal para almacenar la instancia generada
    std::string temp_folder = "./temp_instance";
    if (!std::filesystem::exists(temp_folder)) {
      std::filesystem::create_directory(temp_folder);
    }
    // Limpiar la carpeta temporal (opcional)
    for (const auto& entry : std::filesystem::directory_iterator(temp_folder)) {
      std::filesystem::remove_all(entry.path());
    }
    
    // Generar la instancia en la carpeta temporal
    generador.generar(num_nodos, 1, temp_folder);
    
    // Suponemos que se genera un único fichero en la carpeta temporal
    std::string instancia_archivo;
    for (const auto& entry : std::filesystem::directory_iterator(temp_folder)) {
      if (entry.is_regular_file()) {
        instancia_archivo = entry.path().string();
        break;
      }
    }
    
    if (instancia_archivo.empty()) {
      std::cerr << "No se encontró la instancia generada." << std::endl;
      return 1;
    }
    
    // Imprimir el contenido de la instancia por pantalla
    std::ifstream archivo(instancia_archivo);
    if (archivo.is_open()) {
      std::cout << "\n--- Contenido de la instancia generada ---\n";
      std::cout << archivo.rdbuf() << std::endl;
      archivo.close();
    } else {
      std::cerr << "Error al abrir el archivo de la instancia." << std::endl;
    }
    
    // Ejecutar los algoritmos TSP sobre la instancia generada
    TSPFuerzaBruta fuerza_bruta(instancia_archivo);
    TSPVoraz voraz(instancia_archivo);
    TSPDinamico dinamico(instancia_archivo);
    
    fuerza_bruta.resolver();
    voraz.resolver();
    dinamico.resolver();
    
    std::cout << "\n--- Resultados del TSP ---\n";
    std::cout << "Fuerza Bruta: Costo = " << fuerza_bruta.obtenerMejorCosto()
              << ", Tiempo = " << fuerza_bruta.obtenerTiempoEjecucion() << " ms" << std::endl;
    std::cout << "Camino: " << fuerza_bruta.obtenerMejorRuta() << std::endl << std::endl;
    
    std::cout << "Programación Dinámica: Costo = " << dinamico.obtenerMejorCosto()
              << ", Tiempo = " << dinamico.obtenerTiempoEjecucion() << " ms" << std::endl;
    std::cout << "Camino: " << dinamico.obtenerMejorRuta() << std::endl << std::endl;
    
    std::cout << "Voraz: Costo = " << voraz.obtenerMejorCosto()
              << ", Tiempo = " << voraz.obtenerTiempoEjecucion() << " ms" << std::endl;
    std::cout << "Camino: " << voraz.obtenerMejorRuta() << std::endl;    
  } else if (opcion == 2) {
    int min_nodos, max_nodos;
    std::cout << "Ingrese el número mínimo de nodos: ";
    std::cin >> min_nodos;
    std::cout << "Ingrese el número máximo de nodos: ";
    std::cin >> max_nodos;
    
    std::string ruta_carpeta = argv[1];
    
    // Generar instancias para cada tamaño en el intervalo
    for (int i = min_nodos; i <= max_nodos; ++i) {
      generador.generar(i, 1, ruta_carpeta);
    }
    
    // Recopilar las rutas de las instancias generadas
    std::vector<std::string> instancias;
    for (const auto& entry : std::filesystem::directory_iterator(ruta_carpeta)) {
      if (entry.is_regular_file()) {
        instancias.push_back(entry.path().string());
      }
    }
    
    // Ejecutar los algoritmos TSP para cada instancia y recopilar resultados
    std::vector<std::tuple<std::string, TSPFuerzaBruta, TSPVoraz, TSPDinamico>> resultados;
    for (const auto& instancia : instancias) {
      TSPFuerzaBruta fuerza_bruta(instancia);
      TSPVoraz voraz(instancia);
      TSPDinamico dinamico(instancia);
      fuerza_bruta.resolver();
      voraz.resolver();
      dinamico.resolver();
      resultados.emplace_back(instancia, fuerza_bruta, voraz, dinamico);
    }
    
    // Imprimir la tabla de resultados en el archivo de salida
    imprimirResultados(resultados);
    std::cout << "\nLos resultados han sido guardados en ../output/resultado.txt" << std::endl;
    
  } else {
    std::cerr << "Opción no válida." << std::endl;
    return 1;
  }
  
  return 0;
}

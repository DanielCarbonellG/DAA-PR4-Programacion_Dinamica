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
 * @file generar-instancia.cc: archivo que contiene la implementacion de la clase GenerarInstancia
 * @brief Contiene la implementacion de la clase GenerarInstancia del programa que resuelve el problema del TSP
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

#include "../include/generar-instancia.h"

/**
 * @brief Genera el nombre del nodo basado en un índice.
 * @param index Índice del nodo.
 * @return Nombre del nodo.
 */
std::string generarNombreNodo(int index) {
  std::string nombre;
  while (index >= 0) {
    nombre = char('A' + (index % 26)) + nombre;
    index = index / 26 - 1;
  }
  return nombre;
}

/**
 * @brief Genera instancias del problema del TSP.
 * @param num_nodos Número de nodos (ciudades).
 * @param num_instancias Número de instancias a generar.
 * @param carpeta_salida Carpeta donde se guardarán las instancias generadas.
 */
void GenerarInstancia::generar(int num_nodos, int num_instancias, const std::string& carpeta_salida) {
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
      nodos.push_back(generarNombreNodo(j));
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
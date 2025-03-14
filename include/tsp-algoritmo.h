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
 * @file tsp-algoritmo.h: archivo que contiene la cabecera de la clase TSPAlgoritmo
 * @brief Contiene la cabecera de la clase TSPAlgoritmo del programa que resuelve el problema del TSP
 */

#ifndef TSP_ALGORITMO_H
#define TSP_ALGORITMO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <limits>

const int INFINITO = std::numeric_limits<int>::max();
const int TIEMPO_LIMITE_MS = 300000;

/**
 * @class TSPAlgoritmo
 * @brief Clase base abstracta para resolver el problema del TSP (Traveling Salesman Problem).
 */
class TSPAlgoritmo {
 protected:
  std::unordered_map<std::string, std::unordered_map<std::string, int>> matriz_distancias;
  int cantidad_ciudades;
  std::string mejor_ruta;
  int mejor_costo;
  std::string punto_origen;
 public:
  TSPAlgoritmo(std::string nombreFichero) : matriz_distancias(), cantidad_ciudades(0), mejor_ruta(""), mejor_costo(INFINITO), punto_origen("") {
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
      matriz_distancias[ciudad2][ciudad1] = distancia;
    }
  }
  virtual ~TSPAlgoritmo() {}
  virtual void resolver() = 0;
  int obtenerMejorCosto() { return mejor_costo; }
  std::string obtenerMejorRuta() { return mejor_ruta; }
  std::string obtenerPuntoOrigen() const { return punto_origen; }
};

#endif

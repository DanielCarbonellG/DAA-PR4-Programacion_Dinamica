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
 * @file generar-instancia.h: archivo que contiene la cabecera de la clase GenerarInstancia
 * @brief Contiene la cabecera de la clase GenerarInstancia del programa que resuelve el problema del TSP
 */

#ifndef GENERAR_INSTANCIA_H
#define GENERAR_INSTANCIA_H

#include <string>

/**
 * @class GenerarInstancia
 * @brief Clase que genera instancias del problema del TSP.
 */
class GenerarInstancia {
 public:
  GenerarInstancia() {}
  ~GenerarInstancia() {}
  void generar(int num_nodos, int num_instancias, const std::string& carpeta_salida);
};

#endif
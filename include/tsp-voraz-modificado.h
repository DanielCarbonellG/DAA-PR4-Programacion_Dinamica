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
 * @file tsp-voraz.h: archivo que contiene la cabecera de la clase TSPVoraz
 * @brief Contiene la cabecera de la clase TSPVoraz del programa que resuelve el problema del TSP
 */

#ifndef TSP_VORAZ_MODIFICADO_H
#define TSP_VORAZ_MODIFICADO_H

#include <string>

#include "tsp-algoritmo.h"

/**
 * @class TSPVoraz
 * @brief Clase que implementa el algoritmo voraz para resolver el problema del TSP.
 */
class TSPVorazModificado : public TSPAlgoritmo {
 private:
  std::string tiempo_ejecucion;
 public:
 TSPVorazModificado(std::string nombreFichero) : TSPAlgoritmo(nombreFichero), tiempo_ejecucion("0") {}
  ~TSPVorazModificado() override {}
  void resolver() override;
  std::string obtenerTiempoEjecucion() const { return tiempo_ejecucion; }
};

#endif
/**
 * Enrique Manuel Pedroza Castillo
 * Alu0100886351
 * Clase set, que guarda conjunto de numeros permitiendo aplicar sobre los mismos operaciones de 
 * union, diferencia, interseccion y complementacion
*/

#include <vector>
#include <iostream>
#include <fstream>
#ifndef SET_H
#define SET_H

class Set {
 public:
  Set();    // constructor por defecto
  Set(int); // constructor parametrizado con un entero que indica el tamaño de elementos inicial

  void Insert(int);   // metodo para insertar un valor entero dentro del conjunto
  void Delete(int);   // metodo para eliminar un valor entero dentro del conjunto
  void Clean();       // metodo para limpiar los valores del vector e inicializarlos a 0
  bool IsEmpty();     // metodo para saber si el conjunto esta vacio
  bool IsInside(int);   // metodo para saber si un numero entero dado esta dentro del conjunto

  friend bool operator==(const Set&, const Set&);
  friend Set operator+(const Set&, const Set&);
  friend Set operator-(const Set&, const Set&);
  friend Set operator*(const Set&, const Set&);
  friend Set operator!(const Set&);
  void operator=(const Set& a) {
    this->elementos = a.elementos;
    this->Max = a.Max;
  }
  std::vector<int> ElementosDecimales() const;    // metodo para obtener el conjunto de decimales representados dentro del conjunto
  std::vector<long> GetElementos();               // metodo para obtener los elementos long dentro del conjunto
  int CalcularSizeVector(int);                    // metoo para calcular el tamaño del vector inicial especificando un valor entero
  void Imprimir(std::fstream& Out);               // metodo para imprimir en un fichero el conjunto

 private:
  std::vector<long> elementos;
  int Max;
};

#endif

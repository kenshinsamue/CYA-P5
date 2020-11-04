#include "set_calculator.h"

// Metodo para leer los conjuntos del fichero y devolverlos
// estructurados dentro de un verctor de strings
std::vector<std::string> LeerFichero(std::fstream& Entrada) {
  std::string linea;
  std::vector<std::string> conjunto;
  std::string caracter;
   while (linea.back() != '}') {
    Entrada >> linea;
    if (linea.front() == '{') {
      linea.erase(0, 1);
    }
     caracter = linea;
     caracter.erase(caracter.size() - 1, 1);
     conjunto.push_back(caracter);
   }
  return conjunto;
}
// Metodo para crear la instancia de Set, basandose en
// el vector de strings
void OperarConjuntos(std::fstream& In, Set& conjunto) {
  std::vector<int> elementos;
  std::vector<std::string> cadenas;
  cadenas = LeerFichero(In);
  for (auto i : cadenas) {
    elementos.push_back(stoi(i));
  }
  for (auto i : elementos) conjunto.Insert(i);
}
//Metodo para escribir el resultado de la operacion binaria entre 
// los Sets "a" y "b" y escribirlos en el fichero de salida especificado
void GuardarResultado(Set a, Set b, std::string operador, Set r,
                      std::fstream& output) {
  a.Imprimir(output);
  output << " " << operador << " ";
  b.Imprimir(output);
  output << " = ";
  r.Imprimir(output);
  output << std::endl;
}
// metodo para escribir en el fichero de salida la operacion especificada
// entre los Sets "a" y "b" para la comparacion
void GuardarResultado(Set a, Set r, std::string operador,
                      std::fstream& output) {
  output << operador << " ";
  a.Imprimir(output);
  output << " = ";
  r.Imprimir(output);
  output << std::endl;
}

//Metodo para escribir en el fichero de salida la operacion unaria de 
//Complementacion
void GuardarResultado(Set a, Set b, std::string operador, bool igualdad,
                      std::fstream& output) {
  a.Imprimir(output);
  output << " " << operador << " ";
  b.Imprimir(output);
  output << " = ";
  if (igualdad == true) {
    output << "Los conjuntos son iguales" << std::endl;
  } else {
    output << "Los conjuntos no son iguales" << std::endl;
  }
}
Set ResutladoOperacion(Set a, Set b, std::string operador) {
  Set resultado;
  if (operador == "+") resultado = a + b;
  if (operador == "-") resultado = a - b;
  if (operador == "*") resultado = a * b;
  return resultado;
}
int main(int arcg, char* argv[]) {
  if (arcg == 3) {
    std::fstream input;
    std::fstream output;
    input = std::fstream(argv[1], std::fstream::in);
    output = std::fstream(argv[2], std::fstream::out);
    if (input.is_open() && output.is_open()) {
      Set set1,set2,set3;
      std::string operador;
      std::string caracter;
      char cara;
      while (!input.eof()) {
        input >> (cara);
        if (cara == '{') {
          OperarConjuntos(input, set1);
          input >> operador;
          OperarConjuntos(input, set2);
          if (operador != "==") {
            set3 = ResutladoOperacion(set1, set2, operador);
            GuardarResultado(set1, set2, operador, set3, output);
          } else {
            GuardarResultado(set1, set2, operador, (set1 == set2), output);
          }
        } 
        if (cara == '!') {
            operador = caracter;
            OperarConjuntos(input, set1);
            set2 = !set1;
            GuardarResultado(set1, set2, operador, output);
        }
        
        set1.Clean();set2.Clean();set3.Clean();
      }
    } else {
      std::cout << "Error al abrir los ficheros" << std::endl;
    }
  } else {
    std::cout << "This program is a set calculator, which supports operations between sets of characters."<<std::endl;
    std::cout<<"It requires two parameters indicating the names for the input and output files."<<std::endl;
    std::cout<<" Usage: ./set_calculator input.txt output.txt"<< std::endl;
  }
}

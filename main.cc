#include <iostream>
#include <fstream>
#include "set_calculator.h"

std::vector <std::string> LeerFichero(std::fstream& Entrada){
  std::string linea;
  std::vector <std::string> conjunto;
  std::string caracter;
  while(linea.back() != '}'){
    Entrada>>linea;
    if(linea.front() == '{'){
      linea.erase(0,1);
    }
    caracter=linea;
    caracter.erase(caracter.size()-1,1);
    conjunto.push_back(caracter);
  }
  return conjunto;
}

void OperarConjuntos(std::fstream& In,Set& conjunto){
  std::vector<int> elementos;
  std::vector<std::string> cadenas;
  cadenas = LeerFichero(In);  
  for(auto i: cadenas){
    elementos.push_back(stoi(i));
  }
  for(auto i: elementos)
    conjunto.Insert(i);
}
void GuardarResultado(Set a, Set b, std::string operador, Set r,std::fstream& output){
      a.Imprimir(output);
      output<<" "<<operador<<" ";
      b.Imprimir(output);
      output<<" = ";
      r.Imprimir(output);
      output<<std::endl;
}
void GuardarResultado(Set a,Set r,std::string operador,std::fstream& output ){
  output<<operador<<" ";
  a.Imprimir(output);
  output<<" = ";
  r.Imprimir(output);
  output<<std::endl;
}
void GuardarResultado(Set a, Set b,std::string operador,bool igualdad,std::fstream& output){
      a.Imprimir(output);
      output<<" "<<operador<<" ";
      b.Imprimir(output);
      output<<" = ";
      if(igualdad==true){
        output<<"Los conjuntos son iguales"<<std::endl;
      }
      else{
        output<<"Los conjuntos no son iguales"<<std::endl;
      }
}
Set ResutladoOperacion (Set a, Set b ,std::string operador){
  Set resultado;
  if(operador == "+")
    resultado = a + b;
  if(operador == "-")
    resultado = a - b;
  if(operador == "*")
    resultado = a*b; 
  return resultado;
}
int main(int arcg, char *argv[]){
  if(arcg==3){
    std::fstream input;
    std::fstream output;
    input = std::fstream(argv[1],std::fstream::in);
    output = std::fstream(argv[2],std::fstream::out);
    if(input.is_open() && output.is_open()){
       Set set1; 
       Set set2;
       Set set3;
       std::string operador;   
       std::string caracter;
       while(!input.eof()){
          set1.Clean();
          set2.Clean();
          set3.Clean();
          input>>(caracter);
          if(caracter=="{"){
            OperarConjuntos(input,set1);
            input>>operador;            
            OperarConjuntos(input,set2);
            if(operador!= "=="){
              set3 = ResutladoOperacion(set1,set2,operador);
              GuardarResultado(set1,set2,operador,set3,output);
            }
            else{
              GuardarResultado(set1,set2,operador,(set1==set2),output);
            }
          }
          else{
            if(caracter=="!"){
              operador = caracter;
              OperarConjuntos(input,set1);
              set2 = !set1;
              GuardarResultado(set1,set2,operador,output);
            }
          }
       }        
    }
    else{
      std::cout<<"Error al abrir los ficheros"<<std::endl;
    }
  }
  else{
    std::cout<<"Error, No se han especificado los argumentos correctamente"<<std::endl;
  }
}
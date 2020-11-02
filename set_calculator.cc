#include "set_calculator.h"


Set::Set(){
  Max = sizeof(long)*8;
  Max--;
  long variable =0;
  elementos.push_back(variable);
}

Set::Set(int longitud){
  Max=longitud;
  Max--;
  long variable;
  for(int i=0;i<CalcularSizeVector(longitud);i++){  
    variable = 0;
    elementos.push_back(variable);       
  }
}

void Set::Clean(){
  for(auto i :elementos){
    i=0;
  }
}
bool Set::IsEmpty(){
  bool resultado = true;
  for(int i=0;i< elementos.size() && resultado==true;i++)
    if(elementos[i]!=(long)0)
      resultado=false;
  return resultado;
}

bool Set::IsInside(int numero){
  if(numero <=Max){
    int indice = numero/(sizeof(long)*8);
    int bit = numero%(sizeof(long)*8);
    long number = 1;
    number = number<<bit;
    long resultado = (elementos[indice])&(number);
    return (resultado == number);
  }
  else{
    return false;
  }
}

void Set::Insert(int numero){
  if(numero>Max){
    std::cout<<"Error, el numero no es representable"<<std::endl;
    exit(0);
  }
  else{
    int indice = numero/(sizeof(long)*8);
    int bit = numero%(sizeof(long)*8);
    long number = 1;
    number = number<<bit;
    elementos[indice] = (elementos[indice])|(number);
  }
}
void Set::Delete(int numero){

    int indice = numero/(sizeof(long)*8);
    int bit = numero%(sizeof(long)*8);
    long number = 1;
    number = ~(number<<bit);
    elementos[indice] = (elementos[indice])&(number);
}

void Set::Imprimir(std::fstream& Out){
  std::vector<int> valores = ElementosDecimales();
  std::string salida;
  salida= salida+"{";
  for(auto i : valores){
    salida= salida +(std::to_string(i)+", ");
  }
  salida.erase(salida.size()-2,2);
  salida= salida+"}";
  Out<<salida;
}
int Set::CalcularSizeVector(int n_elementos){
  int size = sizeof(long);
  size = size * 8;
  size = n_elementos / size; 
  size++;
  return(size);
}

void Set::SetId(std::string id){Id=id;}

std::string Set::GetId(){return Id;}
void Set::SetElementos(std::vector<long> elementos_nuevos){
  elementos = elementos_nuevos;
}

std::vector<int> Set::ElementosDecimales()const{
  std::vector<int> decimales;
  for(int j=elementos.size()-1;j>=0;j--){
    long n = elementos[j]; 
    for (int i = (8*sizeof(long))-1; i >= 0; i--) { 
      long k = n >> i; 
      if (k & 1){
        decimales.push_back(i+(j*8*sizeof(long)));
      }   
    }
  }
  return decimales;
}

Set operator + (const Set &a,const Set &b){
  
  std::vector<int> vector_a = a.ElementosDecimales();
  std::vector<int> vector_b = b.ElementosDecimales();
  Set tmp;
   if(a.Max == 63 && b.Max==63){
     tmp = Set();
  }
  else{
    if(a.Max > b.Max )
      tmp = Set(a.Max+1);
    else
      tmp = Set(b.Max+1);
  }
  tmp.SetId(a.Id + b.Id);
  for(auto i:vector_a)
    tmp.Insert(i);
  for(auto i:vector_b)
    tmp.Insert(i);
  return tmp;
}

Set operator - (const Set &a,const Set &b){
  Set tmp = a;
  std::vector<int> vector_b = b.ElementosDecimales();
  for(auto i: vector_b){
    tmp.Delete(i);
  }
  return tmp;
}

Set operator * (const Set &a,const Set &b){
  std::vector<int> vector_a = a.ElementosDecimales();
  std::vector<int> vector_b = b.ElementosDecimales();
  std::vector<int> vector_r ;
  Set tmp;
  Set aux_a = a;
  Set aux_b = b;
  for(auto i :vector_a){
    if(aux_b.IsInside(i)){
      vector_r.push_back(i);
    }
  }
  for(auto i :vector_b){
    if(aux_a.IsInside(i)){
      vector_r.push_back(i);
    }
  }
  for(auto i:vector_r){
    tmp.Insert(i);
  }
  return tmp;
}

Set operator ! (const Set &a){
  Set aux = a;
  int maximo =aux.CalcularSizeVector(a.Max +1)*sizeof(long)*8; 
  Set limite(maximo);
  for(int i = 0;i<maximo;i++){
    limite.Insert(i);
  }
  aux = limite - aux;
  for(int i=a.Max+1;i<maximo;i++){
    aux.Delete(i);
  }
  return aux;
}

bool operator == (const Set &a,const Set &b){
  bool igual = true;
  Set primero =a;
  Set segundo =b;
  if(primero.elementos.size()==segundo.elementos.size()){
    for(auto i:primero.elementos){
      if(segundo.IsInside(i)==false){
        igual = false;
        break;
      }
    }
    for(auto i:segundo.elementos){
      if(primero.IsInside(i)==false){
        igual = false;
        break;
      }
    }
    return igual;
  }
  else{
    return false;
  }
  return true;
}
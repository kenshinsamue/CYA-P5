#ifndef SET_H
#define SET_H
#include <vector>
#include <iostream>
#include <fstream>
class Set{

  public:
    
    Set();
    Set(int);
    
    void Insert(int);
    void Delete(int);
    void Clean();
    bool IsEmpty();
    bool IsInside(int);

    friend bool operator == (const Set&,const Set&);
    friend Set operator + (const Set&,const Set&);
    friend Set operator - (const Set&,const Set&);
    friend Set operator * (const Set&,const Set&);
    friend Set operator ! (const Set&);
    void operator = (const Set& a){
      this->Id=a.Id;
      this->elementos=a.elementos;
      this->Max = a.Max;
    }
    std::vector<int> ElementosDecimales()const;

    int CalcularSizeVector(int);
    void SetId (std::string);
    std::string GetId();
    void SetElementos(std::vector<long>);

    void Imprimir(std::fstream& Out);
    
  private:
    std::vector<long> elementos;
    int Max; 
    std::string Id;
    
};

#endif
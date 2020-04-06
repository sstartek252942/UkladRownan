#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "rozmiar.h"
#include "Wektor.hh"
#include <iostream>


enum MetodaWyznacznika {laplace, gauss, sarrus};


class Macierz {
  Wektor array[ROZMIAR]; //Program dziala na macierzach pionowych

  double dopelnienie(int x, int y) const;

  public: 
  Macierz();
  Macierz(Wektor A, Wektor B, Wektor C);
  //Macierz(const Macierz & M2);

  const Wektor & operator[] (int index) const;
  Wektor & operator[] (int index);

  Macierz operator + (const Macierz & B) const;
  Macierz operator - (const Macierz & B) const;
  Macierz operator * (const Macierz & B) const;

  Macierz operator * (double B) const;
  Wektor  operator * (const Wektor & W) const;

  bool operator == (const Macierz & W2) const;
  bool operator != (const Macierz & W2) const;
  
  Macierz SwapLineVertical(int w1, int w2) const;
  Macierz SwapLineHorizontal(int w1, int w2) const;

  Macierz transponuj() const;
  Macierz odwroc() const;
  double Wyznacznik(MetodaWyznacznika metoda = sarrus) const;

  

};


std::istream& operator >> (std::istream &Strm, Macierz &Mac);

std::ostream& operator << (std::ostream &Strm, const Macierz &Mac);

Macierz operator *(double B, const Macierz M);

//Macierz MacierzJednostkowa();

#endif

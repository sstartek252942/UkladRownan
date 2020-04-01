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
  Macierz(const Macierz & M2);

  const Wektor  & operator[] (int index) const;
  Wektor & operator[] (int index);

  const Macierz operator +(const Macierz & B) const;
  const Macierz operator -(const Macierz & B) const;
  const Macierz operator *(const Macierz & B) const;

  const Macierz operator *(double B) const;
  const Wektor operator *(const Wektor & W) const;

  bool operator == (const Macierz & W2) const;
  bool operator != (const Macierz & W2) const;
  
  const Macierz SwapLineVertical(int w1, int w2) const;
  const Macierz SwapLineHorizontal(int w1, int w2) const;

  const Macierz transponuj() const;
  const Macierz odwroc() const;
  double Wyznacznik(MetodaWyznacznika metoda = sarrus) const;

  

};


/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::istream& operator >> (std::istream &Strm, Macierz &Mac);

/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::ostream& operator << (std::ostream &Strm, const Macierz &Mac);

const Macierz operator *(double B, const Macierz M);

//Macierz MacierzJednostkowa();

#endif

#ifndef WEKTOR_HH
#define WEKTOR_HH

#include "rozmiar.h"
#include <iostream>


/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
class Wektor {
  double array[ROZMIAR];


  public: 
  Wektor();
  Wektor(double xx,double yy,double zz);
  Wektor(double *tab);
  Wektor(const Wektor & W2);

  const double & operator[] (int index) const;
  double & operator[] (int index);

  const Wektor operator + (Wektor const &Wek) const;
  const Wektor operator - (Wektor const &Wek) const;
  double operator * (Wektor const &Wek) const;
  const Wektor operator * (double const &a) const;

  double dlugosc() const;

  bool operator== (const Wektor & W2) const;
  bool operator!= (const Wektor & W2) const;
  const Wektor Swap(int w1, int w2) const;
};

Wektor operator*(double a, const Wektor & W2);
/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::istream& operator >> (std::istream &Strm, Wektor &Wek);

/*
 * To przeciazenie trzeba opisac. Co ono robi. Jaki format
 * danych akceptuje. Jakie jest znaczenie parametrow itd.
 * Szczegoly dotyczace zalecen realizacji opisow mozna
 * znalezc w pliku:
 *    ~bk/edu/kpo/zalecenia.txt 
 */
std::ostream& operator << (std::ostream &Strm, const Wektor &Wek);

#endif

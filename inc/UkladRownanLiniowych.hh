#ifndef UKLADROWNANLINIOWYCH_HH
#define UKLADROWNANLINIOWYCH_HH

#include <iostream>
#include "Wektor.hh"
#include "Macierz.hh"


enum MetodaUkladu {cramer, gaussjordan, odwrotna};

/*
 *  Tutaj trzeba opisac klase. Jakie pojecie modeluje ta klasa
 *  i jakie ma glowne cechy.
 */
class UkladRownanLiniowych {
  Macierz macierz;
  Wektor wektor;

  public:
  UkladRownanLiniowych(){};
  UkladRownanLiniowych(const Macierz & M, const Wektor & W);

  Wektor rozwiaz(MetodaUkladu metoda = cramer) const;

  const Wektor & getwektor() const;
  void setwektor(const Wektor & W);

  const Macierz & getmacierz() const;
  void setmacierz(const Macierz & M);
};


std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych &UklRown);

std::ostream& operator << ( std::ostream &Strm, const UkladRownanLiniowych &UklRown);


#endif

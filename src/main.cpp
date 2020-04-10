#include <iostream>
#include <iomanip>
#include "Wektor.hh"
#include "Macierz.hh"
#include "UkladRownanLiniowych.hh"
#include "rozmiar.h"


/*
 * Tu definiujemy pozostale funkcje.
 * Lepiej jednak stworzyc dodatkowy modul
 * i tam je umiescic. Ten przyklad pokazuje
 * jedynie absolutne minimum.
 */


int main()
{
  UkladRownanLiniowych   UklRown;   // To tylko przykladowe definicje zmiennej
  Wektor Wynik; bool ErrorWynik = false; Wektor Blad;

  std::cout << std::endl; 
  std::cin >> UklRown;
  if (!std::cin.good()){std::cerr<<ERRORLOAD<<std::endl<<std::endl; exit(0);}

  //std::cout << "Macierz A^T:" << std::endl; 
  //std::cout << UklRown.getmacierz().transponuj() << std::endl;
  //std::cout << "Macierz A:" << std::endl; 
  //std::cout << UklRown.getmacierz()<< std::endl;
  //std::cout << "Wektor B:" << std::endl; 
  //std::cout << UklRown.getwektor()<< std::endl;
  
  std::cout << std::endl;
  std::cout << "Wyznacznik - Sarrus:\t"  << UklRown.getmacierz().Wyznacznik(sarrus)  << std::endl;
  std::cout << "Wyznacznik - Laplace:\t" << UklRown.getmacierz().Wyznacznik(laplace) << std::endl;
  std::cout << "Wyznacznik - Gauss:\t"   << UklRown.getmacierz().Wyznacznik(gauss)   << std::endl;
  
  std::cout << std::endl;
  std::cout << "Uklad rownan" << std::endl << UklRown << std::endl<< std::endl;
  
  //Cramer
  try 
  {
     Wynik = UklRown.rozwiaz(cramer);
     ErrorWynik = false;
  }
  catch (int Error)
  {
    std::cout << "Cramer: " <<ERRORNOANSWER << std::endl;
    ErrorWynik = true;
  }
  if (!ErrorWynik)
  {
    Blad = UklRown.getmacierz() * Wynik - UklRown.getwektor();
    std::cout << "Rozwiazanie X1 X2 X3 - Cramer:" << std::endl << Wynik << std::endl;
    std::cout << "Wektor bledu - Cramer:" << std::endl << Blad << std::endl;
    std::cout << "Dlugosc wektor bledu - Cramer:" << std::endl << Blad.dlugosc() << std::endl<< std::endl;
    std::cout << std::endl;
  }

  //Gauss-Jordan
  try 
  {
     Wynik = UklRown.rozwiaz(gaussjordan);
     ErrorWynik = false;
  }
  catch (int Error)
  {
    std::cout << "Gauss-Jordan: "<< ERRORNOANSWER << std::endl;
    ErrorWynik = true;
  }
  if (!ErrorWynik)
  {
    Blad = UklRown.getmacierz() * Wynik - UklRown.getwektor();
    std::cout << "Rozwiazanie X1 X2 X3 - Gauss:" << std::endl << Wynik << std::endl;
    std::cout << "Wektor bledu - Gauss:" << std::endl << Blad << std::endl;
    std::cout << "Dlugosc wektor bledu - Gauss:" << std::endl << Blad.dlugosc() << std::endl;
    std::cout << std::endl<< std::endl;
  }

  //Macierz odwrotna
  try 
  {
     Wynik = UklRown.rozwiaz(odwrotna);
     ErrorWynik = false;
  }
  catch (int Error)
  {
    std::cout << "Macierz odwrotna: "<< ERRORNOANSWER << std::endl;
    ErrorWynik = true;
  }
  if (!ErrorWynik)
  {
    Blad = UklRown.getmacierz() * Wynik - UklRown.getwektor();
    std::cout << "Rozwiazanie X1 X2 X3 - Macierz odwrotna:" << std::endl << Wynik << std::endl;
    std::cout << "Wektor bledu - Macierz odwrotna:" << std::endl << Blad << std::endl;
    std::cout << "Dlugosc wektor bledu - Macierz odwrotna:" << std::endl << Blad.dlugosc() << std::endl<< std::endl;
  }
}

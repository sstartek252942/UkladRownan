#include <iostream>
#include <iomanip>
#include "Wektor.hh"
#include "Macierz.hh"
#include "UkladRownanLiniowych.hh"



/*
 * Tu definiujemy pozostale funkcje.
 * Lepiej jednak stworzyc dodatkowy modul
 * i tam je umiescic. Ten przyklad pokazuje
 * jedynie absolutne minimum.
 */


int main()
{
  UkladRownanLiniowych   UklRown;   // To tylko przykladowe definicje zmiennej

  /*Macierz M1,M2;
  std::cin >> M1;
  M2 = M1;
  M1 = M1.transponuj();
  std::cout << "Macierz A1:"<< std::endl << M1 << std::endl;
  std::cout << "Macierz A2:"<< std::endl << M2 << std::endl;*/

  std::cout << std::endl << " Start programu " << std::endl << std::endl;
  std::cin >> UklRown;
  std::cout << "Macierz A^T:" << std::endl; 
  std::cout << UklRown.getmacierz().transponuj() << std::endl;
  std::cout << "Macierz A:" << std::endl; 
  std::cout << UklRown.getmacierz()<< std::endl;

  std::cout << "Wektor[0]:" << UklRown.getmacierz()[0] << std::endl;
  std::cout << "Wektor[1]:" << UklRown.getmacierz()[1] << std::endl;
  std::cout << "Wektor[2]:" << UklRown.getmacierz()[2] << std::endl;

  std::cout << std::endl;
  std::cout << "Wyznacznik - Sarrus:\t" << UklRown.getmacierz().Wyznacznik() << std::endl;
  std::cout << "Wyznacznik - Laplace:\t" << UklRown.getmacierz().Wyznacznik() << std::endl;
  std::cout << "Wyznacznik - Gauss:\t" << UklRown.getmacierz().Wyznacznik() << std::endl;

  std::cout << std::endl;
  std::cout << "Wektor wyrazow wolnych b:" << std::endl;  
  std::cout << UklRown.getwektor() << std::endl;
  
  std::cout << std::endl;
  std::cout << "Uklad rownan" << std::endl << UklRown << std::endl;
  
  Wektor Blad;

  std::cout << std::endl;
  Blad = UklRown.getmacierz() * UklRown.rozwiaz() - UklRown.getwektor();
  std::cout << "Rozwiazanie X1 X2 X3 - Cramer:" << std::endl << UklRown.rozwiaz() << std::endl;
  std::cout << "Wektor bledu - Cramer:" << std::endl << Blad << std::endl;
  std::cout << "Dlugosc wektor bledu - Cramer:" << std::endl << Blad.dlugosc() << std::endl;
  
  std::cout << std::endl;
  Blad = UklRown.getmacierz() * UklRown.rozwiaz(gaussjordan) - UklRown.getwektor();
  std::cout << "Rozwiazanie X1 X2 X3 - Gauss:" << std::endl << UklRown.rozwiaz(gaussjordan) << std::endl;
  std::cout << "Wektor bledu - Gauss:" << std::endl << Blad << std::endl;
  std::cout << "Dlugosc wektor bledu - Gauss:" << std::endl << Blad.dlugosc() << std::endl;

  std::cout << std::endl;
  Blad = UklRown.getmacierz() * UklRown.rozwiaz(odwrotna) - UklRown.getwektor();
  std::cout << "Rozwiazanie X1 X2 X3 - Macierz odwrotna:" << std::endl << UklRown.rozwiaz(odwrotna) << std::endl;
  std::cout << "Wektor bledu - Macierz odwrotna:" << std::endl << Blad << std::endl;
  std::cout << "Dlugosc wektor bledu - Macierz odwrotna:" << std::endl << Blad.dlugosc() << std::endl;

  
}

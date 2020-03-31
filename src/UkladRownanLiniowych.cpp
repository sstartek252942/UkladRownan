#include "UkladRownanLiniowych.hh"
#include <iomanip>

//************Konstruktory************//
UkladRownanLiniowych::UkladRownanLiniowych()
{
  //this->macierz.();
  //this->wektor.();
}

UkladRownanLiniowych::UkladRownanLiniowych(const Macierz & M, const Wektor & W)
{
  this->macierz = M;
  this->wektor = W;
}

//************Metody:Getter i Setter************//
const Wektor & UkladRownanLiniowych::getwektor() const
{
   return wektor;
}
void UkladRownanLiniowych::setwektor(const Wektor & W)
{
  this->wektor = W;
}

const Macierz & UkladRownanLiniowych::getmacierz() const
{
  return macierz;
}

void UkladRownanLiniowych::setmacierz(const Macierz & M)
{
  this->macierz = M;
}

//************Metody: Rozwiaz************//
const Wektor UkladRownanLiniowych::rozwiaz(MetodaUkladu metoda) const
{
  Macierz M2(this->macierz);
  Wektor wynik(this->wektor);

  switch (metoda){

  case cramer:
    double W,WX,WY,WZ;
    W = M2.Wyznacznik();

    M2[0] = wektor;
    WX = M2.Wyznacznik();
    
    M2[0] = macierz[0];
    M2[1] = wektor;
    WY = M2.Wyznacznik();
    
    M2[1] = macierz[1];
    M2[2] = wektor;
    WZ = M2.Wyznacznik();

    if (W != 0)
    {
      wynik[0] = WX/W; wynik[1] = WY/W; wynik[2] = WZ/W;
      return wynik;
    }
    //else if (WX !=0 || WY != 0 || WZ != 0) std::cerr << "Uklad sprzeczny" << std::endl;
    else std::cerr << ERRORNOANSWER << std::endl;
    exit(1);

  case gaussjordan:
    M2 = M2.transponuj();

    //*****pierwsza kolumna*****//
    if (M2[0][0] == 0) {if (M2[1][0] == 0) {if (M2[2][0] == 0) {std::cerr << ERRORNOANSWER << std::endl; exit(0);}
                                          else {M2 = M2.SwapVertical(0,2); wynik = wynik.Swap(0,2);}}
                       else {M2 = M2.SwapVertical(0,1); wynik = wynik.Swap(0,1);}}

    wynik[1] = wynik[1] - wynik[0] * (M2[1][0] / M2[0][0]);	M2[1] = M2[1] - M2[0] * (M2[1][0] / M2[0][0]); 
    wynik[2] = wynik[2] - wynik[0] * (M2[2][0] / M2[0][0]);	M2[2] = M2[2] - M2[0] * (M2[2][0] / M2[0][0]); 
    
    //*****druga kolumna*****//
    if (M2[1][1] == 0) {if (M2[2][1] == 0) {std::cerr << ERRORNOANSWER << std::endl; exit(0);}
                       else {M2 = M2.SwapVertical(1,2); wynik = wynik.Swap(1,2);}}

    wynik[2] = wynik[2] - wynik[1] * (M2[2][1] / M2[1][1]);	M2[2] = M2[2] - M2[1] * (M2[2][1] / M2[1][1]); 

    
    //*****trzecia kolumna*****// 
    if (M2[2][2] == 0) {std::cerr << ERRORNOANSWER << std::endl; exit(0);}
    wynik[0] = wynik[0] - wynik[2] * (M2[0][2] / M2[2][2]);	M2[0] = M2[0] - M2[2] * (M2[0][2] / M2[2][2]); 
    wynik[1] = wynik[1] - wynik[2] * (M2[1][2] / M2[2][2]);	M2[1] = M2[1] - M2[2] * (M2[1][2] / M2[2][2]); 

    
    //*****druga kolumna*****//
    wynik[0] = wynik[0] - wynik[1] * (M2[0][1] / M2[1][1]);	M2[0] = M2[0] - M2[1] * (M2[0][1] / M2[1][1]); 

    
    //*****Rozwiazanie*****//
    wynik[0] = wynik[0]/M2[0][0]; 
    wynik[1] = wynik[1]/M2[1][1]; 
    wynik[2] = wynik[2]/M2[2][2];
    return wynik;
  
  case odwrotna:
    M2 = M2.transponuj().odwroc();
    wynik = M2 * this->wektor;
  return wynik;

  }
  std::cerr << ERROROUTOFENUM << std::endl;
  exit(0);
}


//************Funkcje: in/out************//
std::istream& operator >> (std::istream &Strm, UkladRownanLiniowych &UklRown)
{
  Wektor tempW;
  Macierz tempM;
  Strm >> tempM >> tempW;
  UklRown.setmacierz(tempM);
  UklRown.setwektor(tempW);
  return Strm; 
}


std::ostream& operator << ( std::ostream &Strm,  const UkladRownanLiniowych &UklRown)
{
  Macierz tempM(UklRown.getmacierz().transponuj());
  
  for (int i = 0; i < ROZMIAR; i++)
  Strm <<  " |" << tempM[i] << "| " << " |x_" << i+1 << "|"<< std::setw(2) << (i==1?'=':' ') << std::setw(2) << "|" << std::setw(SKIP) << UklRown.getwektor()[i] << "|" << std::endl;
  return Strm; 
}

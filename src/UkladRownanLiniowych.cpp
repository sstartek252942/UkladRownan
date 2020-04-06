#include "UkladRownanLiniowych.hh"
#include <iomanip>

//************Konstruktory************//
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
Wektor UkladRownanLiniowych::rozwiaz(MetodaUkladu metoda) const
{
  Macierz tempM2(this->macierz);
  Wektor wynik;
  Wektor tempW2(wektor);

  switch (metoda){

  case cramer:
    double W;
    W = tempM2.Wyznacznik();


    for (int i = 0; i < ROZMIAR; i++)
    {
      tempM2[i] = wektor;
      wynik[i] = tempM2.Wyznacznik();
      tempM2[i] = macierz[i];
    }

    if (W != 0)
    {
      for (int i = 0; i < ROZMIAR; i++)
      {
        wynik[i] = wynik[i]/W;
      }
      return wynik;
    }
    //else if (WX !=0 || WY != 0 || WZ != 0) std::cerr << "Uklad sprzeczny" << std::endl;
    else std::cerr << ERRORNOANSWER << std::endl;
    exit(1);

  case gaussjordan:
    tempM2 = tempM2.transponuj();

    for (int i = 0; i < ROZMIAR-1; i++)
    {
      //podmienianie  
      bool flag = false;
      int j = i;        
      while (!flag && j < ROZMIAR)
      {
        if (tempM2[i][j] != 0)
        {
          if (i != j) 
          {
            tempM2 = tempM2.SwapLineVertical(i, j); //praca na macierzy tranponowanej, dlatego nie jest SwapLineHorizontal (tak jak by wynikalo na logike)
            tempW2 = tempW2.Swap(i,j);
          }
          flag = true;
        }
        j++;
      }
      //wyznacznik 0, bo nie da się podzielic i zostaly same zera
      if (!flag) {std::cerr << ERRORNOANSWER << std::endl; exit(0);}

      //odejmowanie, aby powstala macierz trojkatna
      for (int k = i+1; k < ROZMIAR; k++)
      {
        tempW2[k] = tempW2[k] - tempW2[i] * (tempM2[k][i] / tempM2[i][i]);	
        tempM2[k] = tempM2[k] - tempM2[i] * (tempM2[k][i] / tempM2[i][i]); 
      }
    }
    
    //sprawdzanie czy ostatni element ostatniego wiersza nie jest rowny 0, co oznaczaloby, ze caly ostatni wiersz jest 0
    if (tempM2[ROZMIAR-1][ROZMIAR-1] == 0) {std::cerr << ERRORNOANSWER << std::endl; exit(0);}
    
    for (int i = ROZMIAR-1; i > 0; i--)
    {
      //odejmowanie, aby powstala macierz diagonalna
      for (int k = i-1; k >= 0; k--)
      {
        tempW2[k] = tempW2[k] - tempW2[i] * (tempM2[k][i] / tempM2[i][i]);	
        tempM2[k] = tempM2[k] - tempM2[i] * (tempM2[k][i] / tempM2[i][i]); 
      }
    }
    
    //*****Rozwiazanie*****//
    for (int i = 0; i < ROZMIAR; i++)
    {
      wynik[i] = tempW2[i]/tempM2[i][i]; 
    }
    return wynik;
  
  case odwrotna:
    tempM2 = tempM2.odwroc();
    wynik = tempM2 * wektor;
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

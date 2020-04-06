#include "Macierz.hh"
#include <iomanip>

//************Konstruktory************//
Macierz::Macierz()
{
  for (int j = 0; j < ROZMIAR; j++)
    for (int i = 0; i < ROZMIAR; i++)
       this->array[i][j] = 0;
}

/*Macierz::Macierz(const Macierz & M2)
{
  for (int i=0; i<ROZMIAR; i++)
  (*this)[i] = M2[i];
}*/

Macierz::Macierz(Wektor A, Wektor B, Wektor C)
{
  (*this)[0] = A;
  (*this)[1] = B;
  (*this)[2] = C;
}

//************Metody:Getter i Setter************//
const Wektor & Macierz::operator[] (int index) const
{
  if (index < 0 || index >= ROZMIAR) 
  {
    std::cerr << ERROROUTOFBOUNDS << std::endl;
    exit(1);
  }
  return this->array[index];
}

Wektor & Macierz::operator[] (int index)
{
  if (index < 0 || index >= ROZMIAR) 
  {
    std::cerr << ERROROUTOFBOUNDS << std::endl;
    exit(1);
  }
  return this->array[index];
}

//************Metody operatorow arytmetycznych************//
Macierz Macierz::operator + (const Macierz & M2) const
{
  Macierz temp;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    temp[i] = (*this)[i] + M2[i];
  }
  return temp;
}

Macierz Macierz::operator - (const Macierz & M2) const
{
  Macierz temp;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    temp[i] = (*this)[i] - M2[i];
  }
  return temp;
}

Macierz Macierz::operator * (const Macierz & M2) const
{
  Macierz M1T((*this).transponuj());
  Macierz temp;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    for (int j = 0; j < ROZMIAR; j++)    
    {
        temp[j][i] += M1T[j] * M2[i];
        //std::cout << (*this)[j] * M2T[i] << std::endl;
    }
  }
  return temp;
}

Macierz Macierz::operator * (double a) const 
{
  Macierz temp;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    temp[i] = (*this)[i] * a;
  }
  return temp;
}

bool Macierz::operator == (const Macierz & M2) const
{
  bool flag = true;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    if ((*this)[i] != M2[i])
    flag = false;
  }
  return flag;
}

bool Macierz::operator != (const Macierz & M2) const
{
  return !(*this==M2);
}
  
Macierz Macierz::transponuj() const
{
  Macierz M2;
  for (int j = 0; j < ROZMIAR; j++)
    for (int i = 0; i < ROZMIAR; i++)
        M2[j][i]= (*this)[i][j];
  
  return M2;
}

Wektor Macierz::operator * (const Wektor & W) const
{
  Wektor tempW;
  for (int i = 0; i < ROZMIAR; i++)    
  {
    for (int j = 0; j < ROZMIAR; j++)    
    {
      tempW[i] += (*this)[j][i] * W[j];
      //std::cout << (*this)[j][i] << " " << W[j] << std::endl;
    }
  }
  return tempW;
}

double Macierz::dopelnienie(int x, int y) const
{
  double temp;
  if (x < 0 || x >= ROZMIAR || y < 0 || y >= ROZMIAR)
  {
    std::cerr << ERROROUTOFBOUNDS << std::endl;
    exit(1);
  }
 
  temp = (*this)[(x+1)%ROZMIAR][(y+1)%ROZMIAR] * (*this)[(x+2)%ROZMIAR][(y+2)%ROZMIAR] - (*this)[(x+2)%ROZMIAR][(y+1)%ROZMIAR] * (*this)[(x+1)%ROZMIAR][(y+2)%ROZMIAR];
  return temp;
}

Macierz Macierz::odwroc() const
{
  Macierz M2;
  double Wyznacznik = (*this).Wyznacznik();
  if (Wyznacznik != 0){
  for (int j = 0; j < ROZMIAR; j++)
    for (int i = 0; i < ROZMIAR; i++)
        M2[i][j] = (*this).dopelnienie(i,j) / Wyznacznik;
  }
  return M2.transponuj();
}

double Macierz::Wyznacznik(MetodaWyznacznika metoda) const //sarrus, laplace, gauss
{
  double temp = 0;
  switch(metoda){
  case sarrus:		//Macierz 3x3
    for (int i = 0; i < ROZMIAR; i++)
      temp += (*this)[i % ROZMIAR][0] * (*this)[(i+1) % ROZMIAR][1] * (*this)[(i+2) % ROZMIAR][2];
    for (int i = 0; i < ROZMIAR; i++)
      temp -= (*this)[i % ROZMIAR][0] * (*this)[(i+2) % ROZMIAR][1] * (*this)[(i+1) % ROZMIAR][2];
    return temp;

  case laplace:		//Macierz 3x3, dla innych trzeba poprawić dopelnienie
    for (int i = 0; i < ROZMIAR; i++)
    temp += (*this)[i][0] * ((*this).dopelnienie(i,0));
    return temp;
  
  case gauss: //Macierz dowolna
    Macierz tempMacierz(*this);
    temp = 1;
    for (int i = 0; i < ROZMIAR-1; i++)
    {
      //podmienianie  
      bool flag = false;
      int j = i;        
      while (!flag && j < ROZMIAR)
      {
        if (tempMacierz[i][j] != 0)
        {
          if (i != j) 
          {
            tempMacierz = tempMacierz.SwapLineVertical(i, j);
            temp *= -1;
          }
          flag = true;
        }
        j++;
      }
      //wyznacznik 0, bo nie da się podzielic i zostaly same zera
      if (!flag) return 0;

      //odejmowanie
      for (int k = i+1; k < ROZMIAR; k++)
      {
        tempMacierz[k] = tempMacierz[k] - tempMacierz[i] * (tempMacierz[k][i] / tempMacierz[i][i]);
      }
    }
    
    for (int i = 0; i < ROZMIAR; i++)
    {
      temp *= tempMacierz[i][i];
    }
    //tempMacierz[1] = tempMacierz[1] - tempMacierz[0] * (tempMacierz[1][0] / tempMacierz[0][0]);
    //tempMacierz[2] = tempMacierz[2] - tempMacierz[0] * (tempMacierz[2][0] / tempMacierz[0][0]);
    //tempMacierz[2] = tempMacierz[2] - tempMacierz[1] * (tempMacierz[2][1] / tempMacierz[1][1]);

    return temp;
  }
  std::cerr << ERROROUTOFENUM << std::endl;
  exit(0);
}

Macierz Macierz::SwapLineHorizontal(int w1, int w2) const
{
  Macierz M2((*this).transponuj());
  if (w1 < 0 || w1 >= ROZMIAR || w2 < 0 || w2 >= ROZMIAR)
  {
    std::cerr << ERROROUTOFBOUNDS << std::endl;
    exit(1);
  }
 
  Wektor tempW(M2[w1]);
  M2[w1] = M2[w2];
  M2[w2] = tempW;
  M2 = M2.transponuj();
  return M2;
}

Macierz Macierz::SwapLineVertical(int w1, int w2) const
{
  Macierz M2(*this);
  if (w1 < 0 || w1 >= ROZMIAR || w2 < 0 || w2 >= ROZMIAR)
  {
    std::cerr << ERROROUTOFBOUNDS << std::endl;
    exit(1);
  }
 
  Wektor tempW(M2[w1]);
  M2[w1] = M2[w2];
  M2[w2] = tempW;
  return M2;
}

//************Funkcje mnozenia************//
Macierz operator *(double a, const Macierz M)
{
  return M*a;
}

//************Funkcje: in/out************//
std::istream& operator >> (std::istream &Strm, Macierz &Mac)
{
  for (int i = 0; i < ROZMIAR; i++)
  { 
    Strm>>Mac[i];
  }
  return Strm;
}


std::ostream& operator << (std::ostream &Strm, const Macierz &Mac)
{
  for (int i = 0; i < ROZMIAR; i++)
  {
     for (int j = 0; j < ROZMIAR; j++)
     {
       Strm << std::setw(SKIP) << Mac.transponuj()[i][j];
     }
   Strm  << std::endl;
  }
  return Strm;
}



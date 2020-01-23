#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

//*******************************
//** Tutaj definiujemy funkcję **
//*******************************

double f(double x)
{
  return sqrt(1-(x*x));
}

//********************
//** Program główny **
//********************

int main()
{
  int N; //liczba punktów/prostokątów podziałowych
  double a,b,s,h;
  int i;

  cout << setprecision(3)      // 3 cyfry po przecinku
       << fixed;               // format stałoprzecinkowy
  
  cout << "Podaj liczbe prostokatow podzialowych\n\n"
		  "N = ";
  cin >> N;
  
  if(N <= 0) {
	  cout<< "Liczba prostokatow podzialowych musi byc wieksza od zera [N > 0],\nuruchom program ponownie i wprowadz poprawne dane\n";
	  return -1;
  }
  
  cout << "Podaj poczatek przedzialu calkowania\n\n"
          "a = ";
  cin >> a;
  
  cout << "\nPodaj koniec przedzialu calkowania\n\n"
          "b = ";
  cin >> b;
  
  if(a >= b) {
	cout << "Poczatek przedzialu musi byc mniejszy niz koniec [a < b],\nuruchom program ponownie i wprowadz poprawne dane\n";
	return -1;
  }
	  
  if(a > 1 || b > 1) {
	cout << "Wynik nie jest liczbą rzeczywistą, gdy [a,b > 1],\nuruchom program ponownie i wprowadz poprawne dane\n";
	return -1;
  }
  
  cout << endl;

  #pragma omp parallel reduction (+:s) private(h)
  {
  s  = 0;
  h = (b - a) / N;

  #pragma omp for nowait
  for(i = 1; i <= N; i++) {
	  s += f(a + i * h);
  }
  s *= h;
  }
  cout << "Wartosc calki wynosi : " << setw(8) << s << endl << endl;
  return 0;
} 

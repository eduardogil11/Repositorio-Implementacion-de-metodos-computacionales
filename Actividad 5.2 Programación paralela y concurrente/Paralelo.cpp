// Correr con: g++ -o programa -fopenmp main.cpp
// Si se corre desde otro programa, hacerlo con g++ Paralelo.cpp -o program -fopenmp si se corre


//Librer�as
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <ctime>

//Librer�a especial para paralelizaci�n del programa
#include <omp.h>

using namespace std;


//Funci�n para verificar si el n�mero es primo
bool verificar_primo(int numero) {
	
	//Si el n�mero es menor a 2 devuelve falso, ya que no es un n�mero primo
	if (numero < 2) { 
		return false; 
	}
	
  //Si el n�mero es dos o m�s, revisara si es primo
	else {
    //Ciclo desde 2 hasta el cuadrado del numero
		for (int j = 2; j <= sqrt(numero); j++){ 
      //Si el numero es divisible de manera exacta entre j, no es primo, as� que devuelve falso
			if (numero%j == 0) {
				return false; 
			}		
		}
    //Termina el ciclo, as� que el n�mero es primo y devuelve verdadero
		return true;
	}
}

int main(int argc, char* argv[]) {

	//T�tulo y explicaci�n del programa
	cout << "\t\t Actividad 5.2: Programacion paralela y concurrente\n" <<endl;
	cout << "Version paralela" <<endl;
	cout << "Suma de numeros primos menores a 5,000,000\n" << endl;
	
	//Variables para guardar la suma de los n�meros primos y los tiempos de ejecucion
	long long suma = 0;
	unsigned t0, t1;
	
  //Guarda el tiempo en que se inicio el programa
	t0 = clock();
	
	//Define la regi�n paralela
  #pragma omp parallel
  {
    //Le dice a la parelizaci�n que trabajaremos con for y con la variable "suma" que se le estar� sumando
    #pragma omp parallel for reduction (+:suma)
    //ciclo para recorrer todos los n�mero menores a 5000000
    for(long long i = 0; i < 5000000; i++) {
      
      //Verifica si el n�mero es primo en la funci�n, si lo es, se va sumando a la variable "suma"
      if (verificar_primo(i)) {
        //Le dice a la paralelizaci�n que haga las sumas con precauci�n
        #pragma omp critical 
        suma += i;
      }
    }
  }
	
	//Imprime el resultado de la suma total
	cout << suma << endl;
	
  //Guarda el tiempo en que se acab� el programa
	t1 = clock();
	
  //calcula el tiempo de ejecuci�n del programa
	double time = (double(t1 - t0)/CLOCKS_PER_SEC);

  //Imprime el tiempo de ejecuci�n
	cout << "Tiempo de ejecucion: " << time << " s";
	
	return 0;
}

//Librerías
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;


//Función para verificar si el número es primo
bool verificar_primo(int numero) {
	
	//Si el número es menor a 2 devuelve falso, ya que no es un número primo
	if (numero < 2) { 
		return false; 
	}
	
  //Si el número es dos o más, revisara si es primo
	else {
    //Ciclo desde 2 hasta el cuadrado del numero
		for (int j = 2; j <= sqrt(numero); j++){ 
      //Si el numero es divisible de manera exacta entre j, no es primo, así que devuelve falso
			if (numero%j == 0) {
				return false; 
			}		
		} 
    //Termina el ciclo, así que el número es primo y devuelve verdadero
		return true;
	}
}

int main(int argc, char* argv[]) {

	//Título y explicación del programa
	cout << "\t\t Actividad 5.2: Programacion paralela y concurrente\n" <<endl;
	cout << "Version secuencial" <<endl;
	cout << "Suma de numeros primos menores a 5,000,000\n" << endl;
	
	//Variable para guardar la suma de los números primos y los tiempos de ejecucion
	long long suma = 0;
	unsigned t0, t1;
	
	//Guarda el tiempo en que se inicio el programa
  t0 = clock();

    //ciclo para recorrer todos los número menores a 5000000
    for(long long i = 0; i < 5000000; i++) {
      
      //Verifica si el número es primo en la función, si lo es, se va sumando a la variable "suma"
      if (verificar_primo(i)) {
        suma += i;
      }
    }
  
	
	//Imprime el resultado de la suma total
	cout << suma << endl;
	
  //Guarda el tiempo en que se acabó el programa
	t1 = clock();
	
  //calcula el tiempo de ejecución del programa
	double time = (double(t1 - t0)/CLOCKS_PER_SEC);

  //Imprime el tiempo de ejecución
	cout << "Tiempo de ejecucion: " << time << " s";
	
	return 0;
}

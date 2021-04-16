/*
 * main.cpp
 *
 *  Created on: 28/03/2021
 *      Author: Eduardo Rodríguez Gil
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

void lexerAritmetico(string archivo) { // Función principal
	
	// Lee el archivo
  ifstream texto;
  texto.open(archivo.c_str(), ios::in);

  // Variables
  string line;
  vector<char> token;
	vector<string> type, tipos, numeros;
	
	// Cada línea se guarda como un vector
	while(!texto.eof()) {
		getline(texto, line);
		tipos.push_back(line); 
	}
	
	texto.close(); // Cierra el archivo
	
	// Recorre el vector
	for(int i = 0; i < tipos.size(); i++) {
	for(int j = 0; j < tipos[i].size(); j++) {

    // Signo de suma
    if(tipos[i][j] == '+') {
      token.push_back(tipos[i][j]);
			type.push_back("SUMA");
			numeros.push_back("---");
      }

    // Signo de multiplicación
		else if(tipos[i][j] == '*') {
			token.push_back(tipos[i][j]);
			type.push_back("MULTIPLICATION");
			numeros.push_back("---");
			}

    // Signo de igual
		else if(tipos[i][j] == '=') {
			token.push_back(tipos[i][j]);
			type.push_back("ASSIGMENT");
			numeros.push_back("---");
			}
			
		// Signo de potencia
		else if(tipos[i][j] == '^') {
			token.push_back(tipos[i][j]);
			type.push_back("POWER");
			numeros.push_back("---");
			}
			
		// Paréntesis derecho
		else if(tipos[i][j] == ')') {
      token.push_back(tipos[i][j]);
			type.push_back("RIGHT PARENTHESIS");
			numeros.push_back("---");
			}	
			
		// Paréntesis izquierdo
		else if(tipos[i][j] == '(') {
			token.push_back(tipos[i][j]);
			type.push_back("LEFT PARENTHESIS");
			numeros.push_back("---");
			}
			
		else if(tipos[i][j] == '/') { // Checa las diagonales

		  // Comentario
		  if(tipos[i][j + 1] == '/') {
        break;
				}
				
			// Signo de división
      else {
				token.push_back(tipos[i][j]);
				type.push_back("DIVISION");
				numeros.push_back("---");
        }				
      }
		
			else if(tipos[i][j] == '-') { // Checa si es un simbolo negativo o signo de resta

				// Signo de resta
				if(tipos[i][j + 1] == ' ') {
					token.push_back(tipos[i][j]);
					type.push_back("SUBTRACTION");
					numeros.push_back("---");
          }
				
				// Checa si un número cuenta con e- o si el número es negativo
				else {
          string number = " ";
          for(int k = j; k < tipos[i].size(); k++) {
            if(tipos[i][j] == ' ') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
							break;
              }

            // El recorrido llega a un signo de suma
						if(tipos[i][j] == '+') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);

							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("SUMA");
							numeros.push_back("---");
							break;
              }
						
						// El recorrido llega a un signo de multiplicación
						if(tipos[i][j] == '*') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
							
							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("MULTIPLICATION");
							numeros.push_back("---");
							break;
						  }

            // El recorrido llega a un signo de potencia
						if(tipos[i][j] == '^'){
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);

							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("POWER");
							numeros.push_back("---");
							break;
						  }

						// El recorrido llega a un signo igual
						if(tipos[i][j] == '=') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
							
							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("ASSIGMENT");
							numeros.push_back("---");
							break;
              }						
						
						// El recorrido llega a un paréntesis derecho
						if(tipos[i][j] == ')') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
				
							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("RIGHT PARENTHESIS");
							numeros.push_back("---");
							break;
              }
						
						// El recorrido llega a un paréntesis izquierdo
						if(tipos[i][j] == '(') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
							
							// Fin del ciclo
							token.push_back(tipos[i][j]);
							type.push_back("|LEFT PARENTHESIS");
							numeros.push_back("---");
							break;
              }
						
						// El recorrido llega a una diagonal
						if(tipos[i][j] == '/') {
							token.push_back('0');
							type.push_back("REAL");
							numeros.push_back(number);
							
							// Revisa si es comentario
							if(tipos[i][j + 1] == '/') {
								break;
                }

							// Revisa si es un signo de división
							else if(tipos[i][j + 1] != '/') {
								token.push_back(tipos[i][j]);
								type.push_back("DIVISION");
								numeros.push_back("---");
                }
              break;
              }					
            number+=tipos[i][j];
            j++;
          }
					
					// El recorrido agrega los digitos
					if(j == tipos[i].size()) {
						token.push_back('0');
						type.push_back("REAL");
						numeros.push_back(number);
            }
          }
        }
			
			// Revisa en la lista si es un número
			else if((tipos[i][j] == ('0'))||(tipos[i][j] == ('1'))||(tipos[i][j] == ('2'))||(tipos[i][j] == ('3'))||(tipos[i][j] == ('4'))||(tipos[i][j] == ('5'))||(tipos[i][j] == ('6'))||(tipos[i][j] == ('7'))||(tipos[i][j] == ('8'))||(tipos[i][j] == ('9'))) {
        
				string save = " "; // Variable que guarda los digitos del número
				bool check = true; // Variable que comprueba si el número es entero o real

				// Recorrido que agrega los digitos de los números 
				for(int k = j; k < tipos[i].size(); k++) {
					if(tipos[i][j] == ' ') { // El recorrido encuentra un ' '

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {
              
							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
              }
						token.push_back('0');
						numeros.push_back(save);

						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						break;
            }

          if(tipos[i][j] == '+') { // El recorrido llega a un signo de suma

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un signo de suma en Token  y arroja un SUMA en Type
						token.push_back(tipos[i][j]);
						type.push_back("SUMA");
						numeros.push_back("---");
						break;
					  }
					
					
					if(tipos[i][j] == '*') { // El recorrido llega a un signo de multiplicación

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un signo de multiplicación en Token  y arroja un MULTIPLICATION en Type
						token.push_back(tipos[i][j]);
						type.push_back("MULTIPLICATION");
						numeros.push_back("---");
						break;
					  }
					 	
					if(tipos[i][j] == '=') { // El recorrido llega a un signo de igual

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un igual en Token  y arroja un ASSIGMENT en Type
						token.push_back(tipos[i][j]);
						type.push_back("ASSIGMENT");
						numeros.push_back("---");
						break;
					  }

          if(tipos[i][j] == '^') { // El recorrido llega a un signo de porcentaje

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un signo de porcentaje en Token  y arroja un POWER en Type
						token.push_back(tipos[i][j]);
						type.push_back("POWER");
						numeros.push_back("---");
						break;
					  }						
						
					if(tipos[i][j] == ')') { // El recorrido llega a un paréntesis derecho
						
            // Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un paréntesis derecho en Token  y arroja un RIGHT PARENTHESIS en Type
						token.push_back(tipos[i][j]);
						type.push_back("RIGHT PARENTHESIS");
						numeros.push_back("---");
						break;
					  }
					
					
					if(tipos[i][j] == '(') { // El recorrido llega a un paréntesis izquierdo
						
            // Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Arroja un paréntesis izquierda en Token  y arroja un  LEFT PARENTHESIS en Type
						token.push_back(tipos[i][j]);
						type.push_back("LEFT PARENTHESIS");
						numeros.push_back("---");
						break;
					}
						
					if(tipos[i][j] == '/') { // El recorrido llega a una diagonal

						// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
						
						// Revisa si es comentario
						if(tipos[i][j + 1] == '/') {
							break;
			        }

						// Revisa si es división
						else if(tipos[i][j + 1] != '/') {

							// Arroja un signo de división en Token  y arroja un  DIVISION en Type
							token.push_back(tipos[i][j]);
							type.push_back("DIVISION");
							numeros.push_back("---");
              }
						break;
					  }						
					save+=tipos[i][j];
					j++;					
				}
				
				// El recorrido agrega los digitos
				if(j == tipos[i].size()) {

					// Recorre los dígitos del número
						for(int n = 0; n < save.size(); n++) {

							// Si cuenta con una e, E o . se combierte en falso
							if((save[n] == 'e')||(save[n] == 'E')||(save[n] == '.')) {check = false;}					
						}
						token.push_back('0');
						numeros.push_back(save);
						
						// Si es verdadero type arroja INTEGERT y si es falso type arroja REAL
						if(check == true) {
              type.push_back("INTEGER");
              }					
						else {
              type.push_back("REAL");
              }
            }												
          }

			else {
				if(tipos[i][j] != ' ') { // Revisa si no es una variable
					string elements = " "; // Variable que guarda los elementos 
					
					// Recorre para agregar los elementos
					for(int k = j; k < tipos[i].size(); k++) {
						if(tipos[i][j] == ' ') { // El recorrido se encuentra un ' '
							// En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							break;
						  }
						
						if(tipos[i][j] == '=') { // El recorrido llega a un signo de igual

              // En Token se le agrega un 0 y arroja un VARIABLE en Type						
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un igual en Token  y arroja un ASSIGMENT en Type
							token.push_back(tipos[i][j]);
							type.push_back("ASSIGMENT");
							numeros.push_back("---");
							break;
						  }
						
						if(tipos[i][j] == ')') { // El recorrido llega a un paréntesis derecho

							// En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un paréntesis derecho en Token  y arroja un RIGHT PARENTHESIS en Type
							token.push_back(tipos[i][j]);
							type.push_back("RIGHT PARENTHESIS");
							numeros.push_back("---");
							break;
						  }
						
						if(tipos[i][j] == '(') { // El recorrido llega a un paréntesis izquierdo
							
              // En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un paréntesis izquierda en Token  y arroja un  LEFT PARENTHESIS en Type
							token.push_back(tipos[i][j]);
							type.push_back("LEFT PARENTHESIS");
							numeros.push_back("---");
							break;
						}
						
						// El recorrido llega a una diagonal
						if(tipos[i][j] == '/') {
							
              // En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Revisa si es comentario
							if(tipos[i][j + 1] == '/') {
                break;
							  }

							// Revisa si es división
							else if(tipos[i][j + 1] != '/') {
                
								// Arroja un signo de división en Token  y arroja un  DIVISION en Type
								token.push_back(tipos[i][j]);
								type.push_back("DIVISION");
								numeros.push_back("---");
							}
						break;
						}
						
						if(tipos[i][j] == '+') { // El recorrido llega a un signo de suma
							
              // En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un signo de suma en Token  y arroja un SUMA en Type
							token.push_back(tipos[i][j]);
							type.push_back("SUMA");
							numeros.push_back("---");
							break;
						  }
						
						if(tipos[i][j] == '*') { // El recorrido llega a un signo de multiplicación

							// En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un signo de multiplicación en Token  y arroja un MULTIPLICATION en Type
							token.push_back(tipos[i][j]);
							type.push_back("|MULTIPLICATION");
							numeros.push_back("---");
							break;
						  }
					
						if(tipos[i][j] == '-') { // El recorrido llega a un signo de menos
							
              // En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un signo de menos en Token  y arroja un SUBTRACTION en Type
							token.push_back(tipos[i][j]);
							type.push_back("SUBTRACTION");
							numeros.push_back("---");
							break;
						  }
						
						if(tipos[i][j] == '^') { // El recorrido llega a un signo de porcentaje
							
              // En Token se le agrega un 0 y arroja un VARIABLE en Type
							token.push_back('0');
							type.push_back("VARIABLE");
							numeros.push_back(elements);
							
							// Arroja un signo de porcentaje en Token  y arroja un POWER en Type
							token.push_back(tipos[i][j]);
							type.push_back("|POWER");
							numeros.push_back("---");
							break;
						  }
						elements+=tipos[i][j];
						j++;	
					}
					
					// El recorrido agrega los digitos
	 				if(j == tipos[i].size()){

	 					// En Token se le agrega un 0 y arroja un VARIABLE en Type
						token.push_back('0');
						type.push_back("VARIABLE");
						numeros.push_back(elements);
					}											
				}
			}		
		}
	}
	
	
  //Formato de la Tabla
  cout<<"Token\t\t\t\t\t\t\t\t"<<"Type"<<endl;
  cout<<"---------------------------------------------------------"
  <<endl;
	
	for (int i = 0; i < token.size(); i++) {

		// Muestra Token
		if(token[i] == '0')
			cout<<numeros[i]<<"\t\t\t\t\t\t\t\t"<<type[i]<<endl;
		
		// Muestra el resto de Token
		else
    cout<< token[i]<<"\t\t\t\t\t\t\t\t"<<type[i]<<endl;
		cout<<"---------------------------------------------------------"
    <<endl;
    }
}

int main(int argc, char* argv[]) {
	string archivo; // Variable para escribir el nombre del archivo
	
	// Para escribir el nombre del archivo
	cout<<"Nombre del archivo: ";
	cin>>archivo;
	cout<<"\n";	
	
	// Llamamos a la función
	lexerAritmetico(archivo);
}
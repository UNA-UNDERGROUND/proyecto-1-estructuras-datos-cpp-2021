#include <iostream>
#include "cola_prioridad.hpp"

int main() { 
	ListaDoble<int> valores{2,3,5,6,7,9,1};
	colaPrioridad<int> cola(valores);
	for (size_t i = 0; i < valores.size(); i++) {
		std::cout << "valor actual:" << cola.recuperar() << "\n";
	}
	std::cin.ignore();
}
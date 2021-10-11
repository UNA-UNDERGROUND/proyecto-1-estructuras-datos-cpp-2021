#include "heap.hpp"

template <typename T> class colaPrioridad : private Heap<T> {
  private:
	bool menor = false;

  public:
	using Heap<T>::Heap;
	colaPrioridad(bool menor = false) : menor(menor) {}
	void insertar(T elem) {
		for (size_t i = 0; i < Heap<T>::size(); i++) {
			T val = Heap<T>::at(i);
			// cada clase es responsable de sobrecargar su operador
			if (menor ? elem < val : elem > val) {
				Heap<T>::insertar(elem, i);
				return;
			}
		}
		Heap<T>::insertarFinal(elem);
	}
	T recuperar() {
		T val = Heap<T>::at(0);
		Heap<T>::eliminarInicio();
		return val;
	}
    void pop(){
        Heap<T>::eliminarInicio();
    }
	bool vacio() { return Heap<T>::size() == 0; }
};
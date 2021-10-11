#include "heap.hpp"

template <typename T> class colaPrioridad {
  private:
	bool mayor = false;
	Heap<T> heap;

  public:
	colaPrioridad(ListaDoble<T>& lista, bool mayor = false): colaPrioridad(mayor){
		heap = Heap<T>::crearHeap(lista);
	}
	colaPrioridad(bool mayor = false) : mayor(mayor) {}
	void insertar(T elem) {
		heap.Insertar(elem, mayor);
	}
	T recuperar() {
		T val = heap.top();
		pop();
		return val;
	}
    void pop(){
		heap.Eliminar();
    }
	bool vacio() { return heap.size() == 0; }

	template <typename T> bool compara(T& obj_a, T& obj_b) { 
		return (obj_a > obj_b) ? true : false; 
	}
};
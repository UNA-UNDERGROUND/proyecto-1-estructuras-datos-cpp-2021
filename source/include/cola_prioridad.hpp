#include <lista_doble.hpp>

template <typename T> class colaPrioridad : public ListaDoble<T> {
  private:
	bool menor = false;

  public:
	colaPrioridad(bool menor = false) : menor(menor) {}
	void insertar(T elem) {
		for (size_t i = 0; i < ListaDoble<T>::size(); i++) {
			T val = ListaDoble<T>::at(i);
			// cada clase es responsable de sobrecargar su operador
			if (menor ? elem < val : elem > val) {
				ListaDoble<T>::insertar(elem, i);
				return;
			}
		}
		ListaDoble<T>::insertarFinal(elem);
	}
	T recuperar() {
		T val = ListaDoble<T>::at(0);
		ListaDoble<T>::eliminarInicio();
		return val;
	}
    void pop(){
        ListaDoble<T>::eliminarInicio();
    }
	bool vacio() { return ListaDoble<T>::size() == 0; }
};
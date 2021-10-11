#pragma once
#include "lista_doble.hpp"

template <typename T> class Heap : private ListaDoble<T> {
	size_t getPadre(size_t pos) { return (pos - 1) / 2; }
	size_t getIzquierdo(size_t pos) { return (2 * pos + 1); }
	size_t getDerecho(size_t pos) { return (2 * pos + 2); }

	void heapify_down(size_t pos, bool ordenMayor = true) {
		size_t izquierdo = getIzquierdo(pos);
		size_t derecho = getDerecho(pos);
		size_t actual = pos;

		if (izquierdo < size() &&
		    (ordenMayor ? ListaDoble<T>::at(izquierdo) > ListaDoble<T>::at(pos)
		                : ListaDoble<T>::at(izquierdo) < ListaDoble<T>::at(pos))) {
			actual = izquierdo;
		}
		if (derecho < size() &&
		    (ordenMayor ? ListaDoble<T>::at(derecho) > ListaDoble<T>::at(actual)
		                : ListaDoble<T>::at(derecho) < ListaDoble<T>::at(actual))) {
			actual = derecho;
		}
		if (actual != pos) {
			ListaDoble<T>::swap(pos, actual);
			heapify_down(actual);
		}
	}
	void heapify_up(size_t pos, bool ordenMayor = true) {
		if (pos &&
		    (ordenMayor ? ListaDoble<T>::at(getPadre(pos)) < ListaDoble<T>::at(pos)
		                : ListaDoble<T>::at(getPadre(pos)) > ListaDoble<T>::at(pos))) {
			ListaDoble<T>::swap(pos, getPadre(pos));
			heapify_up(getPadre(pos));
		}
	}

  public:
	Heap() = default;
	explicit Heap(std::initializer_list<T> l) : ListaDoble<T>(l) { Heapify(); }
	explicit Heap(Heap<T> &&heap) : ListaDoble<T>(heap) { Heapify(); }
	explicit Heap(Heap<T> &heap) : ListaDoble<T>(heap) { Heapify(); }
	explicit Heap(ListaDoble<T> &&v) : ListaDoble<T>(v) { Heapify(); }
	explicit Heap(ListaDoble<T> &v) : ListaDoble<T>(v) { Heapify(); }

	size_t size() const { return ListaDoble<T>::size(); }
	bool empty() const { return size() == 0; }

	void Insertar(T &valor, bool ordenMayor = true) {
		ListaDoble<T>::push_back(valor);
		size_t indice = size() - 1;
		heapify_up(indice, ordenMayor);
	}
	void Insertar(T &&valor) {
		ListaDoble<T>::push_back(valor);
		size_t indice = size() - 1;
		heapify_up(indice);
	}
	void Eliminar() {
		if (empty()) {
			throw std::underflow_error("no hay elementos en el Heap");
		}
		size_t pos = size() - 1;
		ListaDoble<T>::at(0) = ListaDoble<T>::at(pos);
		ListaDoble<T>::pop_back();
		heapify_down(0);
	}
	T &top() {
		if (empty()) {
			throw std::underflow_error("no hay elementos en el Heap");
		}
		return ListaDoble<T>::at(0);
	}
	const T &top() const {
		if (empty()) {
			throw std::underflow_error("no hay elementos en el Heap");
		}
		return ListaDoble<T>::at(0);
	}

	void clear() { ListaDoble<T>::clear(); }

	T &operator[](size_t pos) { return ListaDoble<T>::at(pos); }

	Heap &operator=(Heap<T> &&heap) {
		ListaDoble<T>::operator=(heap);
		Heapify();
		return *this;
	}
	Heap &operator=(Heap<T> &heap) {
		ListaDoble<T>::operator=(heap);
		Heapify();
		return *this;
	}
	Heap &operator=(ListaDoble<T> &&v) {
		ListaDoble<T>::operator=(v);
		Heapify();
		return *this;
	}
	Heap &operator=(ListaDoble<T> &v) {
		ListaDoble<T>::operator=(v);
		Heapify();
		return *this;
	}

	Heap &Heapify(bool ordenMayor = true) {
		if (size()) {
			for (int i = size() / 2 - 1; i >= 0; i--) {
				heapify_down(i, ordenMayor);
			}
			for (int i = size() - 1; i >= 0; i--) {
				ListaDoble<T>::swap(0, i);
				heapify_down(0, ordenMayor);
			}
		}
		return *this;
	}

	static Heap crearHeap(ListaDoble<T>& lista){
		return Heap(lista);
	}
};

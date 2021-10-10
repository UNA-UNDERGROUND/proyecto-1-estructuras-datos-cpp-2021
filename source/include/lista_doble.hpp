#pragma once
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <tuple>
#include <type_traits>

template <typename T> class ListaDoble {
  private:
	class nodo {
		T valor;
		nodo *siguiente = nullptr;
		nodo *anterior = nullptr;

	  public:
		explicit nodo(T &valor, nodo *siguiente = nullptr, nodo *anterior = nullptr)
		    : valor(valor), siguiente(siguiente), anterior(anterior) {}
		const T &getValor() const { return valor; }
		T &getValor() { return valor; }
		void setSiguiente(nodo *n) { siguiente = n; }
		void setAnterior(nodo *n) { anterior = n; }
		nodo *getSiguiente() const { return siguiente; }
		nodo *getAnterior() const { return anterior; }
		void swap(nodo &b) { std::swap(valor, b.valor); }

		~nodo() {
			if constexpr (std::is_pointer<T>::value) {
				delete valor;
			}
		}
	};
	nodo *inicio = nullptr;
	nodo *ultimo = inicio;
	size_t len = 0;

  public:
	ListaDoble() = default;
	explicit ListaDoble(std::initializer_list<T> l) : len(l.size()) {
		nodo *actual = nullptr;
		for (auto val : l) {
			if (actual) {
				actual = new nodo(val, nullptr, actual);
			} else {
				inicio = new nodo(val, nullptr, actual);
				actual = inicio;
			}
			nodo *anterior = actual->getAnterior();
			if (anterior) {
				anterior->setSiguiente(actual);
			}
		}
		ultimo = actual;
	}
	explicit ListaDoble(const ListaDoble &l) : len(l.len) {
		nodo *otro = l.inicio;
		nodo *actual = inicio;
		for (size_t pos = 0; pos < l.len; pos++) {
			actual = new nodo(otro->getValor(), nullptr, actual);
			nodo *anterior = actual->getAnterior();
			if (anterior) {
				anterior->setSiguiente(actual);
			}
			otro = otro->getSiguiente();
		}
		ultimo = actual;
	}
	explicit ListaDoble(ListaDoble &&l) noexcept
	    : inicio(l.inicio), ultimo(l.ultimo), len(l.len) {
		l.ultimo = l.inicio = nullptr;
		l.len = 0;
	}

	void push_front(T &n) {
		inicio = new nodo(n, inicio);
		nodo *sig = inicio->getSiguiente();
		if (sig) {
			sig->setAnterior(inicio);
		}

		if (!ultimo) {
			ultimo = inicio;
		}
		len++;
	}
	void push_back(T &n) {
		if (len) {
			ultimo->setSiguiente(new nodo(n, nullptr, ultimo));
			ultimo = ultimo->getSiguiente();
			// getNodo(len - 1)->setSiguiente(new nodo(n));
			len++;
		}
		else {
			push_front(n);
		}
	}
	bool pop_front() {
		if (inicio) {
			nodo *siguiente = inicio->getSiguiente();
			delete inicio;
			if (siguiente) {
				siguiente->setAnterior(nullptr);
			}
			inicio = siguiente;
			len--;
			return true;
		}
		return false;
	}
	bool pop_back() {
		if (len != 0) {
			if (len == 1) {
				delete inicio;
			} else {
				nodo *n = getNodo(len - 1);
				ultimo = n->getAnterior();
				ultimo->setSiguiente(nullptr);
				delete n;
			}
			len--;
			return true;
		}
		return false;
	}

	void insert(T &n, size_t pos = 0) {
		if (pos == 0) {
			push_front(n);
		} else if (pos <= len) {
			nodo *anterior = getNodo(pos - 1);
			nodo *nuevo = new nodo(n, anterior, anterior->getSiguiente());
			anterior->getSiguiente()->setSiguiente(nuevo);
			anterior->setSiguiente(nuevo);
			len++;
		} else {
			throw std::out_of_range("posicion fuera de los limites");
		}
	}
	bool erase(size_t pos = 0) {
		if (pos == 0) {
			return pop_front();
		}
		if (pos < len) {
			nodo *previo = getNodo(pos - 1);
			nodo *sig = previo->getSiguiente()->getSiguiente();
			delete previo->getSiguiente();
			previo->setSiguiente(sig);
			len--;
			return true;
		}
		return false;
	}

	size_t size() const { return len; }
	bool empty() const { return len; }
	void clear() {
		while (len) {
			pop_front();
		}
	}

	T &at(size_t pos) {
		nodo *n = getNodo(pos);
		if (n) {
			return n->getValor();
		}
		throw std::out_of_range("posicion fuera de los limites");
	}
	const T &at(size_t pos) const {
		nodo *n = getNodo(pos);
		if (n) {
			return n->getValor();
		}
		throw std::out_of_range("posicion fuera de los limites");
	}

	T &operator[](size_t pos) { return at(pos); }
	const T &operator[](size_t pos) const { return at(pos); }

	void swap(size_t a, size_t b) {
		if (len && a < len && b < len && a != b) {
			nodo *nodoA = getNodo(a);
			nodo *nodoB = getNodo(b);
			nodoA->swap(*nodoB);
		}
	}

  private:
	nodo *getNodo(size_t pos) const {
		if (pos >= len || len == 0) {
			return nullptr;
		}
		// c++ 17, pre c++17 puede declarar uno de los 2 afuera
		bool reversa = pos > len / 2;
		for (auto [n, i] =
		         std::tuple{reversa ? ultimo : inicio, reversa ? len - 1 : 0};
		     n; (reversa ? i-- : i++),
		              n = (reversa ? n->getAnterior() : n->getSiguiente())) {
			if (i == pos) {
				return n;
			}
		}
		return nullptr;
	}

  public:
	class Iterator {
		nodo *actual = nullptr;

	  public:
		Iterator(nodo *n = nullptr) : actual(n) {}

		T &operator*() { return actual->getValor(); }
		bool operator!=(Iterator &o) { return this->actual != o.actual; }

		Iterator &operator++() {
			actual = actual ? actual->getSiguiente() : actual;
			return *this;
		}
		Iterator &operator--() {
			actual = actual ? actual->getAnterior() : actual;
			return *this;
		}
	};
	class ConstIterator {
		nodo *actual = nullptr;

	  public:
		ConstIterator(nodo *n = nullptr) : actual(n) {}

		const T &operator*() { return actual->getValor(); }
		bool operator!=(ConstIterator &o) { return this->actual != o.actual; }

		ConstIterator &operator++() {
			actual = actual ? actual->getSiguiente() : actual;
			return *this;
		}
		ConstIterator &operator--() {
			actual = actual ? actual->getAnterior() : actual;
			return *this;
		}
	};

	ListaDoble operator=(const ListaDoble &l) {
		clear();

		nodo *otro = l.inicio;
		nodo *actual = inicio;
		for (size_t pos = 0; pos < l.len; pos++) {
			actual = new nodo(otro->getValor(), nullptr, actual);
			nodo *anterior = actual->getAnterior();
			if (anterior) {
				anterior->setSiguiente(actual);
			}
			otro = otro->getSiguiente();
		}
		ultimo = actual;
		return *this;
	}
	ListaDoble operator=(ListaDoble &&l) noexcept {
		clear();
		inicio = l.inicio;
		ultimo = l.ultimo;
		len = l.len;
		l.ultimo = l.inicio = nullptr;
		l.len = 0;
		return *this;
	}

	Iterator begin() { return Iterator(inicio); }
	Iterator end() { return Iterator(ultimo); }

	~ListaDoble() { clear(); }
};

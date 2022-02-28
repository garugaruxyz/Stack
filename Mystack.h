#ifndef My_Stack_h
#define My_Stack_h

#include <iterator>
#include <cstddef>  // std::ptrdiff_t
#include <ostream> // std::ostream
#include <iostream> // std::cout
#include <cassert>

template <typename T>
class Mystack {
  T *_arr;
  unsigned int _size;
    

public:
	/**
		Costruttore di default. 

		@post _arr==new T [0]
		@post _size==0
	*/
	Mystack() : _size(0), _arr(new T [0]){}
	/**
		Costruttore di copia

		@param other stack da copiare
		@throw eccezione di allocazione di memoria
	*/
	Mystack(const Mystack &other) : _size(other._size), _arr(new T [other._size]){
 		try {
		//Creo nuovo array
		for (int i = 0; i < _size; i++)
			_arr[i] = other._arr[i];
		} catch (...) {
			svuota();
			throw;
		}
	}

	/**
		Distruttore
	*/
	~Mystack(){ clear(); }

	/**
	* Cancella il contenuto nella lista
	*/
	void clear() {
		_size = 0;
		delete[] _arr;
	}
	/**
	* Inserimento di un valore in cima allo stack
	* @param val valore da inserire nella lista
	* @throw eccezione di allocazione di memoria
	*/
	void push(const T &val){
		try
		{
			_size = _size + 1;
			T *buff = new T [_size];
		
			//Creo temporaneo
			for (int i = 0; i < _size-1; i++)
				buff[i] = _arr[i];

			buff[_size-1] = val;  //Aggiungo ultimo valore inserito
			delete[] _arr;        //Elimino vecchio
			
			//scambio array tra puntatori
			_arr = nullptr;
			_arr = buff;
			buff = nullptr;
		}
		catch(...)
		{
			throw;
		}
	}

	/**
	*	Rimuovi il valore in cima allo stack
	*	@return valore in cima allo stack
	*/
	T pop(){
		//controllo underflow
		if(isEmpty()){
			clear();
			assert(_size > 0 && "Stack underflow termino il programma");
		}
		//valore da tornare
		T val = _arr[_size-1];
		//size diminuisce di 1
		_size = _size - 1;
		//creo buffer, controllo prima che non vada in underflow
		T *buff = new T [_size];

		//Creo temporaneo
		for (int i = 0; i < _size; i++)
			buff[i] = _arr[i];

		delete[] _arr;        //Elimino vecchio
		//scambio array tra puntatori
		_arr = nullptr;
		_arr = buff;
		buff = nullptr;
		
		return val;
	}

	/**
	*	Controlla se lo stack è vuoto
	*	@return true se lo stack è vuoto
	*/
	bool isEmpty() const{return _size <= 0;}

	/**
	*	Visualizza il valore in cima allo stack
	*	@return valore in cima allo stack
	*/
	T peek() {
		if(isEmpty()){
			clear();
			assert(_size > 0 && "Stack underflow termino il programma");
		}
		return _arr[_size-1];
	}
	/**
	*	Controlla dimensione dello stack
	*	@return dimensione dello stack
	*/
	unsigned int getSize() const { return _size; }

	/**
	*	Un metodo per svuotare lo stack.
	*/
	void svuota() {
		_size = 0;
		delete[] _arr;
		_arr = nullptr;
	}

	/**
	*	Un costruttore che prende una coppia di iteratori: uno che punta all’inizio
	*	di una sequenza di elementi e uno che punta alla fine della sequenza.
	*	Questo costruttore è usato per riempire lo stack. 
	*	@param begin iteratore di inizio della sequenza dati
	*	@param end iteratore di fine della sequenza dati
	*	@throw eccezione di allocazione della memoria
	*/
	template <typename IterT> 
	Mystack(IterT begin, IterT end) : _size(0), _arr(new T[0]) {
		try{
			while(begin != end) {
				push(static_cast<T>(*begin));
				++begin;
			}
		}
		catch(...) {
			svuota();
			throw;
		}
	}

	/**
	*	Un metodo pubblico che ha la stessa funzionalità del costruttore secondario 
	*   che costruisce una lista a partire da una
	*	sequenza di dati identificata da due iteratori.
	*   Se lo stack contiene già dei dati, questi vengono rimossi.
	*
	*	@param begin iteratore di inizio della sequenza dati
	*	@param end iteratore di fine della sequenza dati
	*	@throw eccezione di allocazione della memoria
	*/
	template <typename IterT> 
	void riempiStack(IterT begin, IterT end){
		try{
			if(_size > 0){
				std::cout << "L' array contiene valori, eseguo svuota()" << std::endl;
				svuota();
			}
			while(begin != end) {
				push(static_cast<T>(*begin));
				++begin;
			}
		}
		catch(...) {
			svuota();
			throw;
		}
	}

	/**
	*	Un metodo pubblico removeif che, dato un predicato generico P su un
	*	elemento di tipo T (liberamente definibile dall'utente), elimina dallo stack
	*	tutti gli elementi che soddisfano il predicato P.
	*
	*	@param op tipo di operazione da effettuare
	*	@throw eccezione di allocazione della memoria
	*/
	template <typename P>
	void removeif(const P &op){
		try
		{
			typename Mystack<T>::const_iterator begin, end;
		
			unsigned int i = 0;
			//conta valori per nuova size
			for(begin = this->begin(), end = this->end(); begin!=end; begin--){
				if(op(*begin))
					i++;
			}

			//creo buff di dimensione necessaria
			T *buff = new T [i];
			i = 0;

			//metto i valori che rispettano la condizione nel buff
			for(begin = this->begin(), end = this->end(); begin!=end; begin--){
				if(!(op(*begin))){
					buff[i] = *begin;
					i++;
				}
			}

			delete[] _arr;        //Elimino vecchio
			//scambio array tra puntatori
			_size = i;
			_arr = nullptr;
			_arr = buff;
			buff = nullptr;
		}
		catch(...)
		{
			throw;
		}
	}

	class const_iterator;

	class const_iterator {
		//	
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef ptrdiff_t                       difference_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;

	
		const_iterator() : ptr(nullptr) {}
		
		const_iterator(const const_iterator &other) : ptr(other.ptr) {}

		const_iterator& operator=(const const_iterator &other) {
			ptr = other.ptr;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return ptr;
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++ptr;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			++ptr;
			return *this;
		}

		// Operatore di iterazione post-decremento
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--ptr;
			return tmp;
		}

		// Operatore di iterazione pre-decremento
		const_iterator &operator--() {
			--ptr;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (ptr == other.ptr);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (ptr != other.ptr);
		}

	private:
		const T* ptr;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Mystack; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T* p) : ptr(p) {}
		
		// !!! Eventuali altri metodi privati
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_arr + (_size -1));
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(_arr - 1);
	}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Mystack<T> &m) {
	typename Mystack<T>::const_iterator begin, end;
    
	begin = m.begin();
	end = m.end();

	if(m.getSize() > 0){
		while(begin!=end){
			os << *begin << " ";
			begin--;
		}
	}
	else
		os << "Stack vuoto" << std::endl;
	return os;
}

#endif
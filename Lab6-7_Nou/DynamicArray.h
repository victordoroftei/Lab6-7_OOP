#pragma once

template <typename ElementT>
class IteratorVector;

template<typename ElemType>
class DynamicArray
{

private:

	int dim, cap;
	ElemType* elem;

	void redimensionare()
	{
		ElemType* newElem = new ElemType[this->cap * 2];

		int i;
		for (i = 0; i <= this->dim - 1; i++)
			newElem[i] = this->elem[i];

		delete[] elem;
		elem = newElem;

		this->cap *= 2;
	}

public:

	/*
		Parametri de intrare / iesire:
			-

		Preconditii / postconditii:
			-

		Constructorul clasei DynamicArray.
	*/
	DynamicArray()
	{
		this->dim = 0;
		this->cap = 1;
		this->elem = new ElemType[this->cap];
	}

	/*
		Parametri de intrare:
			- other: alt DynamicArray

		Parametri de iesire:
			-

		Preconditii:
			- other: DynamicArray

		Postconditii:
			- this = other

		Constructorul de copiere pentru clasa DynamicArray.
	*/
	DynamicArray(const DynamicArray& other)
	{
		int i = 0;

		this->cap = other.cap;
		this->dim = other.dim;
		this->elem = new ElemType[this->cap];
		for (i = 0; i <= other.dim - 1; i++)
			this->elem[i] = other.elem[i];
	}

	/*
		Parametri de intrare:
			- other: alt DyamicArray

		Parametri de iesire:
			-

		Preconditii:
			- other: DynamicArray

		Postconditii:
			-

		Suprascrierea pentru operatorul ==
		Functia returneaza true daca this == other, sau false, in caz contrar.
	*/
	bool operator ==(const DynamicArray& other) const
	{
		if (other.dim != this->dim)
			return false;

		int i;
		for (i = 0; i <= other.dim - 1; i++)
			if (!(other.elem[i] == this->elem[i]))
				return false;

		return true;
	}

	/*
		Parametri de intrare:
			- other: alt DyamicArray

		Parametri de iesire:
			-

		Preconditii:
			- other: DynamicArray

		Postconditii:
			- this = other

		Suprascrierea pentru operatorul =
	*/
	DynamicArray& operator =(const DynamicArray& other)
	{
		if (this == &other)
			return *this;

		ElemType* newElem = new ElemType[other.cap];

		int i;
		for (i = 0; i <= other.size() - 1; i++)
			newElem[i] = other.elem[i];

		delete[] this->elem;

		this->elem = newElem;
		this->cap = other.cap;
		this->dim = other.dim;

		return *this;
	}

	/*
		Parametri de intrare / iesire:
			-

		Precnditii / postconditii:
			-

		Functia ce returneaza dimensiunea vectorului.
	*/
	int size() const
	{
		return this->dim;
	}

	/*
		Parametri de intrare:
			- index: indexul elementului din vector ce trebuie modificat
			- e: elementul nou

		Parametri de iesire:
			-

		Preconditii:
			- index: integer pozitiv
			- e: ElemType

		Postconditii:
			- this->elem = this->elem - this->elem[index] + e
	*/
	void modify(int index, ElemType& e)
	{
		this->elem[index] = e;
	}

	/*
		Parametri de intrare:
			- index: indexul elementului ce trebuie sters

		Parametri de iesire:
			-

		Preconditii:
			- index: integer pozitiv

		Postconditii:
			- this->elem = this->elem - e

		Functia ce sterge elementul de pe pozitia transmisa ca parametru.
	*/
	void erase(int index)
	{
		int i;

		for (i = index; i <= this->dim - 2; i++)
			this->elem[i] = this->elem[i + 1];

		this->dim--;
	}

	/*
		Parametri de intrare:
			- e: elementul ce trebuie adaugat in vector

		Parametri de iesire:
			-

		Preconditii:
			- e: ElemType

		Postconditii:
			- this->elem = this->elem + e
			- (this->capacitate = 2 * this->capacitate)

		Functia adauga la finalul vectorului elementul transmis ca parametru, redimensionand daca este nevoie.
	*/
	void push_back(const ElemType& e)
	{
		if (this->dim + 1 > this->cap)
			this->redimensionare();

		this->elem[this->dim] = e;
		this->dim++;
	}

	/*
		Parametri de intrare:
			- index: indexul elementului ce trebuie returnat

		Parametri de iesire:
			-

		Preconditii:
			- index: integer pozitiv

		Postconditii:
			-

		Functia returneaza elementul din vector de pe pozitia transmisa ca parametru.
	*/
	ElemType& at(int index) const
	{
		return this->elem[index];
	}

	/*
		Parametri de intrare / iesire:
			-

		Precnditii / postconditii:
			-

		Destructorul clasei DynamicArray.
	*/
	~DynamicArray()
	{
		delete[] this->elem;
	}

	friend class IteratorVector<ElemType>;

	IteratorVector<ElemType> begin()
	{
		return IteratorVector<ElemType>(*this);
	}

	IteratorVector<ElemType> end()
	{
		return IteratorVector<ElemType>(*this, dim);
	}

};


template<typename ElemType>
class IteratorVector
{

private:

	const DynamicArray<ElemType>& v;
	int poz = 0;

public:

	IteratorVector(const DynamicArray<ElemType>& v) noexcept : v{ v } {}

	IteratorVector(const DynamicArray<ElemType>& v, int poz) noexcept : v{ v }, poz{ poz } {}

	bool valid() const
	{
		return this->poz < this->v.dim;
	}

	ElemType& element() const
	{
		return this->v.elem[poz];
	}

	void next()
	{
		this->poz++;
	}

	ElemType& operator*()
	{
		return this->element();
	}

	IteratorVector& operator++()
	{
		next();
		return *this;
	}

	bool operator==(const IteratorVector& other)noexcept
	{
		return this->poz == other.poz;
	}

	bool operator!=(const IteratorVector& other)noexcept
	{
		return !(*this == other);
	}
};
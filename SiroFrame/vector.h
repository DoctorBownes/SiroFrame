#ifndef VECTOR_H_
#define VECTOR_H_

template <typename T>
class SiroVector {
public:
	SiroVector();
	~SiroVector();
	void push_back(T newval);
	unsigned char resize(unsigned char size);
	unsigned char size() { return arraySize; };
	
	T& operator[](unsigned char index) {
		return templateArray[index];
	}

private:
	T* templateArray;
	unsigned char arraySize = 0;
};

template<typename T>
SiroVector<T>::SiroVector() {
	templateArray = nullptr;
}

template<typename T>
SiroVector<T>::~SiroVector() {
	delete[] templateArray;
}

template<typename T>
unsigned char SiroVector<T>::resize(unsigned char size) {
	// Allocate memory for the array in the temporary array.
	T* tmpArray = new T[size];

	// Copy the elements of old array.
	for (unsigned char count = 0; count < size; count++) {
		*(tmpArray + count) = *(templateArray + count);
	}

	// Delete old array
	delete[] templateArray;

	// Copy array
	templateArray = tmpArray;

	// Increase size
	return arraySize = size;
};

template <typename T>
void SiroVector<T>::push_back(T newval) {
	// Allocate memory for the array in the temporary array.
	T* tmpArray = new T[arraySize + 1];

	// Copy the elements of old array.
	for (unsigned char count = 0; count < arraySize; count++) {
		*(tmpArray + count) = *(templateArray + count);
	}

	// Push new value
	*(tmpArray + arraySize) = newval;

	// Delete old array
	delete[] templateArray;

	// Copy array
	templateArray = tmpArray;

	// Increase size
	arraySize++;
};

#endif

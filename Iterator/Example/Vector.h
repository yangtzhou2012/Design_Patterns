#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "LinearStruct.h"

template <typename T>
class VectorIterator;

template <typename T>
class Vector : public LinearStruct<T>
{
public:
	Vector();
	Vector(int len);
	virtual ~Vector();

	virtual bool PushFront(const T &item);
	virtual bool PopFront(void);
	virtual bool PushBack(const T &item);
	virtual bool PopBack(void);

	virtual T* Front(void);
	virtual const T* Front(void) const;
	virtual T* Back(void);
	virtual const T* Back(void) const;

	virtual int Size(void) const;

	virtual VectorIterator<T>* CreateIterator(void);

protected:
	T *data;
	int capacity;
	int count;

	static const int defCapacity;

	friend class VectorIterator<T>;
};

template <typename T>
class VectorIterator : public LinearIterator<T>
{
public:
	VectorIterator(const Vector<T> *vec);

	virtual void First(void);
	virtual void Next(void);
	virtual bool IsDone(void);
	virtual T* CurrentItem(void);

protected:
	const Vector<T> *vector;
	int current;
};


template <typename T>
const int Vector<T>::defCapacity = 16;

template <typename T>
Vector<T>::Vector() : data(NULL), capacity(0), count(0)
{
	data = new T[defCapacity];
	if (data)
		capacity = defCapacity;
}

template <typename T>
Vector<T>::Vector(int len) : data(NULL), capacity(0), count(0)
{
	if (len <= 0)
		len = defCapacity;

	data = new T[len];
	if (data)
		capacity = len;
}

template <typename T>
Vector<T>::~Vector()
{
	if (data)
		delete[] data;
}

template <typename T>
bool Vector<T>::PushFront(const T &item)
{
	T *temp = NULL;

	if (count == capacity) {
		T *temp = new T[capacity * 2];
		if (temp == NULL)
			return false;
		capacity *= 2;
	} else {
		temp = data;
	}

	for (int i = count - 1; i >= 0; i--)
		temp[i+1] = data[i];
	temp[0] = item;
	count++;

	if (temp != data) {
		delete[] data;
		data = temp;
	}

	return true;
}

template <typename T>
bool Vector<T>::PopFront(void)
{
	if (count > 0) {
		for (int i = 0; i < count - 1; i++)
			data[i] = data[i+1];
		count--;
		return true;
	} else {
		return false;
	}
}

template <typename T>
bool Vector<T>::PushBack(const T &item)
{
	if (count == capacity) {
		T *temp = new T[capacity * 2];
		if (temp == NULL)
			return false;

		for (int i = 0; i < count; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
		capacity *= 2;
	}

	data[count++] = item;
	return true;
}

template <typename T>
bool Vector<T>::PopBack(void)
{
	if (count > 0) {
		count--;
		return true;
	} else {
		return false;
	}
}

template <typename T>
int Vector<T>::Size(void) const
{
	return count;
}

template <typename T>
T* Vector<T>::Front(void)
{
	if (count > 0)
		return &data[0];
	else
		return NULL;
}

template <typename T>
const T* Vector<T>::Front(void) const
{
	if (count > 0)
		return &data[0];
	else
		return NULL;
}

template <typename T>
T* Vector<T>::Back(void)
{
	if (count > 0)
		return &data[count-1];
	else
		return NULL;
}

template <typename T>
const T* Vector<T>::Back(void) const
{
	if (count > 0)
		return &data[count-1];
	else
		return NULL;
}

template <typename T>
VectorIterator<T>* Vector<T>::CreateIterator(void)
{
	return (new VectorIterator<T>(this));
}


template <typename T>
VectorIterator<T>::VectorIterator(const Vector<T> *vec) : vector(vec), current(0)
{

}

template <typename T>
void VectorIterator<T>::First(void)
{
	current = 0;
}

template <typename T>
void VectorIterator<T>::Next(void)
{
	current++;
}

template <typename T>
bool VectorIterator<T>::IsDone(void)
{
	if (vector)
		return (current >= vector->count ? true : false);
	else
		return true;
}

template <typename T>
T* VectorIterator<T>::CurrentItem(void)
{
	if (!IsDone())
		return &(vector->data[current]);
	else
		return NULL;
}

#endif // _VECTOR_H_

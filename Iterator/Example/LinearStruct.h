#ifndef _LINEAR_STRUCT_H_
#define _LINEAR_STRUCT_H_

template <typename T>
class LinearIterator;

template <typename T>
class LinearStruct {
public:
	virtual bool PushFront(const T &item) = 0;
	virtual bool PopFront(void) = 0;
	virtual bool PushBack(const T &item) = 0;
	virtual bool PopBack(void) = 0;

	virtual T* Front(void) = 0;
	virtual const T* Front(void) const = 0;
	virtual T* Back(void) = 0;
	virtual const T* Back(void) const = 0;

	virtual LinearIterator<T>* CreateIterator(void) = 0;
};

template <typename T>
class LinearIterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual T* CurrentItem() = 0;
};

#endif // _LINEAR_STRUCT_H_
